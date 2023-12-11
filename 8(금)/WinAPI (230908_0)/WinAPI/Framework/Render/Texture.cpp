#include "Framework.h"

unordered_map<wstring, Texture*> Texture::textures;
bool Texture::isDebugMode = false;

Texture::Texture(wstring file, COLORREF transColor, UINT frameX, UINT frameY)
    : imageFrame{ (long)frameX, (long)frameY }, transfColor(transColor)
{
    HDC hdc = GetDC(hWnd);
    memDC = CreateCompatibleDC(hdc);
    stretchDC = CreateCompatibleDC(hdc);
    alphaMemDC = CreateCompatibleDC(hdc);
    hBitmap = (HBITMAP)LoadImage(hInst, file.c_str(),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);    

    SelectObject(memDC, hBitmap);

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);
    imageSize = { bitmap.bmWidth, bitmap.bmHeight };    

    cutSize = { imageSize.x / imageFrame.x, imageSize.y / imageFrame.y };    

    hStretchBitmap = CreateCompatibleBitmap(hdc, cutSize.x, cutSize.y);
    hAlphaBitmap = CreateCompatibleBitmap(hdc, cutSize.x, cutSize.y);

    //셀렉트 오브젝트를 생성자에서 미리 해둔다
    //왜냐면 인스턴스 하나가 그림 하나만 그릴 거니까
    //(한 함수에서 두 개 이상의 그림을 그릴 필요가 없으니까)
    // -> 텍스처 관리, 화면의 미관에 대단히 유용 (+프로그램 속도는 대폭 저하되지만... 요즘 컴퓨터가 이 정도도 못 견디진 않으니까)
    SelectObject(stretchDC, hStretchBitmap);
    SelectObject(alphaMemDC, hAlphaBitmap);

    ReleaseDC(hWnd, hdc);
}

Texture::~Texture()
{
    DeleteDC(memDC);
    DeleteDC(stretchDC);
    DeleteDC(alphaMemDC);
    DeleteObject(hBitmap);
    DeleteObject(hStretchBitmap);
    DeleteObject(hAlphaBitmap);
}

Texture* Texture::Add(wstring file, UINT frameX, UINT frameY, COLORREF transColor)
{
    if (textures.count(file) > 0)
        return textures[file];

    Texture* texture = new Texture(file, transColor, frameX, frameY);
    textures[file] = texture;

    return texture;
}

void Texture::Delete()
{
    for (pair<wstring, Texture*> texture : textures)
    {
        delete texture.second;
    }
}

void Texture::Render(HDC hdc, Rect* rect, POINT curFrame, bool isTrans)
{
    if (isDebugMode)
    {
        rect->LineRender(hdc);
    }

    if (!isTrans)
    {
        BitBlt(
            hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->size.x, (int)rect->size.y,
            memDC,
            cutSize.x * curFrame.x,
            cutSize.y * curFrame.y,            
            SRCCOPY
        );
        return;
    }

    GdiTransparentBlt(
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        (int)rect->size.x, (int)rect->size.y,
        memDC,
        cutSize.x * curFrame.x,
        cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        transfColor
    );
}

void Texture::Render(HDC hdc, Rect* rect, int alpha, POINT curFrame, bool isTrans)
{
    if (isDebugMode)
    {
        rect->LineRender(hdc);
    }

    blendFunc.SourceConstantAlpha = alpha;

    if (!isTrans)
    {
        BitBlt(
            hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->size.x, (int)rect->size.y,
            memDC,
            cutSize.x * curFrame.x,
            cutSize.y * curFrame.y,
            SRCCOPY
        );
        return;
    }

    BitBlt(
        alphaMemDC,
        0, 0, cutSize.x, cutSize.y,
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        SRCCOPY
    );

    GdiTransparentBlt(
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        memDC,
        cutSize.x * curFrame.x,
        cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        transfColor
    );

    GdiAlphaBlend(
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        (int)rect->size.x, (int)rect->size.y,
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        blendFunc
    );
}

void Texture::Render(HDC hdc, Rect* rect, bool isLeft, int alpha, POINT curFrame, bool isTrans)
{
    if (isDebugMode)
    {
        rect->LineRender(hdc);
    }

    blendFunc.SourceConstantAlpha = alpha;
    int leftMult = isLeft ? -1 : 1 ;

    if (!isTrans)
    {
        BitBlt(
            hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->size.x, (int)rect->size.y,
            memDC,
            cutSize.x * curFrame.x,
            cutSize.y * curFrame.y,
            SRCCOPY
        );
        return;
    }

    BitBlt(
        alphaMemDC,
        0, 0, cutSize.x, cutSize.y,
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        SRCCOPY
    );

    StretchBlt(
        stretchDC,
        0, 0,
        cutSize.x, cutSize.y,
        memDC,
        cutSize.x * (curFrame.x + (int)isLeft) - (int)isLeft,
        cutSize.y * curFrame.y,
        cutSize.x * leftMult, cutSize.y,
        SRCCOPY
    );

    GdiTransparentBlt(
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        stretchDC,
        0, 0,
        //cutSize.x * curFrame.x,
        //cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        transfColor
    );

    GdiAlphaBlend(
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        (int)rect->size.x, (int)rect->size.y,
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        blendFunc
    );
}

float Texture::GetPixelHeight(Vector2& pos)
{
    int startY = (int)pos.y < 0.0f ? 0 : (int)pos.y;
    int endY = imageSize.y > WIN_HEIGHT ? WIN_HEIGHT : imageSize.y;


    for (int y = startY; y <= endY; ++y)
    {
        COLORREF pixColor = GetPixel(memDC, (int)pos.x, y); 

        if (pixColor != transfColor)
        {
            return (float)y;
        }
    }

    return (float)endY;
}

float Texture::GetPixelHeight(Vector2& pos, COLORREF exColor)
{
    // 기준 점을 확실히 하자
    // 시작점 : 매개변수로 받은 위치(검색 시작 위치)가 윈도우 안에 있을 때 해당 Y좌표
    // 도착점 : 이미지와 윈도우 크기 중에서 더 작은 쪽(더 위에 있는 쪽)을 선택, 해당 Y좌표

    int startY = (int)pos.y < 0.0f ? 0 : (int)pos.y;
    int endY = imageSize.y > WIN_HEIGHT? WIN_HEIGHT : imageSize.y;

    // 기준 점을 사이에 두고 각 픽셀의 색깔 정보를 하나씩 받아온다
    // 아래 for문을 돌리면 가장 작은 Y좌표부터 검색한다 = 제일 위쪽 화소부터 분석

    for (int y = startY; y <= endY; ++y)
    {
        // 화소 분석 함수 호출
        // GetPixel 함수 : DC에 있는 모든 좌표별 픽셀의 색 정보를 반환하는 함수

        COLORREF pixColor = GetPixel(memDC, (int)pos.x, y);

        // 이 색깔이 제외 대상이 아니라면

        if (pixColor != exColor)
        {
            return (float)y; // 해당 Y좌표를 결과값으로 반환
        }
    }

    // 여기까지 왔다면 위에서부터 화소 분석을 했는데 "땅" 같은 픽셀이 없었다
    // 그러므로 "가장 밑바닥"을 반환을 해줘야 한다

    // 가장 밑바닥 = 그림의 세로 크기, 혹은 윈도우 크기, 중에서 더 작은 값
    // (캐릭터가 밖으로 튀어나가지 않게)

    return (float)endY;
}
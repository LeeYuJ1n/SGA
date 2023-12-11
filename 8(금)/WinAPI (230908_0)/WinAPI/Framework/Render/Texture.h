#pragma once

class Rect;

class Texture
{
private:
    Texture(wstring file, COLORREF transColor, UINT frameX, UINT frameY);
    ~Texture();

public:
    static Texture* Add(wstring file, UINT frameX = 1, UINT frameY = 1, COLORREF transColor = MAGENTA);
    static void Delete();

    void Render(HDC hdc, Rect* rect, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, Rect* rect, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, Rect* rect, bool isLeft, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);

    Vector2 GetSize() { return Vector2(cutSize); }
    POINT GetFrame() { return imageFrame; }

    static void SetDebug() { isDebugMode = !isDebugMode; }

    // 그림에서 화소 단위로 판별한 높이 구하기
    float GetPixelHeight(Vector2& pos); // 텍스처 내에 투명값이 지정된 경우
    float GetPixelHeight(Vector2& pos, COLORREF exColor); // 투명값 (제외값) 수동 입력

    HDC GetMemDC() { return memDC; }

private:

    //텍스처 (와 애니메이션) 출력 클래스

    //DC 3종 (메모리 버퍼, 스트레치, 알파 섞기)
    HDC memDC;
    HDC stretchDC;
    HDC alphaMemDC;

    //DC에 그림 연산 결과를 주고받기 위한 가상 비트맵 3종 (메모리 버퍼, 스트레치, 알파 섞기)
    HBITMAP hBitmap;
    HBITMAP hStretchBitmap;
    HBITMAP hAlphaBitmap;

    //알파 섞기 연산에 사용할 비트맵 섞기 정보
    BLENDFUNCTION blendFunc;

    //투명해질 색 값 (인스턴스 혹은 이미지 로딩 시에 이 색을 지정해주면 그 색이 투명해진다)
    COLORREF transfColor;

    //이미지 정보들 (크기, 프레임이 나뉠 경우 어떻게 나뉠 것인가, 잘린 프레임 크기)
    POINT imageSize;
    POINT imageFrame;
    POINT cutSize;

    //텍스처가 여럿일 경우 (애니메이션 등으로 여러 그림이 한 번에 묶일 경우) 정보를 담기 위한 맵
    static unordered_map<wstring, Texture*> textures;
    static bool isDebugMode;
};
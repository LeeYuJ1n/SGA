#include "Framework.h"

Landscape::Landscape(wstring file, bool autoPlay)
{
    for (int i = 0; i < 2; i++)
    {
        ImageRect* bg = new ImageRect(file);
        bg->size = { bg->size.x, WIN_HEIGHT };
        bg->pos = { bg->Half().x + bg->size.x * i, bg->Half().y};        
        bgs.push_back(bg);
    }

    //자동 스크롤 여부를 받아 스피드 변수를 초기화합니다.
    autoScroll = autoPlay;
    InitSpeed();
}

Landscape::~Landscape()
{
    for (ImageRect* bg : bgs)
        delete bg;
}

void Landscape::Update()
{
    // 이 클래스는 이제 Move 함수를 별도로 쓰지 않습니다.
    // 스테이지의 속도를 이어받아, 업데이트될 때마다 자기 자신을 무조건 새로고침합니다.

    // 본 클래스의 멤버 변수 bgSpeed는 생성자 호출 시에 한 번 초기화를 합니다.
    // 클래스 안의 InitSpeed() 함수를 참조해주세요.

    // 그 다음엔 (Sample)Scene.cpp 의 업데이트에서 계속 본 클래스의 인스턴스가
    // 스테이지 매니저의 속도를 반영해서 갱신하도록 해주기면 하면 됩니다.

    // SampleScene.cpp 67번째 줄에서 마지막 참조를 확인해주세요.

    for (ImageRect* bg : bgs)
    {
        bg->pos.x -= bgSpeed * DELTA;
        offsetX += bgSpeed * DELTA;

        if (bg->Right() <= 0.0f)
        {
            bg->pos.x += bg->size.x * 2.0f;
        }

        if (bg->Left() >= WIN_WIDTH)
        {
            bg->pos.x -= bg->size.x * 2.0f;
        }
    }
}

void Landscape::Render(HDC hdc)
{
    for (ImageRect* bg : bgs)
        bg->Render(hdc, { 0, 0 }, false);
}

void Landscape::InitSpeed()
{
    if (autoScroll) bgSpeed = 100.0f;
    else bgSpeed = 0;

}

float Landscape::GetPixelHeight(Vector2& pos)
{
    for (ImageRect* bg : bgs)
    {
        if (pos.x > bg->Left() && pos.x < bg->Right()) // 가로 위치가 현 bg안이라면
        {
            return bg->GetPixelHeight(pos);
        }
    }

    // 혹시 몰라 보험
    return WIN_HEIGHT;
}

float Landscape::GetPixelHeight(Vector2& pos, COLORREF exColor)
{
    for (ImageRect* bg : bgs)
    {
        if (pos.x > bg->Left() && pos.x < bg->Right()) // 가로 위치가 현 bg안이라면
        {
            Vector2 pixPos = { pos.x + offsetX / offsetGl, pos.y };
            return bg->GetPixelHeight(pixPos, exColor);
        }
    }

    // 혹시 몰라 보험
    return WIN_HEIGHT;
}

HDC Landscape::GetMemDC(Vector2& pos)
{
    for (ImageRect* bg : bgs)
    {
        if (pos.x > bg->Left() && pos.x < bg->Right())
        {
            return bg->GetMemDC();
        }
    }

    return NULL;
}
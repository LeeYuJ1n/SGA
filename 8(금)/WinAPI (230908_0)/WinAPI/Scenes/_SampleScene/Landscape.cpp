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

    //�ڵ� ��ũ�� ���θ� �޾� ���ǵ� ������ �ʱ�ȭ�մϴ�.
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
    // �� Ŭ������ ���� Move �Լ��� ������ ���� �ʽ��ϴ�.
    // ���������� �ӵ��� �̾�޾�, ������Ʈ�� ������ �ڱ� �ڽ��� ������ ���ΰ�ħ�մϴ�.

    // �� Ŭ������ ��� ���� bgSpeed�� ������ ȣ�� �ÿ� �� �� �ʱ�ȭ�� �մϴ�.
    // Ŭ���� ���� InitSpeed() �Լ��� �������ּ���.

    // �� ������ (Sample)Scene.cpp �� ������Ʈ���� ��� �� Ŭ������ �ν��Ͻ���
    // �������� �Ŵ����� �ӵ��� �ݿ��ؼ� �����ϵ��� ���ֱ�� �ϸ� �˴ϴ�.

    // SampleScene.cpp 67��° �ٿ��� ������ ������ Ȯ�����ּ���.

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
        if (pos.x > bg->Left() && pos.x < bg->Right()) // ���� ��ġ�� �� bg���̶��
        {
            return bg->GetPixelHeight(pos);
        }
    }

    // Ȥ�� ���� ����
    return WIN_HEIGHT;
}

float Landscape::GetPixelHeight(Vector2& pos, COLORREF exColor)
{
    for (ImageRect* bg : bgs)
    {
        if (pos.x > bg->Left() && pos.x < bg->Right()) // ���� ��ġ�� �� bg���̶��
        {
            Vector2 pixPos = { pos.x + offsetX / offsetGl, pos.y };
            return bg->GetPixelHeight(pixPos, exColor);
        }
    }

    // Ȥ�� ���� ����
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
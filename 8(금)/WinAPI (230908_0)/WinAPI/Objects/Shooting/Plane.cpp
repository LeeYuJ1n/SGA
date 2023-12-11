#include "Framework.h"

Plane::Plane()
{
    hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
    hBrush = CreateSolidBrush(RGB(100, 100, 100));

    radius = BODY_SIZE;
}

Plane::~Plane()
{
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void Plane::Update()
{
    MoveControl();
    FireControl();
    Damage();
}

void Plane::Render(HDC hdc)
{
    SelectObject(hdc, hPen);
    SelectObject(hdc, hBrush);

    //Circle::Render(hdc);
    RenderBody(hdc);    
}

void Plane::RenderBody(HDC hdc)
{
    Ellipse(hdc, pos.x - BODY_SIZE * 0.5f, pos.y - BODY_SIZE,
        pos.x + BODY_SIZE * 0.5f, pos.y + BODY_SIZE);

    Ellipse(hdc, pos.x - BODY_SIZE, pos.y + BODY_SIZE * 0.25f,
        pos.x + BODY_SIZE, pos.y + BODY_SIZE);
}

void Plane::MoveControl()
{
    if (KEY_PRESS(VK_RIGHT))
    {
        pos.x += speed * DELTA;

        if (pos.x > WIN_WIDTH - BODY_SIZE)
            pos.x = WIN_WIDTH - BODY_SIZE;
    }
    if (KEY_PRESS(VK_LEFT))
    {
        pos.x -= speed * DELTA;

        if (pos.x < BODY_SIZE)
            pos.x = BODY_SIZE;
    }
    if (KEY_PRESS(VK_UP))
    {
        pos.y -= speed * DELTA;

        if (pos.y < BODY_SIZE)
            pos.y = BODY_SIZE;
    }
    if (KEY_PRESS(VK_DOWN))
    {
        pos.y += speed * DELTA;

        if (pos.y > WIN_HEIGHT - BODY_SIZE)
            pos.y = WIN_HEIGHT - BODY_SIZE;
    }


}

void Plane::FireControl()
{
    if (KEY_DOWN(VK_SPACE))
    {
        Vector2 firePos = pos + Vector2(0, -BODY_SIZE);
        BulletManager::Get()->Fire(firePos);
    }
}

void Plane::Damage()
{
    Enemy* enemy = EnemyManager::Get()->Collision(this);

    if (enemy)
    {
        enemy->isActive = false;

        Timer::Get()->SetDeltaScale(0.0f);

        MessageBox(hWnd, L"GameOver", L"GameOver", MB_OK);

        PostQuitMessage(0);
    }
}

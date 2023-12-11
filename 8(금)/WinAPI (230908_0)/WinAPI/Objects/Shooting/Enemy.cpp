#include "Framework.h"

Enemy::Enemy()
{
    isActive = false;
}

Enemy::~Enemy()
{
    Destroy();
}

void Enemy::Update()
{
    if (!isActive) return;

    pos.y += speed * DELTA;

    Fire();

    if (pos.y > WIN_HEIGHT + size.y * 0.5f)
        Destroy();

    Damage();
}

void Enemy::Render(HDC hdc)
{
    if (!isActive) return;

    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);

    Rect::Render(hdc);
}

void Enemy::Spawn()
{
    if (isActive) return;

    isActive = true;

    speed = Random(MIN_SPEED, MAX_SPEED);    

    size.x = Random(MIN_SIZE, MAX_SIZE);
    size.y = Random(MIN_SIZE, MAX_SIZE);

    pos.x = Random(size.x * 0.5f, WIN_WIDTH - size.x * 0.5f);
    pos.y = -size.y * 0.5f;

    int r = Random(0, 255);
    int g = Random(0, 255);
    int b = Random(0, 255);

    hBrush = CreateSolidBrush(RGB(r, g, b));
    hPen = CreatePen(PS_SOLID, 1, RGB(r, g, b));
}

void Enemy::Destroy()
{
    if (hBrush == nullptr)
        return;

    isActive = false;

    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void Enemy::Damage()
{
    if (BulletManager::Get()->Collision(this, "PlayerBullet"))
    {
        isActive = false;
    }
}

void Enemy::Fire()
{
    fireTime += DELTA;

    if (fireTime > FIRE_TIME)
    {
        fireTime = 0.0f;

        Vector2 direction = target->pos - pos;

        BulletManager::Get()->Fire(pos, direction);
    }
}

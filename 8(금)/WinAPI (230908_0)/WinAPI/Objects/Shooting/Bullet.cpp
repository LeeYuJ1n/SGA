#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
    radius = SIZE;
    isActive = false;

    hPen = CreatePen(PS_SOLID, 8, RGB(255, 100, 50));
}

Bullet::~Bullet()
{
    DeleteObject(hPen);
}

void Bullet::Update()
{
    if (!isActive) return;

    pos += direction * speed * DELTA;

    if (pos.y < -SIZE || pos.y > WIN_HEIGHT + SIZE)
        isActive = false;

    if (pos.x < -SIZE || pos.x > WIN_WIDTH + SIZE)
        isActive = false;
}

void Bullet::Render(HDC hdc)
{
    if (!isActive) return;

    //Circle::Render(hdc);

    SelectObject(hdc, hPen);

    if (tag == "PlayerBullet")
    {
        MoveToEx(hdc, pos.x, pos.y - SIZE, nullptr);
        LineTo(hdc, pos.x - SIZE, pos.y + SIZE);

        MoveToEx(hdc, pos.x, pos.y - SIZE, nullptr);
        LineTo(hdc, pos.x + SIZE, pos.y + SIZE);
    }    
    else
    {
        Circle::Render(hdc);
    }
}

void Bullet::Fire(const Vector2& pos, const Vector2& direction)
{
    isActive = true;

    this->pos = pos;
    this->direction = direction.GetNormalized();
}

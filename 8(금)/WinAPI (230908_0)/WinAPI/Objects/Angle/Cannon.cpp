#include "Framework.h"

Cannon::Cannon()
{
    radius = 50;
    barrel = new Line();
}

Cannon::~Cannon()
{
    delete barrel;
}

void Cannon::Update()
{
    if (KEY_PRESS(VK_UP))
        angle += DELTA;
    if (KEY_PRESS(VK_DOWN))
        angle -= DELTA;

    barrel->pos = pos;

    float a = mousePos.x - pos.x;
    float b = mousePos.y - pos.y;

    //angle = atan(-b / a);
    angle = atan2(-b, a);

    float x = cos(angle) * barrelLength;
    float y = -sin(angle) * barrelLength;

    barrel->end = Vector2(x, y) + pos;
}

void Cannon::Render(HDC hdc)
{
    Circle::Render(hdc);
    barrel->Render(hdc);
}

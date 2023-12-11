#pragma once

class Plane : public Circle
{
private:
    const float BODY_SIZE = 30;

public:
    Plane();
    ~Plane();

    void Update();
    void Render(HDC hdc);

private:
    void RenderBody(HDC hdc);
    void MoveControl();
    void FireControl();
    void Damage();

private:
    float speed = 200;

    HBRUSH hBrush;
    HPEN hPen;
};
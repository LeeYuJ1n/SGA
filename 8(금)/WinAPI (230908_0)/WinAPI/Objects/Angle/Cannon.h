#pragma once

class Cannon : public Circle
{
public:
    Cannon();
    ~Cannon();

    void Update();
    void Render(HDC hdc);

private:
    Line* barrel;

    float barrelLength = 200.0f;
    float angle = PI * 0.25;
};
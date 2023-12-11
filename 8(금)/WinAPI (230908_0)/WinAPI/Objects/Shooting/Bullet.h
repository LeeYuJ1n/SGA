#pragma once

class Bullet : public Circle
{
private:
    const float SIZE = 20;

public:
    Bullet();
    ~Bullet();

    void Update();
    void Render(HDC hdc);
        
    void Fire(const Vector2& pos, const Vector2& direction = Vector2(0, -1));

private:
    float speed = 500;
    Vector2 direction;

    HPEN hPen;
};
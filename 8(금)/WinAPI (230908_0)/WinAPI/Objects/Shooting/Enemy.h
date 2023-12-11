#pragma once

class Enemy : public Rect
{
private:
    const float MIN_SIZE = 50.0f;
    const float MAX_SIZE = 100.0f;
    const float MIN_SPEED = 100;
    const float MAX_SPEED = 400;
    const float FIRE_TIME = 2.0f;

public:
    Enemy();
    ~Enemy();

    void Update();
    void Render(HDC hdc);

    void Spawn();
    void Destroy();

    void Damage();

    void SetTarget(GameObject* target) { this->target = target; }

private:
    void Fire();

private:
    float speed = 0;
    float fireTime = 0.0f;

    GameObject* target;

    HBRUSH hBrush = nullptr;
    HPEN hPen = nullptr;
};
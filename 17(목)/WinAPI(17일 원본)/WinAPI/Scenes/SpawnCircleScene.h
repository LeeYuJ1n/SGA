#pragma once
#include "Objects/Bullet1.h"

class SpawnCircleScene : public Scene
{
public:
    SpawnCircleScene();
    ~SpawnCircleScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

private:
    HBRUSH hBrush;
    HPEN hPen;

    //POINT rectPos = { (int)CENTER_X, (int)CENTER_Y };
    Rect* rect;

    Circle* circle; // 동그라미
    float speed = 10; // 동그라미를 움직이고 싶어서, 움직이는 속도

    // 선을 그리려고 합니다
    float length = 120;
    float angle;
    Vector2 pos;

    int toggle;

    // 총알을 위한 인스턴스
    vector<Bullet1*> bullets;
};


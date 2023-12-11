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

    Circle* circle; // ���׶��
    float speed = 10; // ���׶�̸� �����̰� �;, �����̴� �ӵ�

    // ���� �׸����� �մϴ�
    float length = 120;
    float angle;
    Vector2 pos;

    int toggle;

    // �Ѿ��� ���� �ν��Ͻ�
    vector<Bullet1*> bullets;
};


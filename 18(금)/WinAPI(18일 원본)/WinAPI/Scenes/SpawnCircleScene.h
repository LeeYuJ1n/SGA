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

    // 총알을 위한 인스턴스 : 할당 후 관리 방식 사용
    vector<Bullet1*> bullets;
    float bulletSize = 10; // 총알 크기를 여기서 미리 지정
    int bulletCount = 5;   // 한 번에 쏠 수 있는 총알 수도 미리 지정

    // 사각형 스폰을 위한 인스턴스와 벡터 (스폰 오브젝트 사용) : 무식한 관리
    vector<SpawnObject*> rects;
    // 추가 변수가 필요하겠지만, 필요할 때 돌아오겠습니다

    // 반사 영역 판별하기 (그리고 총알 반사까지 호출하자)
    void ReflectBullet(Bullet1* bullet, SpawnObject* rect) // 매개변수로 총알과 사각형 필요
    {
        // 지름 크기의 가상 사각형 만들기
        Vector2 diameter = { bullet->GetRadius() * 2, bullet->GetRadius() * 2 };
        Rect tempRect(bullet->Pos(), diameter);

        // 최대한 더 작은 사각혀잉 나오도록 가상의 경계면을 다시 정한다
        float _left = tempRect.Left() > rect->Left() ? tempRect.Left() : rect->Left();
        float _right = tempRect.Right() < rect->Right() ? tempRect.Right() : rect->Right();
        float _top = tempRect.Top() > rect->Top() ? tempRect.Top() : rect->Top();
        float _bottom = tempRect.Bottom() < rect->Bottom() ? tempRect.Bottom() : rect->Bottom();

        // 가상의 경계면끼리 다시 거리를 측정한다
        float xDiff = _right - _left;
        float yDiff = _bottom - _top;

        // 위 계산을 통해서 (꼭 사각형을 직접 만들진 않았지만...)
        // 가상의 사각형을 만들기 위한 재료와 정보를 모두 얻었다

        // 여기서 가상 경계면 사이의 거리를 통해 사각형의 모양도 짐작할 수 있으니

        // 그 사각형이 납작하면 = xDiff가 더 크면 수평 충돌이 일어난 것 (상하방향)
        if (xDiff > yDiff)
        {
            // 수평충돌

            // 원래 의도 : 총알에서 "충돌"이라는 함수를 지정해서 불러오는 거지만

            float currentAngle = bullet->Angle();

            bullet->SetStat((PHI * 2) - currentAngle, bullet->Speed());
            // 호도  = 반지름, 호도 곱하기 원주율 = 호(와 호의 각도)
            // 호도 곱하기 원주율 곱하기 2 = 원 (360도)
        }
        else
        {
            // 수직충돌
            float currentAngle = bullet->Angle();

            bullet->SetStat(PHI - currentAngle, bullet->Speed());
        }
    }
};


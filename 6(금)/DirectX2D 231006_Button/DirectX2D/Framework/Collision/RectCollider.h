#pragma once

// 렉트 콜라이더 : 콜라이더 클래스를 받아서 사각형에 다른 도형이 겹쳤을 때를 계산하려는 클래스

class RectCollider : public Collider
{
public:

    // 사격형에 부딪친 게 원이었을 경우, 해당 원과 사각형의 정보를 판별하기 위한 저장용 구조체
    struct ObbDesc // O : 원, BB : 사각형을 나타내는 기호의 형태 중 하나, AA, BB, CC등..., Desc : descript, 설명, 해명, 분석
    {
        Vector2 position;
        Vector2 axis[2];
        Vector2 halfSize;
    };

public:
    RectCollider(Vector2 size);
    ~RectCollider() = default;

    // 콜라이더에 있던 추상함수를 여기서 오버라이드
    virtual bool IsPointCollision(Vector2 point) override;
    virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
    virtual bool IsCircleCollision(CircleCollider* circle) override;

    //본 콜라이더(사각형의 콜라이더 = 자기도 사각형) 정보
    Vector2 Size() { return size * GlobalScale(); }
    Vector2 Half() { return Size() * 0.5f; }

    Vector2 LeftTop();
    Vector2 LeftBottom();
    Vector2 RightTop();
    Vector2 RightBottom();

    float L();
    float R();
    float T();
    float B();

    ObbDesc GetObb();

private:

    //구체적인 경우의 수에 따른 충돌 판별 함수

    //AABB : AA라는 사각형과 BB라는 사각형이 만난 경우, OBB : 원 O와 사각형 BB가 만난 경우
    bool IsAABB(RectCollider* rect, Vector2* overlap);
    bool IsOBB(RectCollider* rect);

    // 둘의 추정 가능한 위치와 실제 도형의 간극이 생겼는가?
    bool IsSeperate(Vector2 sperateAxis, ObbDesc box1, ObbDesc box2);

private:
    Vector2 size;

    ObbDesc obbDesc;
};
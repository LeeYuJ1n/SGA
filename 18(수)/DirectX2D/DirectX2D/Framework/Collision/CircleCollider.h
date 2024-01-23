#pragma once

class CircleCollider : public Collider
{
private:
    const UINT VERTEX_COUNT = 64; // 원을 모든 점을 정말로 다 조사하면 시간이 걸려서 작게 다각형으로 쪼개서 연산

public:
    //렉트와 마찬가지로 생성자 및 함수 오버라이드
    CircleCollider(float radius = 1.0f);
    ~CircleCollider() = default;

    virtual bool IsPointCollision(Vector2 point) override;
    virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
    virtual bool IsCircleCollision(CircleCollider* circle) override;

    //반지름
    float Radius() { return radius * max(GlobalScale().x, GlobalScale().y); }

private:
    float radius;
};
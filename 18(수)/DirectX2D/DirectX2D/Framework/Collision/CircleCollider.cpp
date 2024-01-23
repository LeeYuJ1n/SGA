#include "Framework.h"

//원 충돌을 규정하기 위한 콜라이더

CircleCollider::CircleCollider(float radius)
    : radius(radius)
{
    type = Type::CIRCLE;

    vertices.reserve(VERTEX_COUNT + 1);

    //각도에 따라 돌아가면서 64각형 만들기

    float theta = XM_2PI / VERTEX_COUNT; // 지정된 분할 수에 따라 360도를 나눠서 단위각 생성
    for (UINT i = 0; i <= VERTEX_COUNT; i++)
    {
        float x = cos(theta * i) * radius; //단위각마다 돌아가면서 버텍스 xy를 구한다
        float y = sin(theta * i) * radius;

        vertices.emplace_back(x, y);
    }

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(VertexPos), vertices.size());
}

bool CircleCollider::IsPointCollision(Vector2 point)
{
    float distance = Distance(point, GlobalPos());

    return distance < Radius();
}

bool CircleCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    return rect->IsCircleCollision(this);
    //winAPI와 마찬가지로, 원/사각 충돌은 그냥 사각 쪽에 함수를 떠넘긴다
}

//원끼리 충돌은 그냥 반지름 길이 합보다 거리가 멀면 충돌 아님
bool CircleCollider::IsCircleCollision(CircleCollider* circle)
{
    float distance = Distance(circle->GlobalPos(), GlobalPos());

    return distance < Radius() + circle->Radius();
}

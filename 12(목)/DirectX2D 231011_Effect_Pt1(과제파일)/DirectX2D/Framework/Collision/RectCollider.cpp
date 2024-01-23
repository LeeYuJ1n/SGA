#include "Framework.h"

RectCollider::RectCollider(Vector2 size)
    : size(size)
{
    type = Type::RECT;

    Vector2 halfSize = size * 0.5f;

    vertices.emplace_back(-halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, +halfSize.y);

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(VertexPos), vertices.size());
}

// 행렬에 적용한 xy 포인트가 도형 안에 있는지를 판별하는 것
// = winAPI 때의 "사각형 경계 안에 점이 있는가?"와 의미가 같다
// 원이냐 아니냐를 따질 필요가 없어서 이쪽이 좀 더 범용 활용 가능
bool RectCollider::IsPointCollision(Vector2 point)
{
    Matrix invWorld = XMMatrixInverse(nullptr, world);

    point *= invWorld;

    Vector2 half = size * 0.5f;

    return abs(point.x) < half.x && abs(point.y) < half.y;
}

//위 함수의 대안, 벡터 연산 없이 직접 점 판별을 하는 것
//bool RectCollider::IsPointCollision(Vector2 point)
//{
//    ObbDesc obb = GetObb(); // <- 점 판별을 한다면서 원과 사각형 충돌 정보는 왜?
//
//    // ...는 winAPI 때와 마찬가지로, 원과 사각형의 충돌 연산에서 마지막에 점 충돌이 계산되어야 할 수 있으니까
//
//    Vector2 direction = obb.position - point;
//
//    float d = abs(Dot(direction, obb.axis[0]));
//
//    if (d > obb.halfSize.x) return false;
//
//    d = abs(Dot(direction, obb.axis[1]));
//
//    if (d > obb.halfSize.y) return false;
//
//    return true;
//}

// 렉트간의 콜리전 : 오버랩 방향도 같이 판별
bool RectCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    if (overlap)
        return IsAABB(rect, overlap); //AABB 함수를 호출

    return IsOBB(rect);
}

// 사각형과 원의 충돌 : 여기서 경우의 수
// 십자가 영역 안에 원이 들어와 있는가? 있는 경우 없는 경우 각자 계산
bool RectCollider::IsCircleCollision(CircleCollider* circle)
{
    ObbDesc obb = GetObb();

    Vector2 direction = obb.position - circle->GlobalPos();

    float x = abs(Dot(direction, obb.axis[0]));
    float y = abs(Dot(direction, obb.axis[1]));

    if (x > obb.halfSize.x + circle->Radius()) return false;
    if (y > obb.halfSize.y + circle->Radius()) return false;

    if (x < obb.halfSize.x) return true;
    if (y < obb.halfSize.y) return true;

    Vector2 temp = Vector2(x, y) - obb.halfSize;

    return circle->Radius() > temp.Length();
}

// 렉트 콜라이더의 세부 정보 구하기
Vector2 RectCollider::LeftTop()
{
    Vector2 edge = Vector2(-size.x, +size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::LeftBottom()
{
    Vector2 edge = Vector2(-size.x, -size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::RightTop()
{
    Vector2 edge = Vector2(+size.x, +size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::RightBottom()
{
    Vector2 edge = Vector2(+size.x, -size.y) * 0.5f;

    return edge * world;
}

float RectCollider::L()
{
    float minLeft = min(LeftTop().x, LeftBottom().x);
    float minRight = min(RightTop().x, RightBottom().x);

    return min(minLeft, minRight);
}

float RectCollider::R()
{
    float maxLeft = max(LeftTop().x, LeftBottom().x);
    float maxRight = max(RightTop().x, RightBottom().x);

    return max(maxLeft, maxRight);
}

float RectCollider::T()
{
    float maxTop = max(LeftTop().y, RightTop().y);
    float maxBottom = max(LeftBottom().y, RightBottom().y);

    return max(maxTop, maxBottom);
}

float RectCollider::B()
{
    float minTop = min(LeftTop().y, RightTop().y);
    float minBottom = min(LeftBottom().y, RightBottom().y);

    return min(minTop, minBottom);
}

//원과 사격형이 부딪치면 나오는 정보 기록
RectCollider::ObbDesc RectCollider::GetObb()
{
    obbDesc.position = GlobalPos();
    obbDesc.halfSize = Half();

    obbDesc.axis[0] = Right();
    obbDesc.axis[1] = Up();

    return obbDesc;
}

// 사각형 둘이 부딪쳤을 때 부딪쳤다는 사실 자체와 부딪친 방향 조사
bool RectCollider::IsAABB(RectCollider* rect, Vector2* overlap)
{
    Vector2 halfSize = Size() * 0.5f;

    float minRight = min(R(), rect->R());
    float maxLeft = max(L(), rect->L());
    float minTop = min(T(), rect->T());
    float maxBottom = max(B(), rect->B());

    overlap->x = minRight - maxLeft;
    overlap->y = minTop - maxBottom;

    if (overlap->x > 0 && overlap->y > 0)
        return true;

    return false;
}

bool RectCollider::IsOBB(RectCollider* rect)
{
    ObbDesc obbA = GetObb();
    ObbDesc obbB = rect->GetObb();

    if (IsSeperate(obbA.axis[0], obbA, obbB)) return false;
    if (IsSeperate(obbA.axis[1], obbA, obbB)) return false;
    if (IsSeperate(obbB.axis[0], obbA, obbB)) return false;
    if (IsSeperate(obbB.axis[1], obbA, obbB)) return false;

    return true;
}

// 떨어졌는지 여부
bool RectCollider::IsSeperate(Vector2 sperateAxis, ObbDesc box1, ObbDesc box2)
{
    float d = abs(Dot(sperateAxis, box1.position - box2.position));

    Vector2 right = box1.axis[0] * box1.halfSize.x;
    Vector2 up = box1.axis[1] * box1.halfSize.y;

    float a = abs(Dot(sperateAxis, right)) + abs(Dot(sperateAxis, up));

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float b = abs(Dot(sperateAxis, right)) + abs(Dot(sperateAxis, up));

    return d > (a + b);
}
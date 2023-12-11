#include "Framework.h"

Rect::Rect(Vector2 pos, Vector2 size)
    : GameObject(pos), size(size)
{
}

Rect::Rect(float left, float top, float right, float bottom)
{
    pos.x = (left + right) * 0.5f;
    pos.y = (top + bottom) * 0.5f;

    size.x = abs(right - left);
    size.y = abs(bottom - top);
}

void Rect::Render(HDC hdc)
{
    if (!isActive)
        return;

    int left = (int)(pos.x - size.x * 0.5f);
    int right = (int)(pos.x + size.x * 0.5f);
    int top = (int)(pos.y - size.y * 0.5f);
    int bottom = (int)(pos.y + size.y * 0.5f);

    Rectangle(hdc, left, top, right, bottom);
}

bool Rect::IsCollision(const Vector2& point) const
{
    if (!isActive)
        return false;

    if (point.x > Left() && point.x < Right())
    {
        if (point.y > Top() && point.y < Bottom())
            return true;
    }

    return false;
}

bool Rect::IsCollision(const Rect* rect) const
{
    if (!isActive) return false;
    if (!rect->isActive) return false;

    if (rect->Left() < Right() && rect->Right() > Left())
    {
        if (rect->Top() < Bottom() && rect->Bottom() > Top())
        {
            return true;
        }
    }

    return false;
}

bool Rect::IsCollision(const Circle* circle) const
{
    // 둘 다 활서화여야 진행되도록 return문 작성
    if (!isActive) return false;
    if (!circle->isActive) return false;
    // 상수화된 함수는 상수가 아닌 함수를 쓰지 못한다
    // 연관되지 못한 클래스에서는 (상수 함수를 쓰면 더, 더) 접근에 제한이 걸린다
    // (클래스 연관성 부여와 상관없이 타 클래스의 제한된 접근권 변수에 조금도 접근을 못한다)
    // 그러면 위에서는 왜? 위에서는 기본적으로 똑같은 클래스니까..(설계도를 공유하니까)

    // 해결 방법은 셋
    // 1. 함수를 상수가 아닌 걸로 바꾸거나 : 최선책. 그런데 이미 작성이 다 된 걸 한 번에 바꾸면 귀찮다
    // 2. Active()를 상수로 바꾸거나 " 차선책. 상수화된 함수는 나중에 수정하기도 힘들다
    // 3. 변수를 접근권을 public으로 바꿔버리면 된다 : 하책. 그런데 이미 작성이 될 대로 된 상황이면 가장 현실적으로 확실

    // 이 사각형과 원의 중심의 위치관계를 봐서...
    
    // 사각형이 중심이 되는 십자가 범위 안에 원의 중심이 들어와 있으면
    // 원의 무조건 최대거리에서 사각형과 충돌
    bool isCross = false; // 십자가 범위에 왔는가? (거짓으로 초기화)

    if (circle->pos.x > Left() && circle->pos.x < Right()) isCross = true;
    if (circle->pos.y > Top() && circle->pos.y < Bottom()) isCross = true;

    if (isCross)
    {
        // 원의 지름 크기를 벡터로 미리 지정 (지름이라고 명명)
        Vector2 diameter = { circle->GetRadius() * 2, circle->GetRadius() * 2 };
        Rect tempRect(circle->pos, diameter);
        // 원 지름을 크기로, 원 위치를 위치로 하는 가상의 사각형 만들기

        // 사각형끼리 충돌! ...하고 결과를 반환하면 된다
        // (원과 사각형의 충돌 시나리오 #2 : 십자가 범위 수행)
        return this->IsCollision(&tempRect);
    }
    else
    {
        // 시나리오 #1 : 십자가 범위 밖에 원이 있는 경우
        // → 원과 사각형의 꼭기점이 만나야 하는 경우

        // 사각형의 꼭지점 정보를 따오기
        Vector2 vertex[4]; // vertex : 꼭지점
        vertex[0] = { Left(), Top() };
        vertex[1] = { Left(), Bottom() };
        vertex[2] = { Right(), Top() };
        vertex[3] = { Right(), Bottom() };

        // 꼭지점을 반복문으로 돌려서
        for (Vector2 point : vertex)
        {
            // 원과 점이 충돌한다면
            if (circle->IsCollision(point))
            {
                return true; // 참반환
            }
        }
    }
    // 여기까지 오면 1. 십자가 범위도 아니고 2. 꼭지점과 원이 만나지도 않은 것
    // → 전혀 안 겹친 것

    return false;
}

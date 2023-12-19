#pragma once

class Rect;
class Circle;

class GameObject
{
public:
    GameObject() = default;
    GameObject(Vector2 pos) : pos(pos) {}
    ~GameObject() = default;

    virtual void Render(HDC hdc) = 0;

    virtual bool IsCollision(const Vector2& point) const = 0;
    virtual bool IsCollision(const Rect* rect) const = 0;
    virtual bool IsCollision(const Circle* circle) const = 0;

    Vector2& Pos() { return pos; }
    bool& Active() { return isActive; }

// protected: // ← 접근권 제한을 준 것. 기본적으로 타 클래스에서 접근 불가
              //   연관성이 있는 클래스끼리도 상수화된 함수를 통해서는 접근 불가
public:       // ← 접근권 제한 없음. 이제 어디서든 호출 가능. 당연히 보안은 약해진다
    bool isActive = true;

    Vector2 pos;
};
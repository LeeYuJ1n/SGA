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

protected:
    bool isActive = true;

    Vector2 pos;
};
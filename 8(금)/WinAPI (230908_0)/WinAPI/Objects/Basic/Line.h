#pragma once

class Line : public GameObject
{
public:
    Line() = default;
    Line(Vector2 start, Vector2 end);

    virtual void Render(HDC hdc) override;

    virtual bool IsCollision(const Vector2& point) const override;
    virtual bool IsRectCollision(const Rect* rect) const override;
    virtual bool IsCircleCollision(const Circle* circle) const override;

public:
    Vector2 end;
};
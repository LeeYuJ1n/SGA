#pragma once

class Circle : public GameObject
{
public:
    Circle() = default;
    Circle(Vector2 pos, float radius);

    virtual void Render(HDC hdc) override;

    virtual bool IsCollision(const Vector2& point) const override;
    virtual bool IsCircleCollision(const Circle* circle) const override;
    virtual bool IsRectCollision(const Rect* rect) const override;

    float GetRadius() const { return radius; }

protected:
    float radius = 0.0f;
};
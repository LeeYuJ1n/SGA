#pragma once

class Circle;

class Rect : public GameObject
{
public:
    Rect() = default;
    Rect(Vector2 pos, Vector2 size);
    Rect(float left, float top, float right, float bottom);
    
    virtual void Render(HDC hdc) override;

    virtual bool IsCollision(const Vector2& point) const override;
    virtual bool IsCollision(const Rect* rect) const override;
    virtual bool IsCollision(const Circle* circle) const override;

    float Left() const { return pos.x - size.x * 0.5f; }
    float Right() const { return pos.x + size.x * 0.5f; }
    float Top() const { return pos.y - size.y * 0.5f; }
    float Bottom() const { return pos.y + size.y * 0.5f; }
        
    Vector2 GetSize() const { return size; }    

protected:    
    Vector2 size;    
};
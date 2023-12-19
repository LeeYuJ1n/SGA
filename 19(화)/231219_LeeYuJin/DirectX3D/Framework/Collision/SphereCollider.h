#pragma once

class SphereCollider : public Collider
{
    // 구체 콜라이더 : 3D에서 원 콜라이더에 대응하는 충돌체 클래스
    //                박스와 비슷하게 중심, ( 구를 위한 ) 반지름, 
    //                ( DX에서 원을 삼각형으로 묘사할 때 쓴 ) 
public:
    SphereCollider(float radius = 1.0f, UINT stackCount = 8, UINT sliceCount = 16);
    ~SphereCollider() = default;

    virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact) override;

    virtual bool IsBoxCollision(BoxCollider* collider) override;
    virtual bool IsSphereCollision(SphereCollider* collider) override;

    float Radius() { return radius * max(GlobalScale().x, max(GlobalScale().y, GlobalScale().z)); }

private:
    virtual void MakeMesh() override;

    float radius;

    UINT stackCount, sliceCount;
};
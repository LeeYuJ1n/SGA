#pragma once

class SphereCollider : public Collider
{
    // ��ü �ݶ��̴� : 3D���� �� �ݶ��̴��� �����ϴ� �浹ü Ŭ����
    //                �ڽ��� ����ϰ� �߽�, ( ���� ���� ) ������, 
    //                ( DX���� ���� �ﰢ������ ������ �� �� ) 
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
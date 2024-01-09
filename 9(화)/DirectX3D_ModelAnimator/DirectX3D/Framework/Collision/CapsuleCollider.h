#pragma once

class CapsuleCollider : public Collider
{
    // Collider��(��) ���� ��ӵ�
    virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact) override;
    virtual bool IsBoxCollision(BoxCollider* collider) override;
    virtual bool IsSphereCollision(SphereCollider* collider) override;
    virtual bool IsCapsuleCollision(CapsuleCollider* collider) override;
    virtual void MakeMesh() override;
};
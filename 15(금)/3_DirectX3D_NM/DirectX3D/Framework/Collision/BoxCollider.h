#pragma once

class BoxCollider : public Collider
{
	// 3D �浹ü�� ��ӹ��� "�ڽ�" ���� �浹ü

	// �ڽ� �浹���� �ʿ��� ��
	// 1. �ڽ� �����
	// 2. �ڽ� ���ۿ� �ʿ��� ����( = ũ��)
	// 3. (WinAPI, DX2D ���� ����) �浹 ����� ��Ȳ�� ����ϱ� ���� ������ (�Լ��� �ְų� ���� �����ϰų� ����ü�� ����ų�)
	//    -> "AABB"�� "OBB" : �ڽ������� �浹�� AABB, ������ �浹�� OBB�� ��Ī

public:
	BoxCollider(Vector3 size = { 1, 1, 1});
	~BoxCollider() = default;

	// OBB ��Ͽ� ����ü
	struct ObbDesc
	{
		Vector3 pos;      // ��ġ
		Vector3 axis[3];  // �� ����
		Vector3 halfSize; // ��� ���Ǹ� ���� ����ũ��
	};

	// OBB�� �߻��� ��� ����ϱ� ���� �Լ�
	void GetObb(ObbDesc& obbDesc);

	// AABB�� �ϴ� ����(�ϳ��ϳ� ����� ���� �þ�� ���� ����)

	// �Ǻ��ϴ� ��� ����
	virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact = nullptr) override;
	virtual bool InSphereCollision(class SphereCollider* collider) override;
	virtual bool IsBoxCollision(class BoxCollider* collider) override;

	// ���� �ٸ� ��� ����� �����ϱ� ���� ���� �Լ�
	bool IsSeperateAxis(Vector3 D, Vector3 axis, ObbDesc box1, ObbDesc box2);

	// (�θ� �������̽����� ����) ��� �����
	virtual void MakeMesh() override;

	// ���� ������(��� ����, ������� ������ ��찡...)
	Vector3 size;
};


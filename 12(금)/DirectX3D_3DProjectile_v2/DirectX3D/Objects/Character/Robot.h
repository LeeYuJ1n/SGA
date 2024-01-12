#pragma once

class Robot
{	
private:
	// enum class STATE // <- �� ��� Ŭ������ "STATE" ����� ����
	                    //    ���� : enum ���� �ߺ��� ��, �ݵ�� �ǵ��� ���� ȣ���� �� �ִ�
	                    //    ���� : Ÿ�ڰ� ������ ���� �ӵ��� (���� ���� ����) ������

	enum State
	{
		STAND_UP,
		WALK,
		RUN,
		HIT,
		DTING
		// ���¸��� ���� : fbx�� Ŭ���� (ù ��¥ �빮��, ������ �ҹ���. �� : "Dying")
	};

public:
	Robot(Transform* transform); // ���ϸ� �ν��Ͻ� ����
	~Robot();

	void Update();
	void Render();

	SphereCollider* GetCollider() { return collider; }
	Transform* GetTransform() { return transform; }

private:
	// TODO : ���� �ȿ��� �߰��� �Ŷ�� ���⿡ ��� ���� �߰��� ��
	//        (�ۿ��� ����� �׷� �ʿ� ����)

	Transform* transform;
	SphereCollider* collider;

	float moveSpeed = 30.0f;

	Vector3 Velocity; // ������ �ᵵ ������ �ƴϾ �Ǵ� ���� �ӵ�
	                  // ������ ��, �ƴ� �� �� ���� ��� ����
};


#pragma once

class TestActor : public SphereCollider
{
	// �׽�Ʈ ĳ���� ( ��ü �浹ü�κ��� ��� ���� )
	// ��ǥ : ���۰� �ּ����� ��ȣ�ۿ��� ������ 3D ��ü �����
private:
	const float GRAVITY = 9.8f * 10; // �߷� ( ĳ���Ϳ� �������� �ʴ� ���� ) ( Value : 9.8 ) : �ʿ��ϸ� ��ũ�η� ���� �ϴ�

public:
	TestActor();
	~TestActor();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	void SetLevel(TerrainEditor* stage) { level = stage; }

private:
	void Control();
	void Jump();

private:
	float moveSpeed = 10.0f;   // �����̴� �ӷ� ( Value : 10.0 )
	float rotSpeed  = 5.0f  ;  // ȸ�� �ӷ� ( Value : 5.0 )
	float jumpPower = 20.0f;   // ���� �ɷ� ( Value : 20.0 )
	float velocity  = 0.0f;    // ������ �ӷ� ( ��Ȳ ) ( Value : 0.0 )

	bool isJump = false; // ���� ���� ���ΰ�?

	// ���ۿ���� ����
	Vector3 prevMousePos; // ���� �ֱ��� ���콺 ������ ��ġ ( ���� )

	// ���� ���� ( ���� : �ͷ��� ������ �������� -> ���߿� �ʿ��ϸ� ���� )
	TerrainEditor* level = nullptr;

	// ���߿� UI�� �߰��Ǹ� �� �ؿ�
};


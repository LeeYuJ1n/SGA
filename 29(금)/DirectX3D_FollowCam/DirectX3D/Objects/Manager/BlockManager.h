#pragma once

class BlockManager : public Singleton<BlockManager>
{
	// ��� �Ŵ��� ( ť�긦 �������� �ϴ� "���" ������ )

private:
	friend class Singleton;

public:
	BlockManager() = default;
	~BlockManager();

	void Update();
	void Render();

	// ���(��) �����ϱ�
	void CreateBlock(UINT width, UINT height);

	// ����� �׾Ƽ� ���� (��� Ȯ�α��� �ϱ� ���� boolean) 
	bool buildBlock(Cube* block);

	// �б� (MValue : collider)
	void Push(Collider* collider);

	// �浹 üũ (�� �� ����� ���� ���)
	Cube* GetCollisionBlock();

	// ����� ���� ���
	float GetHeight(Vector3& pos);

private:
	list<Cube*> blocks; // <- ���� ���� ��� �߰��� �� ������ �����ǵ��� �ϱ� ���ؼ�
};


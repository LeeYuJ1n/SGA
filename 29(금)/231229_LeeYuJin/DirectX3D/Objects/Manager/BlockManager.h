#pragma once

class BlockManager : public Singleton<BlockManager>
{
    // ��� �Ŵ��� (ť�긦 �������� �ϴ� "���" ������)

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
    bool BuildBlock(Cube* block);

    // �б�
    void Push(Collider* collider);

    // �浹 üũ (�� �� ����� ���� ���)
    Cube* GetCollisionBlock();

    // ����� ���� ���
    float GetHeight(Vector3& pos);

private:
    list<Cube*> blocks; // <-���� ���� ��� �߰��� �� ������ �����ǵ��� �ϱ� ���ؼ�
};


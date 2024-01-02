#pragma once

class TestActor : public SphereCollider
{
    // �׽�Ʈ ĳ���� (��ü �浹ü�κ��� ��� ����)
    // : ���۰� �ּ����� ��ȣ�ۿ��� ������ 3D ��ü �����

private:
    const float GRAVITY = 9.8f * 10.0f;        // �߷� (ĳ���Ϳ� �������� ���� ����) : �ʿ��ϸ� ��ũ�� ���� �ϴ� ��

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
    float moveSpeed = 10.0f;    // �����̴� �ӷ� (����)
    float rotSpeed = 5.0f;      // ȸ�� �ӷ�
    float jumpPower = 20.0f;    // ���� �ɷ�

    float velocity = 0.0f;      // ������ �ӷ� (��Ȳ)
    bool isJump = false;        // ���� ���� ���ΰ�?

    //���� ���� ����
    Vector3 prevMousePos;       // ���� �ֱ��� ���콺 ������ ��ġ (����)

    //�������� (���� : �ͷ��� ������ �������� -> ���߿� �ʿ��ϸ� ����)
    TerrainEditor* level = nullptr;

    //���߿� UI�� �߰��Ǹ� �� �ؿ�

    //���ؼ�
    Quad* crosshair;
};


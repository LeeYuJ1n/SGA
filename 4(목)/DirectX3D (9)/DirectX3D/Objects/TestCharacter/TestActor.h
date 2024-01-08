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

    // ���� ���ÿ� �Լ���
    void SetLevel(TerrainEditor* stage) { level = stage; }          // �ͷ����� ���� ������ �����ϰ�
    void UseBlockManager(bool value) { usingBlockManager = value; } // ��ϸŴ��� �̱��� �� �Ÿ� ����ϰ�

private:
    void Control();
    void Jump();

private:
    float moveSpeed = 10.0f;    // �����̴� �ӷ� (����)
    float rotSpeed = 5.0f;      // ȸ�� �ӷ�
    float jumpPower = 20.0f;    // ���� �ɷ�

    float velocity = 0.0f;      // ������ �ӷ� (��Ȳ)
    bool isJump = false;        // ���� ���� ���ΰ�?

    // ���� ���� ����
    Vector3 prevMousePos;       // ���� �ֱ��� ���콺 ������ ��ġ (����)

    // �������� (���� : �ͷ��� ������ �������� -> ���߿� �ʿ��ϸ� ����)
    TerrainEditor* level = nullptr;

    // �������� V2 : ��ϸŴ���
    bool usingBlockManager = false;

    // ���߿� UI�� �߰��Ǹ� �� �ؿ�

    // ���ؼ� (���� ����)
    // Quad* crosshair;

    //���� UI
    ActorUI* ui;

    // UI ���ۿ� ���� ���� ��ġ ���� ����
    // POINT clickCenterPos = { CENTER_X, CENTER_Y };                 // �̸� ������ ���� ��ũ�ΰ� ���
    // POINT clickCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT / 2 };      // 2�� ������
    // POINT clickCenterPos = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f}; // 0.5�� ���ϱ�
    POINT clickCenterPos = { WIN_WIDTH >> 1, WIN_HEIGHT >> 1 };       // ��Ʈ �� ĭ �б�
};


#include "Framework.h"

TestActor::TestActor()
{
    Pos() = { 5, 5, 5 }; // ���� �ȿ� �� �� �ֵ��� �̸� ��ǥ�� �ణ "��"���� ������ֱ�

    //���ؼ� ����
    crosshair = new Quad(L"Textures/UI/cursor.png");
    crosshair->Pos() = { CENTER_X, CENTER_Y, 0 };

    // �ӽ� �ڵ� : ���ؼ��� �÷��̾ �������� �����̵���
    //crosshair->SetParent(this); // �θ� ���ϱ� : ���� �ڵ� ���������� �� �ʿ����� ������, �ǹ̻� ���
    //crosshair->Scale() *= 0.05f; //�ʹ� ũ�� ������ �ʰ�

    crosshair->UpdateWorld();
}

TestActor::~TestActor()
{
    // ���� ������ �ν��Ͻ��� �Ҵ�Ǹ� ���⼭ ����
}

void TestActor::Update()
{
    Control(); // ��Ʈ�� �ϱ�
    Jump();    // ������ ������ ������ �ϱ�

    UpdateWorld(); // �浹ü, (�ִٸ�) �׷���, Ʈ������ ���� ���� ������Ʈ�ϱ�

    // �ӽ� �ڵ� : ����Ʈ ���� �ذ����
    // �÷��̾� ��ġ, ���� ���� �������� ���ؼ� �̵���Ű��
    //crosshair->Pos() = Pos() + CAM->Forward() * 10.0f;
    //crosshair->Rot() = CAM->Rot(); // �þ� ���� ȸ���ϵ���
    //crosshair->UpdateWorld();

    // 2D �̹����� 3D ��� �������� �ۼ� o, ��µ� �Ϻ� ����
    // -> 2D �̹����� Ȱ���� ĳ���� ����� Ȯ�嵵 ����

    // -> �浹�� ���� ��ȣ�ۿ� / ������ �ڷᱸ���� Ȱ���� �κ��丮 / 2D �̹������� ����
    // -> �Ⱦ� �κ��丮
}

void TestActor::Render()
{
    Collider::Render(); // �ڱ�� ���� ������ �׷��� ����
}

void TestActor::PostRender()
{
    // �� �� UI�� �ִٸ� ���⼭ �ۼ��ؼ� ���
    // �� : �Ӹ� �� �̸�ǥ, ü�¹�, ���� �����̸� ���ؼ�...
    crosshair->Render();
}

void TestActor::GUIRender()
{
    // ����� �гο��� ����ϰ� ���� �� �ִٸ� ���⼭ �ۼ�
}

void TestActor::Control()
{
    if (KEY_PRESS('W'))
        // pos.x += UP() .... �� 3���� ����
        Pos() += Forward() * moveSpeed * DELTA;
    if (KEY_PRESS('S'))
        Pos() += Back() * moveSpeed * DELTA; // Backward�� ������ ���� Back�̶�� ����
    if (KEY_PRESS('A'))
        Pos() += Left() * moveSpeed * DELTA;
    if (KEY_PRESS('D'))
        Pos() += Right() * moveSpeed * DELTA;

    // ������ �ƴϸ� �����̽� ������ �� ������ �����ϱ�
    if (!isJump && KEY_DOWN(VK_SPACE))
    {
        velocity = jumpPower; // ���� �ӷ� = ������
        isJump = true;
    }

    // ���콺 Ŀ���� �Ź� �Է� ��ȭ �����ؼ� ���� �Ǻ��ϱ�
    Vector3 delta = mousePos - prevMousePos;
    prevMousePos = mousePos; // ���� �ֱ� Ŀ�� ��ġ �ٽ� ����

    // ī�޶� ���콺�� �����ϱ� (���� ī�޶� ��� �ʿ�)
    CAM->Rot().y += delta.x * rotSpeed * DELTA;
    // ���콺 �¿� �̵� = ī�޶��� ������ ���� ȸ�� = �¿� ȸ��
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
    // ���콺 ���� �̵� = ī�޶��� ������ ���� ȸ�� = ���� ȸ��

    // ī�޶��� �����ӿ� ĳ���͸� ����ȭ
    Rot().y = CAM->Rot().y;

// ���� �ۼ��� ���� ī�޶� ���ؼ� �����ϸ鼭...

// 1. ���� ī�޶�� ���� ī�޶� ������ ��۵� �� �ְ� �غ��ô�.
// 2. ���� ī�޶� ���¿����� ���� ������ �� �� �ְ� �غ��ô�.
// 3. ���� ī�޶� ���¿����� �÷��̾� ������ �� �� �ְ� �غ��ô�.
}

void TestActor::Jump()
{
    velocity -= GRAVITY * DELTA; // �� ��긶�� �ӷ¿��� �߷� ����

    Pos().y += velocity * DELTA;

    float height = 0; //�⺻ ���� = 0
    if (level)        //������ �ִٸ�
        height = level->GetHeightByPos(Pos()); // �ڱⰡ �ִ� ��ġ�� �������� ���� ���� ���ϱ�

    //����� ������ ������ ���� ����
    if (Pos().y - Radius() < height) // ĳ���� ��ġ - ��ü(�浹ü) ���������� ���� �� ���� ��Ȳ
        // = ���� ���� ����
    {
        Pos().y = height + Radius();
        
        velocity = 0;
        isJump = false;
    }
}
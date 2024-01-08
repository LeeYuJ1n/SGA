#include "Framework.h"

TestActor::TestActor()
{
    Pos() = { 5, 5, 5 }; // ���� �ȿ� �� �� �ֵ��� �̸� ��ǥ�� �ణ "��"���� ������ֱ�

    // winAPI ���� �Լ� : ����� ������ ��ũ���� �������ִ� ���
    ClientToScreen(hWnd, &clickCenterPos);
    // ShowCursor(false);
    // �� ���� �߿� Ŀ���� ���� ������ ����

    ui = new ActorUI();
}

TestActor::~TestActor()
{
    delete ui;
}

void TestActor::Update()
{
    Control(); // ��Ʈ�� �ϱ�
    Jump();    // ������ ������ ������ �ϱ�

    UpdateWorld(); // �浹ü, (�ִٸ�) �׷���, Ʈ������ ���� ���� ������Ʈ�ϱ�

    // UI ����
    // ��Ŭ�� : �� �Լ�   -> ��� �������� ȣ��
    // ��Ŭ�� : ���� �Լ� -> �ױ� ȣ��
    if (KEY_DOWN(VK_LBUTTON))
        ui->Pick();

    if (KEY_DOWN(VK_RBUTTON))
        ui->Build();

    ui->Update();
    
}

void TestActor::Render()
{
    Collider::Render(); // �ڱ�� ���� ������ �׷��� ����
}

void TestActor::PostRender()
{
    // �� �� UI�� �ִٸ� ���⼭ �ۼ��ؼ� ���
    // �� : �Ӹ� �� �̸�ǥ, ü�¹�, ���� �����̸� ���ؼ�...
    // crosshair->Render();

    ui->PostRender();
}

void TestActor::GUIRender()
{
    ui->GUIRender();
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


    // ---------------------------------

    // �κ��丮�� ��� ��ȣ�ۿ��� �ִٸ� ���⼭ �ۼ�

}

void TestActor::Jump()
{
    velocity -= GRAVITY * DELTA; // �� ��긶�� �ӷ¿��� �߷� ����

    Pos().y += velocity * DELTA;

    float height = 0; //�⺻ ���� = 0
    if (level)        //������ �ִٸ�
        height = level->GetHeightByPos(Pos()); // �ڱⰡ �ִ� ��ġ�� �������� ���� ���� ���ϱ�

    if (usingBlockManager)
        height = BlockManager::Get()->GetHeight(Pos());

    //����� ������ ������ ���� ����
    if (Pos().y - Radius() < height) // ĳ���� ��ġ - ��ü(�浹ü) ���������� ���� �� ���� ��Ȳ
        // = ���� ���� ����
    {
        Pos().y = height + Radius();
        
        velocity = 0;
        isJump = false;
    }
}
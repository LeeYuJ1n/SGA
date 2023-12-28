#include "Framework.h"

TestActor::TestActor()
{
	Pos() = { 5, 5, 5 }; // ���� ������ �� �� �ֵ��� �̸� ��ǥ�� �ణ "��"���� ������ֱ�
}

TestActor::~TestActor()
{
	// ���� ������ �ν��Ͻ��� �Ҵ�Ǹ� ���⼭ ����
}

void TestActor::Update()
{
	Control();     // ��Ʈ�� �ϱ�
	Jump();        // ������ ������ ������ �ϱ�
	UpdateWorld(); // �浹ü, ( �ִٸ� ) �׷���, Ʈ������ ���� ���� ������Ʈ�ϱ�
}

void TestActor::Render()
{
	Collider::Render(); // �ڱ�� ���� ������ �׷��� ����
}

void TestActor::PostRender()
{
	// �� �� UI�� �ִٸ� ���⼭ ���
	// �� : �Ӹ� �� �̸�ǥ, ü�¹�, ���� �����̸� ���ؼ�
}

void TestActor::GUIRender()
{
	// ����� �гο��� ��¤��� ���� �� �ִٸ� ���⼭ �ۼ�
}

void TestActor::Control()
{
	if (KEY_PRESS('W'))
	{
		// pos.x += UP() ... �� 3���� ����
		Pos() += Forward() * moveSpeed * DELTA;
	}

	if (KEY_PRESS('S'))
	{
		Pos() += Back() * moveSpeed * DELTA; // Backward�� ������ ���� Back�̶�� ����
	}

	if (KEY_PRESS('A'))
	{
		Pos() += Left() * moveSpeed * DELTA;
	}

	if (KEY_PRESS('D'))
	{
		Pos() += Right() * moveSpeed * DELTA;
	}

	// ���࿡ ������ �����̽� ������ �� ������ �����ϱ�
	if (!isJump && KEY_DOWN(VK_SPACE))
	{
		velocity = jumpPower; // ���� �ӷ� = ������
		isJump   = true;
	}

	// ���콺 Ŀ���� �Ź� �Է� ��ȭ �����ؼ� ���� �Ǻ��ϱ�
	Vector3 delta = mousePos - prevMousePos;
	prevMousePos = mousePos; // ���� �ֱ� Ŀ�� ��ġ �ٽ� ����

	// ī�޶� ���콺�� �����ϱ� ( ���� ī�޶� ��� �ʿ� )
}

void TestActor::Jump()
{
	velocity -= GRAVITY * DELTA; // �� ��긶�� �ӷ¿��� �߷� ����
	Pos().y += velocity * DELTA;

	float height = 0; // �⺻ ���̴� 0

	if (level) // ������ �ִٸ�
	{
		height = level->GetHeightByPos(Pos()); // �ڱⰡ �ִ� ��ġ�� �������� ���� ���� ���ϱ�
	}

	// ����� ������ ������ ���� ����
	if (Pos().y - Radius() < height) // ĳ���� ��ġ - ��ü ( �浹ü ) ���������� ���� �� ���� ��Ȳ
									 // = ���� ���� ����
	{
		Pos().y = height + Radius();
		velocity = 0;
		isJump = false;
	}
}

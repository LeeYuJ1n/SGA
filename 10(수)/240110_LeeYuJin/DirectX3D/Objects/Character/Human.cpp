#include "Framework.h"

Human::Human() : ModelAnimator("Human") // �θ� �� �����
{
	// ���� �б�
	ReadClip("Idle", 1);
	ReadClip("Run", 1);
	ReadClip("Jump", 1);

	// ���� ����
	crowbar = new Crowbar();
	crowbar->Load(); // ���� ���õ� ������ �ִ��� ���� ������ �б�

	// ���⸦ �տ� ���
	mainHand = new Transform(); // Ʈ�������� �ִٴ� �͸� ���ϱ�
	crowbar->SetParent(mainHand); // ���� ��ġ = �� ��
}

Human::~Human()
{
	delete crowbar;
	delete mainHand; // <- �̷��� ������ �Ǵ� ���� : �����ʹ� ������ �����Ͱ� ���ư��� �ʴ´�
	                 // ���� �� �ڸ��� ������� ���ɼ��� ���� ��
	                 // �׸��� �� "��"�� ��¥ �����ʹ� ���� ������ �� �ڸ��� ���� �ִ�
}

void Human::Update()
{
	// ������Ʈ���� �߿��� �� : 
	// 1. �� ���� �����ΰ�? (�������� ���� ���� �����ؾ� ��)
	// 2. �� ���� ��� �ִ°�? (�׷��� �ű⿡ ���Ⱑ ���� �״ϱ�)

	mainHand->SetWorld(GetTransformByNode(51)); // Ʈ�������� ���� �Ҵ��ϱ�
	// GetTransformByNode : �� �ִϸ����Ϳ��� ������� "��忡 �Ҵ�� Ʈ������ �޾ƿ���"
	// �Ű����� 51 : fbx ���� �������� �־��� ����� ����

	crowbar->Update();

	ModelAnimator::Update(); // �������μ��� ������Ʈ ���� ����
	                         // Ŭ�������� ������ ����Լ��� �ż� ���� �߻�

	Control();
	Jump();
}

void Human::Render()
{
	crowbar->Render();

	ModelAnimator::Render();
}

void Human::GUIRender()
{
	crowbar->GUIRender();

	ModelAnimator::GUIRender();
}

void Human::Control()
{
	if (KEY_DOWN('W') || KEY_DOWN('S') || KEY_DOWN('A') || KEY_DOWN('D'))
	{
		PlayClip(1); // WŰ�� ������ Walk ��� Ŭ�� ����
	}
	else if (KEY_UP('W') || KEY_UP('S'))
	{
		PlayClip(0); // WŰ�� �� ������ Standing ��� ����
	}
	
	if (KEY_PRESS('W'))
	{
		Pos() -= Forward() * moveSpeed * DELTA;
	}

	if (KEY_PRESS('A'))
	{
		Pos() += Left() * moveSpeed * DELTA;
		Rot().y -= 5.0f * DELTA;
	}

	if (KEY_PRESS('S'))
	{
		Pos() += Forward() * moveSpeed * DELTA;
	}

	if (KEY_PRESS('D'))
	{
		Pos() += Right() * moveSpeed * DELTA;
		Rot().y += 5.0f * DELTA;
	}
}

void Human::Jump()
{
	if (KEY_DOWN(VK_SPACE))
	{
		isJump = true;
	}
	
	// else if (KEY_UP(VK_SPACE))
	// {
	// 	isJump = false;
	// }

	if (isJump)
	{
		PlayClip(2);
		Pos() += Vector3().Up() * jumpVelocity * DELTA;
		jumpVelocity -= jumpForce * DELTA;

		if (Pos().y <= 0)
		{
			PlayClip(0);
			isJump = false;
			Pos().y = 0;
		}
	}
}

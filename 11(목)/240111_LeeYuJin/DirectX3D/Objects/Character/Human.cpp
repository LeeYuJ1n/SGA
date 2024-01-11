#include "Framework.h"

Human::Human() : ModelAnimator("Human") // �θ� �� �����
{
	model = new Model("Kunai");

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

	delete model;
}

void Human::Update()
{
	Control();

	// ������Ʈ���� �߿��� �� : 
	// 1. �� ���� �����ΰ�? (�������� ���� ���� �����ؾ� ��)
	// 2. �� ���� ��� �ִ°�? (�׷��� �ű⿡ ���Ⱑ ���� �״ϱ�)

	mainHand->SetWorld(GetTransformByNode(51)); // Ʈ�������� ���� �Ҵ��ϱ�
	// GetTransformByNode : �� �ִϸ����Ϳ��� ������� "��忡 �Ҵ�� Ʈ������ �޾ƿ���"
	// �Ű����� 51 : fbx ���� �������� �־��� ����� ����

	crowbar->Update();

	ModelAnimator::Update(); // �������μ��� ������Ʈ ���� ����
	                         // Ŭ�������� ������ ����Լ��� �ż� ���� �߻�
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
	if (KEY_DOWN('F'))
	{
		model->Pos().Up() += 
	}
}

void Human::Jump()
{
}

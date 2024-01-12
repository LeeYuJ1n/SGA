#include "Framework.h"

KunaiManager::KunaiManager()
{
	kunaiInstancing = new ModelInstancing("Kunai"); // ���� ���� �����ϴ� �ν��Ͻ� ����

	kunaies.reserve(SIZE); // ������ŭ ����

	FOR(SIZE)
	{
		Transform* transform = kunaiInstancing->Add(); // �ν��Ͻ̿� �� Ʈ������ �߰�
		transform->SetActive(false); // �ϴ� ��Ȱ��ȭ (�� ���ư�)
		Kunai* kunai = new Kunai(transform); // ���� ���� (�ν��Ͻ� ��) Ʈ�������� �Ű��� �� ���� ����
		kunaies.push_back(kunai); // ���� ���Ϳ� ���� ���� ����ü ���� Ŭ������ �߰�
	}
}

KunaiManager::~KunaiManager()
{
	// ���� �ν��Ͻ� ����� ���
	// ���� ���� ����ü Ŭ������ �����
	for (Kunai* kunai : kunaies)
	{
		delete kunai;
	}

	// ���� ���� �ν��Ͻ̵� �������� �����
	delete kunaiInstancing;
}

void KunaiManager::Update()
{
	kunaiInstancing->Update(); // ��(�� ���� Ʈ������) ������Ʈ

	for (Kunai* kunai : kunaies)
	{
		kunai->Update(); // ���� ���� �����͵� ������Ʈ
	}
}

void KunaiManager::Render()
{
	kunaiInstancing->Render(); // ��(�� ���� Ʈ������) ������Ʈ

	for (Kunai* kunai : kunaies)
	{
		kunai->Render(); // ���� ���� �����͵� ������Ʈ
	}
}

void KunaiManager::Throw(Vector3 pos, Vector3 dir)
{
	for (Kunai* kunai : kunaies)
	{
		// ��Ȱ��ȭ�� �Ƶ� �ͺ��� ���ʷ� ������
		if (!kunai->GetTransform()->Active())
		{
			kunai->Throw(pos, dir); // �Ű����� �״�� �����ؼ� �� ��� ������
			return; // �뵵�� �� ������ �״�� ����
		}
	}
}

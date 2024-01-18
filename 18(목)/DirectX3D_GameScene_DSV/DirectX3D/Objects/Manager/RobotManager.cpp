#include "Framework.h"

RobotManager::RobotManager()
{
	// �ν��Ͻ� (�� ���� ��) ����
	robotinstancing = new ModelAnimatorInstancing("Robot");
	robotinstancing->ReadClip("StandUp");
	robotinstancing->ReadClip("Walk");
	robotinstancing->ReadClip("Run");
	robotinstancing->ReadClip("Hit");
	robotinstancing->ReadClip("Dying");

	// �κ� �ν��Ͻ� ���� �ν��Ͻ̰� ����
	FOR(SIZE)
	{
		// �ν��Ͻ̿��� Ʈ�������� �߰��� �� �Ŵ��������� �Ҵ�
		Transform* transform = robotinstancing->Add();
		transform->SetActive(false); // ���� ���� ������ ������ ��ģ�� �ƴ϶� Ȱ��ȭ�� �� ��
		Robot* robot = new Robot(transform, robotinstancing, i); // ���� �ε��� i��°, ���� �ν��Ͻ��� ���� �����ϴ� �κ� ����
		robots.push_back(robot); // ���Ϳ� ���ٿ��� ���� �κ� �߰�
	}
}

RobotManager::~RobotManager()
{
	delete robotinstancing;

	for (Robot* robot : robots)
	{
		delete robot;
	}
}

void RobotManager::Update()
{
	// �浹 �������� ����
	Collision();

	// �ð� ����� üũ
	time += DELTA;

	if (time >= SPAWN_TIME) // �ð��� ����� ���ݿ� �����ϸ�
	{
		time -= SPAWN_TIME; // time�� ���� �߻��� ������ �����ϰ� ����� ������ �켱
		                    // ���� : ��ü�� �ð� ������ ���� ����
		                    // ���� : ������ �������� ��� �ұ�Ģ�� �����(���� ����)
							
		// time = 0;        // time�� ���� �߻��� ������ �����ϰ� ���� ������ �켱
		                    // ���� : ��ü�� ��Ģ���� ���� ȯ���� ���� ����
		                    // ���� : �ð� ������ ������ ������ �ִ�

		Spawn(); // �����
	}

	// �� ��ü�� ������Ʈ
	robotinstancing->Update();

	// �κ��� ��ü�鵵 ������Ʈ (��ü : ���赵�μ��� Ŭ���� + ������μ��� �ν��Ͻ��� ��Ī)
	for (Robot* robot : robots)
	{
		robot->Update();
	}
}

void RobotManager::Render()
{
	robotinstancing->Render();

	for (Robot* robot : robots)
	{
		robot->Render();
	}
}

void RobotManager::PostRender()
{
	for (Robot* robot : robots)
	{
		robot->PostRender();
	}
}

void RobotManager::SetTarget(Transform* target)
{
	this->target = target; // �Ŵ������� ǥ���� �켱 ����

	for (Robot* robot : robots)
	{
		robot->SetTarget(target); // �κ� �ϳ��ϳ��� ǥ���� ����
	}
}

bool RobotManager::IsCollision(Ray ray, Vector3& hitPoint)
{
	// �� �ܺο��� �����Ͱ� ���� ���� �浹 : �ܺ� ������
	// 1. ���콺 Ŭ��
	// 2. ȭ���� ���� �÷��̾��� / �÷��̾���� ����
	// + �Ŵ����� ������ �������� ���� ������ ���� �浹

	Contact contact;
	float minDistance = FLT_MAX;

	for (Robot* robot : robots)
	{
		// �κ� �浹ü�� ���� �� �浹 ���θ� �Ǻ��ؼ�
		if (robot->GetCollider()->IsRayCollision(ray, &contact))
		{
			// ������ �浹�߰� ������ �Ÿ��� ������ �ŵ��ؼ�
			if (contact.distance < minDistance)
			{
				// �ش� ������ ������ ������ �����ϰ� (hitPoint�� �Ҵ�)
				minDistance - contact.distance;
				hitPoint = contact.hitPoint;
			}
		}
	}

	// ã�Ƴ� �Ÿ��� �ʱⰪ���� �ǹ� �ְ� �������� �Ǻ�
	return minDistance != FLT_MAX; // FLT_MAX���� ���� ���� �����Ƿ�, �ٸ��ٸ� �и� ������ ��
}

void RobotManager::Collision()
{
	// �� �ǽð� ���� �浹���� : 
	// 1. ���� ���ο��� �����͵��� �־��� ��
	// 2. �ش� �����ͳ��� �浹 ���θ� �ݺ�����ϱ� ����

	for (Robot* robot : robots)
	{
		// ���ӿ��� �־��� ������, �Ŵ����� ���� ������ ��� �κ��� ��� ����
		// ����� ���� �浹ü�� �־��� �ִ�
		// + ���߿� �ʿ��ϸ� �������� �浹ü ���� �߰��� ���� �ִ�

		// ���̿� �κ��� �浹 ��
		if (KunaiManager::Get()->IsCollision(robot->GetCollider()))
		{
			robot->Hit();
			return; // �ݺ��� ���� -> ������Ʈ�� ������ ��� ���ư���
		}
	}
}

void RobotManager::Spawn()
{
	Vector3 dir; // ����
	dir.x = Random(-1.0f, 1.0f);
	dir.z = Random(-1.0f, 1.0f);

	// �Ŵ����� ���� ���� ǥ���� ���� ��ġ���� ��� ���� ������, ������ ������ ��Ҹ� ����
	// �Ÿ��� �����ϰų�, �Ÿ����� �������� �ϰ� �ʹٸ� �Ʒ� �ڵ��� 2000.0f ����� ����
	Vector3 randomPos = target->Pos() + (dir.GetNormalized() * 2000);

	// ������ ���� ��ҿ��� �κ� ����
	for (Robot* robot : robots)
	{
		if (!robot->GetTransform()->Active()) // ���� �κ��� �� �����ִٸ�
		{
			robot->Spawn(randomPos);
			break;
		}
	}
}

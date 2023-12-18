#include "Framework.h"

Collider::Collider() : GameObject(L"Basic/DiffuseLight.hlsl")
{
	// �޽� �����
	mesh = new Mesh<Vertex>(); // ���� ������ (���� �浹ü���� ���� ���� ���� �ʿ�)

	SetColor(0, 1, 0); // �⺻�� �ʷϻ�
}

Collider::~Collider()
{
	delete mesh;
}

void Collider::Render()
{
	// (2D�� ��������) Ʈ�������� Ȱ��ȭ�Ǿ� �־�� ����
	
	// ���� Ŭ�������� ������ On ���¿��� �� ����
	if (!isRender) return;

	SetRender(); // �θ��� ���� ����

	mesh->Draw(); // ������ �⺻ ���ÿ� ���ؼ� ���
	// mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST); // �޽ø� ���� �������� ǥ���ϱ�
}

bool Collider::IsCollision(Collider* collider)
{
	// Ȱ��ȭ�� ���� �ʾ����� false ��ȯ
	// (����)

	// �ʿ��� ȣ�� (���� ������ ���� ���� �Ǻ� �Լ� ȣ��)
	switch (collider->type) // �ε�ģ �浹ü�� Ÿ���� �����ΰ��� ����
	{
	case Collider::Type::BOX:
		return IsBoxCollision((BoxCollider*)collider);

	case Collider::Type::SPHERE:
		return InSphereCollision((SphereCollider*) collider);
	}

	// ������� �Դٸ� �� �� �ϳ�
	// 1. �浹ü�� Ÿ���� �ڽ��� ����ü�� �ƴϴ�
	// 2. �浹 ��Ȳ ��ü�� � ������ �־ �Ǻ��� �� �ϰڴ�
	//    (�ܼ� �浹 �ƴ��̶�� ������ false�� return���� �״ϱ�)

	return false;
}

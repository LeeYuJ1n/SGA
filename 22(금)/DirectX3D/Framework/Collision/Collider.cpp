#include "Framework.h"

bool Collider::allRender = true; //�������� ����

Collider::Collider()
    //: GameObject(L"Light/DiffuseLight.hlsl")
    : GameObject(L"Basic/Collider.hlsl")
{
    isRender = true; //���� �⺻ ����

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
    //if (!isActive) return;
    
    // ���� Ŭ�������� ������ On ���¿��� �� ���� (�ϰ��� ���� �ɼ��� ��� ������ ���)
    //if (!allRender || !isRender) return;

    SetRender(); //�θ��� ���� ����

    if (isRenderAsLine) //���� ��� ���
    {
        mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST); // �޽ø� ���� �������� ǥ���ϴ� Ÿ��
    }
    else mesh->Draw(); // ������ �⺻ ���ÿ� ���ؼ� ���
}

bool Collider::IsCollision(Collider* collider)
{
    //Ȱ��ȭ�� ���� �ʾ����� false ��ȯ
    if (!isActive) return false;

    // �ʿ��� ȣ�� (���� ������ ���� ���� �Ǻ� �Լ� ȣ��)
    switch (collider->type) // �ε�ģ �浹ü�� Ÿ���� �����ΰ��� ����
    {
    case Collider::Type::BOX:
        return IsBoxCollision((BoxCollider*)collider);
    case Collider::Type::SPHERE:
        return IsSphereCollision((SphereCollider*)collider);
    }

    //������� �Դٸ� �� �� �ϳ�
    // 1. �浹ü�� Ÿ���� �ڽ��� ��ü�� �ƴϴ�
    // 2. �浹 ��Ȳ ��ü�� � ������ �־ �Ǻ��� �� �ϰڴ�
    //    (�ܼ� �浹 �ƴ��̶�� ������ false�� return���� �״ϱ�)

    return false; // ������ �浹 ������ �� �ϴµ� ���� ��ȯ�̶�
}

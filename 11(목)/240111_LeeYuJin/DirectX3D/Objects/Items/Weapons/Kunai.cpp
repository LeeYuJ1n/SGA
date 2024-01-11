#include "Framework.h"
#include "Kunai.h"

// Kunai::Kunai(Transform* transform)
//     : transform(transform)
// {
//     // ���� ���� ��� (�ӽù���)
// 
//     // 1. ���� �ۿ��� �����, �ش� ���� Ʈ�������� ���⿡ �ֱ�
//     // 2. �� transform�� �ӽ÷� ���� �ְ�, ���� ���⼭ �����, �ٽ� ���� Ʈ�������� ���Ҵ��ϱ�
// 
//     transform->Scale() = 1; // ũ�� ���� (��ȭ�� �ʿ��ϸ� �ͼ� ���� �ʿ�)
// 
//     collider = new SphereCollider();
//     collider->SetParent(transform); // �浹ü�� Ʈ�������� �����ϱ�
// 
//     collider->Scale() = 1; // �浹ü ũ�� ���� (��ȭ�� �ʿ��ϸ� �ͼ� ����)
//     collider->Pos() = {}; // ���� ��ġ ���� (�𵨰� �浹ü ���̿� ������ ������ ���⼭ ����
// }

Kunai::Kunai()
{
    // ���� ���� ��� (�ӽù���)
    // 1. ���� �ۿ��� �����, �ش� ���� Ʈ�������� ���⿡ �ֱ�
    // 2. �� transform�� �ӽ÷� ���� �ְ�, ���� ���⼭ �����, �ٽ� ���� Ʈ�������� ���Ҵ��ϱ�
    model = new Model("Kunai");
    model->Scale() *= 100.0f;

    // transform->Scale() = 1; // ũ�� ���� (��ȭ�� �ʿ��ϸ� �ͼ� ���� �ʿ�)
    
    collider = new SphereCollider();
    collider->SetParent(model); // �浹ü�� Ʈ�������� �����ϱ�
    
    collider->Scale() = 1; // �浹ü ũ�� ���� (��ȭ�� �ʿ��ϸ� �ͼ� ����)
    // collider->Pos() = {}; // ���� ��ġ ���� (�𵨰� �浹ü ���̿� ������ ������ ���⼭ ����
}

Kunai::~Kunai()
{
    delete model; // �ӽ� ���� �������� �� �ڵ� ����
    delete collider;
}

void Kunai::Update()
{
    if (!model->Active()) return; // Ȱ��ȭ�� �ƴϸ� ��������

    time += DELTA;

    if (time > LIFE_SPAN)
        model->SetActive(false);

    model->Pos() += direction * speed * DELTA;
    model->UpdateWorld();

    collider->UpdateWorld();
}

void Kunai::Render()
{
    model->Render();
    collider->Render();
}

//�ۿ��� �θ��� ���� ��ô ���
void Kunai::Throw(Vector3 pos, Vector3 dir)
{
    model->SetActive(true);

    model->Pos() = pos;
    direction = dir;

    model->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2;
                       // ���ư��� ����       -    90��
                       // (�Ϲ����� ���) ���η� ������� ����ü�� �յڷ� ������ ������ �� �ְ�

    time = 0; // ���� �ð��� 0
}

#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
    colliders.push_back(new BoxCollider());
    colliders.back()->SetTag("Box1");
     
    // colliders.push_back(new BoxCollider());
    // colliders.back()->SetTag("Box2");

    colliders.push_back(new SphereCollider());
    colliders.back()->SetTag("Sphere1");
    
    // colliders.push_back(new SphereCollider());
    // colliders.back()->SetTag("Sphere2");
}

CollisionScene::~CollisionScene()
{
    for (Collider* collider : colliders)
        delete collider;
}

void CollisionScene::Update()
{
    Ray ray = CAM->ScreenPointToRay(mousePos); //ī�޶� �ִ� ��ũ�� ����ĳ��Ʈ ����� ȣ�� (3���� ���콺 ��ġ ���)

    Contact contact;
    // 0�� �浹ü�� ������ �浹�Ѵٸ�
    // if (colliders[0]->IsRayCollision(ray, &contact))
    // {
    //     colliders[0]->SetColor(1, 0, 0);   // �浹ü�� ������ ����
    //     colliders[1]->Pos() = contact.hit; // �浹�� ���� 1�� �浹ü ��ġ ������Ʈ
    // }
    // else
    // {
    //     colliders[0]->SetColor(0, 1, 0);
    // }

    // 0�� �浹ü�� 1�� �浹ü�� ���� �ε�ġ��
    if (colliders[0]->IsCollision(colliders[1]))
    {
        // �ε�ģ �� �浹ü ������ ����
        colliders[0]->SetColor(1, 0, 0);
        colliders[1]->SetColor(1, 0, 0);
    }
    else
    {
        // �ʷϼ� �ǵ�����
        colliders[0]->SetColor(0, 1, 0);
        colliders[1]->SetColor(0, 1, 0);
    }
    
    for (Collider* collider : colliders)
        collider->UpdateWorld();
}

void CollisionScene::PreRender()
{
}

void CollisionScene::Render()
{
    for (Collider* collider : colliders)
        collider->Render();
}

void CollisionScene::PostRender()
{
}

void CollisionScene::GUIRender()
{
    for (Collider* collider : colliders)
        collider->RenderUI();
}

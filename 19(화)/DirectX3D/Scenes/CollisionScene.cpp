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
    Ray ray = CAM->ScreenPointToRay(mousePos); //카메라에 있는 스크린 레이캐스트 기능을 호출 (3차원 마우스 위치 사용)

    Contact contact;
    // 0번 충돌체가 광원과 충돌한다면
    // if (colliders[0]->IsRayCollision(ray, &contact))
    // {
    //     colliders[0]->SetColor(1, 0, 0);   // 충돌체를 빨갛게 염색
    //     colliders[1]->Pos() = contact.hit; // 충돌한 곳에 1번 충돌체 위치 업데이트
    // }
    // else
    // {
    //     colliders[0]->SetColor(0, 1, 0);
    // }

    // 0번 충돌체와 1번 충돌체가 서로 부딪치면
    if (colliders[0]->IsCollision(colliders[1]))
    {
        // 부딪친 두 충돌체 빨갛게 염색
        colliders[0]->SetColor(1, 0, 0);
        colliders[1]->SetColor(1, 0, 0);
    }
    else
    {
        // 초록속 되돌리기
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

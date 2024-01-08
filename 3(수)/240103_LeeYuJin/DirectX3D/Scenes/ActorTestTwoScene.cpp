#include "Framework.h"
#include "ActorTestTwoScene.h"

ActorTestTwoScene::ActorTestTwoScene()
{
    BlockManager::Get()->CreateBlock(20, 20); // 호출을 통해 생성

    player = new TestActor();
    player->UseBlockManager(true); // 필요는 없었지만 액터 테스트 1과 같이 쓰려고 만든 추가 함수
                                   // 기능 : 블록 매니저를 사용한다고 클래스에 설정하기

    // 추적 카메라 사용
    CAM->SetTarget(player);
    CAM->TargetOptionLoad("Follow");

    target = new Cylinder();
    target->Pos() = { 5.0, 1.0f, 5.0f };
    target->UpdateWorld();
}

ActorTestTwoScene::~ActorTestTwoScene()
{
    // 소멸자 : 다 지우기
    BlockManager::Delete(); // 블록 매니저도 여기서 지우기
    delete player;
    delete target;
}

void ActorTestTwoScene::Update()
{
    BlockManager::Get()->Update();     // 블록 업데이트 부르기
    player->Update();                  // 플레이어 업데이트
    BlockManager::Get()->Push(player); // 원래 함수의 의도까진 아니었지만 응용 가능했던 호출
                                       // Push : 두 물체가 ( = 두 블록이)겹치거나 움직여서 부딪치면
                                       //        한쪽이 반대로 밀려나도록 하는 함수
                                       //        그런데 플레이어도 구체 충돌체가 있기 때문에 적용 가능
                                       //        = 플레이어가 블록에 부딪치면 밀려나게 = 안 겹치게
}

void ActorTestTwoScene::PreRender()
{

}

void ActorTestTwoScene::Render()
{
    BlockManager::Get()->Render();
    player->Render();
    target->Render();
}

void ActorTestTwoScene::PostRender()
{
    player->PostRender();
}

void ActorTestTwoScene::GUIRender()
{
    player->GUIRender();
}
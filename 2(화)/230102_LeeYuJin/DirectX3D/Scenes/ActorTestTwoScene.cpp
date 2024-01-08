#include "Framework.h"
#include "ActorTestTwoScene.h"

ActorTestTwoScene::ActorTestTwoScene()
{
    BlockManager::Get()->CreateBlock(20, 20); // 호출을 통해 생성

	player = new TestActor();

	// 추적 카메라의 표적 설정
	CAM->SetTarget(player);
	CAM->TargetOptionLoad("Follow");
}

ActorTestTwoScene::~ActorTestTwoScene()
{
	delete player;
}

void ActorTestTwoScene::Update()
{
	player->Update();

	BlockManager::Get()->Update();
}

void ActorTestTwoScene::PreRender()
{

}

void ActorTestTwoScene::Render()
{
	BlockManager::Get()->Render();

	player->Render();
}

void ActorTestTwoScene::PostRender()
{
	player->PostRender();
}

void ActorTestTwoScene::GUIRender()
{
	player->GUIRender();
}
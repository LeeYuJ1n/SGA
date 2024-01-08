#include "Framework.h"
#include "ActorTestTwoScene.h"

ActorTestTwoScene::ActorTestTwoScene()
{
    BlockManager::Get()->CreateBlock(20, 20); // ȣ���� ���� ����

	player = new TestActor();

	// ���� ī�޶��� ǥ�� ����
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
#include "Framework.h"
#include "ActorTestTwoScene.h"

ActorTestTwoScene::ActorTestTwoScene()
{
    BLOCKMANAGER->CreateBlock(20, 20); // 호출을 통해 생성

    player = new TestActor();

    CAM->SetTarget(player);
    CAM->TargetOptionLoad("Follow");

}

ActorTestTwoScene::~ActorTestTwoScene()
{
    delete player;
}

void ActorTestTwoScene::Update()
{
    if (KEY_DOWN(VK_RBUTTON))
    {
        // BLOCKMANAGER->CreateBlock(1, 1);
        BLOCKMANAGER->BuildBlock(new Cube());
    }

    BLOCKMANAGER->Update();
    player->Update();
}

void ActorTestTwoScene::PreRender()
{

}

void ActorTestTwoScene::Render()
{
    player->Render();
    BLOCKMANAGER->Render();
}

void ActorTestTwoScene::PostRender()
{

}

void ActorTestTwoScene::GUIRender()
{
    player->GUIRender();
}
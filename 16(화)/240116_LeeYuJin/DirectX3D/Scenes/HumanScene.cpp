#include "Framework.h"
#include "HumanScene.h"

HumanScene::HumanScene()
{
    //human = new Human();
    naruto = new Naruto();
    KunaiManager::Get();

    robot = new Model("Robot");


    CAM->SetTarget(naruto);
    CAM->TargetOptionLoad("Naruto");
    CAM->LookAtTarget();
}

HumanScene::~HumanScene()
{
    //delete human;
    delete naruto;
    delete robot;
    KunaiManager::Get()->Delete();
}

void HumanScene::Update()
{
    //human->Update();
    naruto->Update();
    robot->UpdateWorld();
    KunaiManager::Get()->Update();
}

void HumanScene::PreRender()
{
}

void HumanScene::Render()
{
    //human->Render();
    naruto->Render();
    robot->Render();
    KunaiManager::Get()->Render();
}

void HumanScene::PostRender()
{
}

void HumanScene::GUIRender()
{
    //human->GUIRender();
}

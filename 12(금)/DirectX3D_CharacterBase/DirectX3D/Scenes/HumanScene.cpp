#include "Framework.h"
#include "HumanScene.h"

HumanScene::HumanScene()
{
    human = new Human();
    naruto = new Naruto();
}

HumanScene::~HumanScene()
{
    delete human;
    delete naruto;
}

void HumanScene::Update()
{
    human->Update();
    naruto->Update();
}

void HumanScene::PreRender()
{
}

void HumanScene::Render()
{
    human->Render();
    naruto->Render();
}

void HumanScene::PostRender()
{
}

void HumanScene::GUIRender()
{
    human->GUIRender();
}

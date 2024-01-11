#include "Framework.h"
#include "HumanScene.h"

HumanScene::HumanScene()
{
    human = new Human();
    kunai = new Kunai();
}

HumanScene::~HumanScene()
{
    delete human;
    delete kunai;
}

void HumanScene::Update()
{
    human->Update();
    
    if (KEY_DOWN('F'))
    {
        kunai->Throw(human->Pos(), -human->Pos().Forward());
    }

    kunai->Update();
}

void HumanScene::PreRender()
{
}

void HumanScene::Render()
{
    human->Render();
    kunai->Render();
}

void HumanScene::PostRender()
{
}

void HumanScene::GUIRender()
{
    human->GUIRender();
}

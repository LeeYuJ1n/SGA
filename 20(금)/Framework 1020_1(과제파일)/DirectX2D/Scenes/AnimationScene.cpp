#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
    BulletManager::Get();
    CommandManager::Get();

    ninja = new Ninja();

    background = new Quad(L"Textures/Shooting/backgraound.png");
    background->Pos() = { CENTER_X, CENTER_Y };
    background->UpdateWorld();

    EffectManager::Get()->Add("explosion1", L"Textures/Effect/Explosion1.png", 4, 4);
    EffectManager::Get()->Add("explosion2", L"Textures/Effect/Explosion2.png", 4, 2);
    EffectManager::Get()->Add("fire", 10, L"Textures/Effect/Fire.png", 3, 3);

    EffectManager::Get()->Add("explosion1a", L"Textures/Effect/Explosion1.png", 4, 4, 1, true);
    EffectManager::Get()->Add("explosion2a", L"Textures/Effect/Explosion2.png", 4, 2, 1, true);
    EffectManager::Get()->Add("fireA", 10, L"Textures/Effect/Fire.png", 3, 3, 1, true);

    EffectManager::Get()->SetColor("explosion1", 0, 1, 1);
    EffectManager::Get()->SetColor("explosion1a", 1, 0, 0);
}

AnimationScene::~AnimationScene()
{
    delete ninja;
    delete background;

    BulletManager::Delete();
    EffectManager::Delete();
}

void AnimationScene::Update()
{
    if (KEY_PRESS(VK_RSHIFT))
    {
        if (KEY_DOWN('I'))
            EffectManager::Get()->Play("explosion1", mousePos);
        if (KEY_DOWN('O'))
            EffectManager::Get()->Play("explosion2", mousePos);
        if (KEY_DOWN('P'))
            EffectManager::Get()->Play("fire", mousePos);
    }
    else
    {
        if (KEY_DOWN('I'))
            EffectManager::Get()->Play("explosion1a", mousePos);
        if (KEY_DOWN('O'))
            EffectManager::Get()->Play("explosion2a", mousePos);
        if (KEY_DOWN('P'))
            EffectManager::Get()->Play("fireA", mousePos);
    }

    ninja->Update();

    BulletManager::Get()->Update();
    EffectManager::Get()->Update();
    CommandManager::Get()->Update();
}

void AnimationScene::Render()
{
    background->Render();
    ninja->Render();

    BulletManager::Get()->Render();
    EffectManager::Get()->Render();
}

void AnimationScene::PostRender()
{    
    ninja->PostRender();
}

void AnimationScene::Init()
{
    CAMERA->SetTarget(ninja);
    ninja->Pos() = { CENTER_X, CENTER_Y };
}
void AnimationScene::Quit()
{
    CAMERA->SetTarget(nullptr);
}


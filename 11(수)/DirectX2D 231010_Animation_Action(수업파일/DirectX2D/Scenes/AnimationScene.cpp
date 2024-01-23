#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
    BulletManager::Get();

    ninja = new Ninja();
    testEff = new Effect(L"Textures/Effect/Explosion1.png", Vector2(4, 4), 1, false);
}

AnimationScene::~AnimationScene()
{
    delete ninja;

    BulletManager::Delete();
}

void AnimationScene::Update()
{
    ninja->Update();

    BulletManager::Get()->Update();

    // 테스트 입력
    if (KEY_DOWN(VK_RETURN))
    {
        testEff->Play(mousePos);
    }

    testEff->Update();
}

void AnimationScene::Render()
{
    ninja->Render();

    BulletManager::Get()->Render();
    testEff->Render();
}

void AnimationScene::PostRender()
{
}

void AnimationScene::Init()
{
}

void AnimationScene::Quit()
{
}
#include "Framework.h"
#include "AnimationScene.h"

// 11일의 과제 : 오랜만에 C++ 콘솔 앱

// 실시간 타자기 (영어로)

// 1. 내가 타자를 칩니다.
// 2. 화면에 다음 결과가 나오도록 해주세요
//    A. 첫 줄에는 내가 마지막으로 친 타자 (영어 혹은 숫자여야 합니다)
//    B. 다음 줄에는 내가 지금까지 친 모든 타자가 차례로

// (예시)

// 1, b, 9, f를 내가 타자를 쳤다면

// 화면 첫줄에는 f가
// 다음 줄에는 1b9f라는 글자가 나와야 합니다. (system("cls")와 반복문을 써주세요)
// * 입력은 cin getch 어느 쪽이든 쓸 수 있습니다.
// * 벡터, 맵, 혹은 스트링 어느 것이든 자유롭게 써서 결과를 만들어주세요.


AnimationScene::AnimationScene()
{
    CommandManager::Get();
    BulletManager::Get();

    ninja   = new Ninja();
    // testEff = new Effect(L"Textures/Effect/Fire.png", Vector2(3, 3), 1, false);

    // 매니저를 통한 이펙트 등록
    EffectManager::Get()->Add("explosion1", L"Textures/Effect/Explosion1.png", 4, 4);
    EffectManager::Get()->Add("explosion2", L"Textures/Effect/Explosion2.png", 4, 2);
    EffectManager::Get()->Add("fire", 10, L"Textures/Effect/Fire.png", 3, 3);

    // 애디티브의 a를 붙여서 한 번 더 등록 (추가 블렌드 체험)
    EffectManager::Get()->Add("explosion1a", L"Textures/Effect/Explosion1.png", 4, 4, 1, true);
    EffectManager::Get()->Add("explosion2a", L"Textures/Effect/Explosion2.png", 4, 2, 1, true);
    EffectManager::Get()->Add("fireA", 2, L"Textures/Effect/Fire.png", 3, 3, 1, true);

    EffectManager::Get()->SetColor("explosion1", 1, 0, 0);
    EffectManager::Get()->SetColor("explosion1a", 1, 0, 0);
}

AnimationScene::~AnimationScene()
{
    delete ninja;

    BulletManager::Delete();
}

void AnimationScene::Update()
{
    ninja->Update();

    // 입력으로 재생
    if (KEY_DOWN('Q')) EffectManager::Get()->Play("explosion1", mousePos);
    if (KEY_DOWN('W')) EffectManager::Get()->Play("explosion2", mousePos);
    if (KEY_DOWN('E')) EffectManager::Get()->Play("fire", mousePos);

    if (KEY_DOWN('A')) EffectManager::Get()->Play("explosion1a", mousePos);
    if (KEY_DOWN('S')) EffectManager::Get()->Play("explosion2a", mousePos);
    if (KEY_DOWN('D')) EffectManager::Get()->Play("fireA", mousePos);

    CommandManager::Get()->Update();
    BulletManager::Get()->Update();
    EffectManager::Get()->Update();

    // //테스트 입력
    // if (KEY_DOWN(VK_RETURN))
    // {
    //     testEff->Play(mousePos);
    // }
    // testEff->Update();
}

void AnimationScene::Render()
{
    ninja->Render();

    BulletManager::Get()->Render();
    EffectManager::Get()->Render();
    // testEff->Render();
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
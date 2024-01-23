#include "Framework.h"
#include "AnimationScene.h"

// 17일 : 글자 출력을 다이렉트X로 해보기!
//        -> 다이렉트X의 추가 기능을 사용 (DWrite)
//        1. 프레임워크에 기능 등록
//        2. 디바이스에서 추가 설정 변경

//        위의 준비가 끝난 후 폰트 클래스를 만들자


AnimationScene::AnimationScene()
{
    CommandManager::Get();
    BulletManager::Get();

    ninja = new Ninja();
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

    // 생성자에서 폰트 데이터를 등록해보기
    // 글자색 : 흰색
    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddStyle("PGothic", L"맑은 고딕");
    // PGothic : 키 이름. PGothic = Pure_Gothic
    // L"맑은 고딕" : 실제 폰트 이름을 써야 한다
    
    // 추가 글꼴 사용해보기
    Font::Get()->AddColor("Yellow", 1, 1, 0);
    Font::Get()->AddStyle("Serious", L"궁서체");
    Font::Get()->AddStyle("VerySerious", L"궁서체", 36.0f);

    // 글꼴 세팅
    Font::Get()->SetColor("Yellow");
    Font::Get()->SetStyle("Serious");

    // 출력은 렌더에서
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
    // 글꼴 렌더 준비
    Font::Get()->GetDC()->BeginDraw(); // 문자 그릴 준비 시작 (BeginDraw는 DX의 제공함수)

    ninja->Render();

    BulletManager::Get()->Render();
    EffectManager::Get()->Render();
    // testEff->Render();

    // 글꼴 출력
    Font::Get()->RenderText(L"헬로, 월드!", { 100, WIN_HEIGHT - 100 });

    Font::Get()->GetDC()->EndDraw(); // 문자 그리는 절차 끝
    // Device::Get()->Present(); // 게임 매니저에 있어서 안 씀
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
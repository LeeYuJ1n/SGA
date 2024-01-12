#include "Framework.h"
#include "Human.h"

Human::Human() : ModelAnimator("Human") //부모 모델 만들기
{
    //동작 읽기
    ReadClip("Idle", 1);
    ReadClip("Run", 1);
    ReadClip("Jump", 1);

    action = (ACTION)frameBuffer->Get().cur.clip; // 동작이 0번=가만히 있기라서 액션도 가만히 있기

    //무기 생성
    crowbar = new Crowbar();
    crowbar->Load(); // 사전 세팅된 설정이 있는지 보고 있으면 읽기

    //무기를 손에 쥐기
    mainHand = new Transform(); // 트랜스폼이 있다는 것만 정하기
    crowbar->SetParent(mainHand); // 무기 위치 = 내 손

    // 쿠나이 (매니저 생성)
    KunaiManager::Get(); // 필수는 아닌데 해두면 플레이 도중 렉 유발을 줄일 수 있음
}

Human::~Human()
{
    delete crowbar;
    delete mainHand; // <- 이렇게 지워도 되는 이유 : 포인터는 지워도 데이터가 날아가진 않는다
                     // 단지 그 자리에 덮어씌워질 가능성이 생길 뿐
                     // 그리고 이 "손"의 진짜 데이터는 아직 원본이 그 자리에 남아 있다
}

void Human::Update()
{
    ClipSync();
    Control();
    Jump();

    // 업데이트에서 중요한 것 : 1. 내 손은 무엇인가 (쇠지렛대보다 먼저 수행해야 함)
    //                        2. 그리고 내 손은 어디 있는가 (그래야 거기에 무기가 있을 테니까)

    mainHand->SetWorld(GetTransformByNode(51)); //트랜스폼의 공간 할당하기
    // GetTransformByNode : 모델 애니메이터에서 만들었던 "노드에 할당된 트랜스폼 받아오기"
    // 매개변수 51 : Human.fbx 기준 오른손이 있었던 노드의 순서

    crowbar->Update();

    ModelAnimator::Update(); //원본으로서의 업데이트 또한 수행
                             //클래스명이 없으면 재귀함수가 돼서 문제 발생

    KunaiManager::Get()->Update();
}

void Human::Render()
{
    crowbar->Render();

    ModelAnimator::Render();

    KunaiManager::Get()->Render();
}

void Human::GUIRender()
{
    crowbar->GUIRender();
    ModelAnimator::GUIRender();
}

void Human::ClipSync()
{
    // 재생 중인 동작이 설정된 액션과 달라지면
    if ((ACTION)frameBuffer->Get().cur.clip != action)
    {
        // 행동에 맞는 동작 재생
        PlayClip((int)action);
    }
}

void Human::Control()
{
    if (!isJump)
    {
        if (KEY_PRESS('W'))
        {
            action = ACTION::RUN;
        }

        if (KEY_DOWN(VK_SPACE))
        {
            action = ACTION::JUMP;
            jumpVelocity = jumpForce;
            isJump = true;
        }

        if (KEY_UP('W'))
        {
            action = ACTION::IDLE;
        }

        if (KEY_DOWN(VK_RETURN))
        {
            KunaiManager::Get()->Throw(Pos(), Forward());
        }
    }
}

void Human::Jump()
{
    jumpVelocity -= 9.8f * gravityMult * DELTA;
    Pos().y += jumpVelocity;

    if (Pos().y > 0)
    {
        if (action != ACTION::JUMP) action = ACTION::JUMP;
        isJump = true;
    }

    if (Pos().y < 0)
    {
        Pos().y = 0;
        jumpVelocity = 0;
        if (action == ACTION::JUMP) action = ACTION::IDLE;
        isJump = false;
    }
}

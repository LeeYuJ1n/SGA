#include "Framework.h"

Ninja::Ninja()    
{
    Pos() = { CENTER_X, CENTER_Y };

    CreateActions();
    actions[curAction]->Start();

    Observer::Get()->AddIntParamEvent("Skill", bind(&Ninja::SetActionCode, this, placeholders::_1));
    // placeholder : c++의 네임스페이스, "빈 자리"라는 뜻 - 나중에 여기에 변수 등의 새로운 데이터가 들어올 거라고 예약을 걸어두기

    SetPixelShader(L"Ninja.hlsl");

    // Ninja.hlsl : 그림 샘플링과 2차 텍스처를 모두 지정해서, "살짝 키운" 2차 샘플 텍스처를 조합해주는 셰이더
    // -> 2차 텍스처의 모양이 본래의 텍스처 주변을 "장식"하게 된다

    // -> 이 셰이더의 진짜 이름 : Outline, "외곽선" 셰이더

    sLayer = Texture::Add(L"Textures/rainbow.png");

    // 위 텍스처에 다른 그림을 넣어서 외곽선의 효과를 바꿀 수 있다
    // 반대로 외곽선을 쓰기 싫을 경우에 고의로 텅 빈 완전 투명색 텍스처를 쓰거나, 필요 이상으로 복잡한 그림을 넣어줘도 된다
    // -> 게임에서 쓰이는 "디폴트 텍스처" 혹은 "더미 이미지" 등의 정체

    intBuffer   = new IntValueBuffer();
    floatBuffer = new FloatValueBuffer();
}

Ninja::~Ninja()
{
    for (pair<ActionType, Action*> action : actions)
        delete action.second;
}

void Ninja::Update()
{
    Control();

    actions[curAction]->Update();
    UpdateWorld();
}

void Ninja::Render()
{
    sLayer     ->PSSet(1);
    intBuffer  ->SetPS(1);
    floatBuffer->SetPS(2);

    // 프레임이 바뀔 때마다 사이즈를 직접 도출
    Vector2 frameSize = actions[curAction]->GetClip()->GetCurFrame()->GetSize();
    floatBuffer->Get()[0] = frameSize.x;
    floatBuffer->Get()[1] = frameSize.y;

    // 캐릭터를 렌더하지 않고, 캐릭터의 행동을 렌더한다
    SetRender();
    actions[curAction]->Render();
}

void Ninja::Control()
{
    StackCommandLR();
    Move();
    Jump();
    Attack();
}

void Ninja::StackCommandLR()
{
    // 커맨드 입력에서 왼쪽 여부를 통해 왼방향 장풍을 쏘기 위한 테스트 전용 함수

    if (KEY_DOWN(VK_LEFT))
    {
        // 캐릭터가 어느 방향을 보고 있었는가에 의해 조작을 다르게
        if (IsLeft())
        {
            CommandManager::Get()->StackCommand('0' + 6); // 닌자가 왼쪽을 보고 있었으면 이 키가 "앞"
        }
        else
        {
            CommandManager::Get()->StackCommand('0' + 4);
        }
    }

    if (KEY_DOWN(VK_RIGHT))
    {
        if (IsLeft())
        {
            CommandManager::Get()->StackCommand('0' + 4); // 닌자가 왼쪽이면 이 키는 "뒤"가 된다
        }
        else
        {
            CommandManager::Get()->StackCommand('0' + 6);
        }
    }

    // * 이 조치를 통해서 확인할 수 있는 것 : 2D는 왼쪽 오른쪽 방향이 중요한 개발
    // (그림이 어느 쪽을 보고 있느냐 / 앞이냐 뒤냐가 시종일관 중요)

    // ** 실습 대상 (도전과제)
    // ←↙↓↘→ + 공격 같은 커맨드는 그럼 다시 어떻게 입력을 해야 할까?
    // ---> 닌자가 오른쪽을 볼 때, 왼쪽을 입력하면  "뒤를 입력할 수 있지만, 동시에 닌자는 왼쪽을 돌아보기도 한다"

    // (같이 생각해볼 거리) 왼쪽 키를 누른다고 닌자가 반드시 왼쪽을 봐야만 하는가?
    // (같이 생각해볼 거리2) 플레이어의 관점에서 "앞"이라고 해서 반드시 닌자에게도 "앞"이어야 할까?

    // ---> 이 질문을 이해했을 때, 대전 격투 게임, 혹은 반응이 중요한 서바이벌 슈터 게임 등을 키보드와 커맨드로 구현하기 위한
    //      사고의 조건을 갖춘다고 볼 수 있습니다
}

void Ninja::Move()
{
    if (curAction == JUMP) return;
    if (curAction >= ATTACK) return;

    bool isMove = false;

    isMove |= KEY_PRESS(VK_RIGHT);
    isMove |= KEY_PRESS(VK_LEFT);
    //if (KEY_PRESS(VK_RIGHT) || KEY_PRESS(VK_LEFT)) isMove = true;

    isMove ? SetAction(RUN) : SetAction(IDLE);
}

void Ninja::Jump()
{
    if (curAction >= ATTACK) return;

    if (KEY_DOWN(VK_UP))
        SetAction(JUMP);
}

void Ninja::Attack()
{
    if (curAction >= ATTACK) return;

    if (KEY_DOWN('A'))
    {
        if (curAction == JUMP)
        {
            SetAction(JUMP_ATTACK);
        }
        else
        {
            SetAction(ATTACK);
        }
    }
    
    if (KEY_DOWN('S'))
    {
        if (curAction == JUMP)
        {
            SetAction(JUMP_THROW);
        }
        else
        {
            SetAction(THROW);
        }
    }
}

void Ninja::SetIdle()
{
    SetAction(IDLE);
}

void Ninja::SetAction(ActionType type)
{
    if (curAction == type) return;

    curAction = type;
    actions[type]->Start();
}

void Ninja::SetActionCode(int typeCode)
{
    if (curAction == (ActionType)typeCode) return;

    curAction = (ActionType)typeCode;
    actions[(ActionType)typeCode]->Start();
}

void Ninja::CreateActions()
{
    actions[IDLE]        = new Action("Textures/Ninja/", "Ninja_Idle.xml", true);
    actions[RUN]         = new NinjaRun(this);
    actions[JUMP]        = new NinjaJump(this);
    actions[JUMP]        ->SetEvent(bind(&Ninja::SetIdle, this));
    //bind에 자기 클래스의 멤버 함수를 사용함으로써 void()에 함수 등록
    actions[ATTACK]      = new NinjaMeleeAttack(this);
    actions[ATTACK]      ->SetEvent(bind(&Ninja::SetIdle, this));
    actions[JUMP_ATTACK] = new NinjaJumpAttack(this);
    actions[JUMP_ATTACK]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[THROW]       = new NinjaThrow(this);
    actions[THROW]       ->SetEvent(bind(&Ninja::SetIdle, this));
}
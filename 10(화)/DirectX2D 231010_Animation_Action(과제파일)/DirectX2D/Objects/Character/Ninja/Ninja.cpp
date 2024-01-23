#include "Framework.h"

Ninja::Ninja()    
{
    Pos() = { CENTER_X, CENTER_Y };

    CreateActions();
    actions[curAction]->Start();
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
    // 캐릭터를 렌더하지 않고, 캐릭터의 행동을 렌더한다
    SetRender();
    actions[curAction]->Render();
}

void Ninja::Control()
{
    Move();
    Jump();
    Attack();
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

void Ninja::CreateActions()
{
    actions[IDLE] = new Action("Textures/Ninja/", "Ninja_Idle.xml", true);
    actions[RUN] = new NinjaRun(this);
    actions[JUMP] = new NinjaJump(this);
    actions[JUMP]->SetEvent(bind(&Ninja::SetIdle, this));
    //bind에 자기 클래스의 멤버 함수를 사용함으로써 void()에 함수 등록
    actions[ATTACK] = new NinjaMeleeAttack(this);
    actions[ATTACK]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[JUMP_ATTACK] = new NinjaJumpAttack(this);
    actions[JUMP_ATTACK]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[THROW] = new NinjaThrow(this);
    actions[THROW]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[JUMP_THROW] = new NinjaJumpThrow(this);
    actions[JUMP_THROW]->SetEvent(bind(&Ninja::SetIdle, this));
}
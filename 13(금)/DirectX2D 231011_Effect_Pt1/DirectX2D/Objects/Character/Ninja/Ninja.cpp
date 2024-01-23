#include "Framework.h"

Ninja::Ninja()    
{
    Pos() = { CENTER_X, CENTER_Y };

    CreateActions();
    actions[curAction]->Start();

    Observer::Get()->AddIntParamEvent("Skill", bind(&Ninja::SetActionCode, this, placeholders::_1));
    // placeholder : c++�� ���ӽ����̽�, "�� �ڸ�"��� �� - ���߿� ���⿡ ���� ���� ���ο� �����Ͱ� ���� �Ŷ�� ������ �ɾ�α�
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
    // ĳ���͸� �������� �ʰ�, ĳ������ �ൿ�� �����Ѵ�
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
    actions[JUMP]->SetEvent(bind(&Ninja::SetIdle, this));
    //bind�� �ڱ� Ŭ������ ��� �Լ��� ��������ν� void()�� �Լ� ���
    actions[ATTACK]      = new NinjaMeleeAttack(this);
    actions[ATTACK]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[JUMP_ATTACK] = new NinjaJumpAttack(this);
    actions[JUMP_ATTACK]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[THROW]       = new NinjaThrow(this);
    actions[THROW]->SetEvent(bind(&Ninja::SetIdle, this));
}
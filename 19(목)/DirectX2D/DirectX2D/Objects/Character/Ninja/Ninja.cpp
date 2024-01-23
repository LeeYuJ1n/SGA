#include "Framework.h"

Ninja::Ninja()    
{
    Pos() = { CENTER_X, CENTER_Y };

    CreateActions();
    actions[curAction]->Start();

    Observer::Get()->AddIntParamEvent("Skill", bind(&Ninja::SetActionCode, this, placeholders::_1));
    // placeholder : c++�� ���ӽ����̽�, "�� �ڸ�"��� �� - ���߿� ���⿡ ���� ���� ���ο� �����Ͱ� ���� �Ŷ�� ������ �ɾ�α�

    SetPixelShader(L"Ninja.hlsl");

    // Ninja.hlsl : �׸� ���ø��� 2�� �ؽ�ó�� ��� �����ؼ�, "��¦ Ű��" 2�� ���� �ؽ�ó�� �������ִ� ���̴�
    // -> 2�� �ؽ�ó�� ����� ������ �ؽ�ó �ֺ��� "���"�ϰ� �ȴ�

    // -> �� ���̴��� ��¥ �̸� : Outline, "�ܰ���" ���̴�

    sLayer = Texture::Add(L"Textures/rainbow.png");

    // �� �ؽ�ó�� �ٸ� �׸��� �־ �ܰ����� ȿ���� �ٲ� �� �ִ�
    // �ݴ�� �ܰ����� ���� ���� ��쿡 ���Ƿ� �� �� ���� ����� �ؽ�ó�� ���ų�, �ʿ� �̻����� ������ �׸��� �־��൵ �ȴ�
    // -> ���ӿ��� ���̴� "����Ʈ �ؽ�ó" Ȥ�� "���� �̹���" ���� ��ü

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

    // �������� �ٲ� ������ ����� ���� ����
    Vector2 frameSize = actions[curAction]->GetClip()->GetCurFrame()->GetSize();
    floatBuffer->Get()[0] = frameSize.x;
    floatBuffer->Get()[1] = frameSize.y;

    // ĳ���͸� �������� �ʰ�, ĳ������ �ൿ�� �����Ѵ�
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
    // Ŀ�ǵ� �Է¿��� ���� ���θ� ���� �޹��� ��ǳ�� ��� ���� �׽�Ʈ ���� �Լ�

    if (KEY_DOWN(VK_LEFT))
    {
        // ĳ���Ͱ� ��� ������ ���� �־��°��� ���� ������ �ٸ���
        if (IsLeft())
        {
            CommandManager::Get()->StackCommand('0' + 6); // ���ڰ� ������ ���� �־����� �� Ű�� "��"
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
            CommandManager::Get()->StackCommand('0' + 4); // ���ڰ� �����̸� �� Ű�� "��"�� �ȴ�
        }
        else
        {
            CommandManager::Get()->StackCommand('0' + 6);
        }
    }

    // * �� ��ġ�� ���ؼ� Ȯ���� �� �ִ� �� : 2D�� ���� ������ ������ �߿��� ����
    // (�׸��� ��� ���� ���� �ִ��� / ���̳� �ڳİ� �����ϰ� �߿�)

    // ** �ǽ� ��� (��������)
    // ��ס�١� + ���� ���� Ŀ�ǵ�� �׷� �ٽ� ��� �Է��� �ؾ� �ұ�?
    // ---> ���ڰ� �������� �� ��, ������ �Է��ϸ�  "�ڸ� �Է��� �� ������, ���ÿ� ���ڴ� ������ ���ƺ��⵵ �Ѵ�"

    // (���� �����غ� �Ÿ�) ���� Ű�� �����ٰ� ���ڰ� �ݵ�� ������ ���߸� �ϴ°�?
    // (���� �����غ� �Ÿ�2) �÷��̾��� �������� "��"�̶�� �ؼ� �ݵ�� ���ڿ��Ե� "��"�̾�� �ұ�?

    // ---> �� ������ �������� ��, ���� ���� ����, Ȥ�� ������ �߿��� �����̹� ���� ���� ���� Ű����� Ŀ�ǵ�� �����ϱ� ����
    //      ����� ������ ����ٰ� �� �� �ֽ��ϴ�
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
    //bind�� �ڱ� Ŭ������ ��� �Լ��� ��������ν� void()�� �Լ� ���
    actions[ATTACK]      = new NinjaMeleeAttack(this);
    actions[ATTACK]      ->SetEvent(bind(&Ninja::SetIdle, this));
    actions[JUMP_ATTACK] = new NinjaJumpAttack(this);
    actions[JUMP_ATTACK]->SetEvent(bind(&Ninja::SetIdle, this));
    actions[THROW]       = new NinjaThrow(this);
    actions[THROW]       ->SetEvent(bind(&Ninja::SetIdle, this));
}
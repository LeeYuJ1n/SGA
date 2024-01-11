#include "Framework.h"

Human::Human() : ModelAnimator("Human") //�θ� �� �����
{
    //���� �б�
    ReadClip("Idle", 1);
    ReadClip("Run", 1);
    ReadClip("Jump", 1);

    action = (ACTION)frameBuffer->Get().cur.clip; // ������ 0��=������ �ֱ�� �׼ǵ� ������ �ֱ�

    // ���� ���� (Crowbar����)
    // crowbar = new Crowbar();
    // crowbar->Load(); // ���� ���õ� ������ �ִ��� ���� ������ �б�

    // ���� ����
    kunai = new Model("Kunai");
    kunai->Rot().y = 180.0f;
    kunai->Load();

    //���⸦ �տ� ���
    mainHand = new Transform(); // Ʈ�������� �ִٴ� �͸� ���ϱ�
    kunai->SetParent(mainHand);
    // crowbar->SetParent(mainHand); // ���� ��ġ = �� ��
}

Human::~Human()
{
    // delete crowbar;
    delete mainHand; // <- �̷��� ������ �Ǵ� ���� : �����ʹ� ������ �����Ͱ� ���ư��� �ʴ´�
                     // ���� �� �ڸ��� ������� ���ɼ��� ���� ��
                     // �׸��� �� "��"�� ��¥ �����ʹ� ���� ������ �� �ڸ��� ���� �ִ�

    delete kunai;
}

void Human::Update()
{
    ClipSync();
    Control();
    Jump();

    // ������Ʈ���� �߿��� �� : 1. �� ���� �����ΰ� (�������뺸�� ���� �����ؾ� ��)
    //                        2. �׸��� �� ���� ��� �ִ°� (�׷��� �ű⿡ ���Ⱑ ���� �״ϱ�)

    mainHand->SetWorld(GetTransformByNode(51)); //Ʈ�������� ���� �Ҵ��ϱ�
    // GetTransformByNode : �� �ִϸ����Ϳ��� ������� "��忡 �Ҵ�� Ʈ������ �޾ƿ���"
    // �Ű����� 51 : Human.fbx ���� �������� �־��� ����� ����

    // crowbar->Update();
    kunai->UpdateWorld();

    ModelAnimator::Update(); //�������μ��� ������Ʈ ���� ����
                             //Ŭ�������� ������ ����Լ��� �ż� ���� �߻�
}

void Human::Render()
{
    // crowbar->Render();

    ModelAnimator::Render();
}

void Human::GUIRender()
{
    // crowbar->GUIRender();
    kunai->GUIRender();
    ModelAnimator::GUIRender();
}

void Human::ClipSync()
{
    // ��� ���� ������ ������ �׼ǰ� �޶�����
    if ((ACTION)frameBuffer->Get().cur.clip != action)
    {
        // �ൿ�� �´� ���� ���
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

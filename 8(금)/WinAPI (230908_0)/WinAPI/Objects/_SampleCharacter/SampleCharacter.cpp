#include "Framework.h"

SampleCharacter::SampleCharacter()
{
    texture = Texture::Add(L"Textures/_SampleCharacter/_SampleCharacter.bmp", 7, 10);
    imageRect = new ImageRect(texture);
    
    size = { 96, 96 }; // 96 : �̹����� ��������Ʈ 1�� ũ�� ����. 1�� ũ�Ⱑ �ٲ� ���, �� �κе� �ٲ��� �Ѵ�
    imageOffset = { 0, 0 }; //ĳ���� ���� ��ġ (��Ʈ) �� ������ �׷��� �׸��� ��ġ�� �ٸ� ���, ���⼭ ������ �ϸ� �ȴ�

    CreateAnimations();   // �ִϸ��̼� ������ ȣ��
    animations[curAction]->Play(); //�ִϸ��̼� "���� �׼�(curAction)" �÷��� �����϶�
                                   // �Լ� ���� : ������ ������� �ִϸ��̼��� Ž���ؼ�
                                   // ù ��° �ڷ���(�׼� �ڵ�)�� ã������ ��� ���۵��� ���ʷ� ���
    BulletManager::Get();
}

SampleCharacter::~SampleCharacter()
{
    delete imageRect;

    for (pair<ActionType, Animation*> animation : animations)
        delete animation.second;
}

void SampleCharacter::Update()
{
    // �� ������ ��� ���� �Լ��� �����ΰ�
    // ������Ʈ������ ȣ�⸸ + ȣ���� ���ؼ� "�� �Լ��� ������ ��Ȳ���� �Ǵܸ�"

    Jump();
    GetHit();
    Die();

    WalkAndRun();

    Attack();
    Attack_Run();

    Attack_GetCombo();
    Attack_InputDelay();

    AutoAnimation();

    // �׸��� ��ġ ����
    imageRect->pos = pos + imageOffset;
    animations[curAction]->Update(); //�ִϸ��̼� ������Ʈ (�ε���++)

    BulletManager::Get()->Update();
}

void SampleCharacter::Render(HDC hdc)
{
    //Rect::LineRender(hdc); //����׿�. ĳ���Ͱ� ������ ������ ���� ���̰� �׸���

    //�̹��� ���
    imageRect->Render(hdc, isLeft, (int)alphaValue, animations[curAction]->GetFrame());

    BulletManager::Get()->Render(hdc);
}

void SampleCharacter::Jump()
{
    // ���� Ƚ���� 2ȸ ����, Ű�� �����̽��� Ȥ�� ȭ��ǥ �� Ű,
    // ������ "���� ��" ������ ��, ���� ���� �ƴ� ��
    // �� ������ ��� �����Ǹ� ������ �ϱ�
    if (jumpCount < 2 && (KEY_DOWN(VK_SPACE)||KEY_DOWN(VK_UP)) &&
        StageManager::Get()->IsPlay() && !isAttacking)
    {
        yVelocity = JUMP_POWER;
        jumpCount++;

        SetAction(JUMP); //�� ȣ��� �׼��� "�� �ֱ�" Ȥ�� "�ڵ� ������ �׼�"���� "����"�� �ٲ��
    }

    // ������ ������� ��(�߷°� �ð��� ���� ���� ����) ����
    yVelocity -= GRAVITY * DELTA;
    pos.y -= yVelocity * DELTA;

    //�Ʒ��� üũ
    Vector2 bottomPos = pos;
    bottomPos.y = Bottom() - BOTTOM_CHECK;
    //�Ʒ��ʰ� �ٴ��� ���踸 ���캸�� (�簢�� �浹 + ���� üũ�� �⺻������ ���� : �Ʒ��ʸ� ������ ��)
    float groundHeight = StageManager::Get()->GetGroundHeight(bottomPos);

    //�ٴ� ���� ������ ���߰�
    if (Bottom() > groundHeight)
    {
        if (yVelocity < 0)
        {
            yVelocity = 0.0f; //�������� �ӵ� 0
            jumpCount = 0;    //������ Ƚ���� 0
            pos.y = groundHeight - Half().y;

            //"���� ������"�� ���? - �ؿ�!
        }
    }
}

void SampleCharacter::Attack()
{
    if (!StageManager::Get()->IsPlay()) return;
    
    if (curAction == RUN) return;
    if (attackInputDelay != 0) return;

    if (KEY_DOWN(VK_RETURN))
    {
        BulletManager::Get()->Fire(pos, mousePos - pos);
    }

    //���콺 ��Ŭ�� ��
    if (KEY_DOWN(VK_LBUTTON))
    {
        switch (attackCount)
        {
        case 0: //������ �� ���� ������
            SetAction(ATTACK_1); //���� ���� ����
            attackCount++; //���� Ƚ���� +1
            attackInputDelay = ATTACK_DELAY; //�Է� ���� �ð��� ���� ���� ������ �����
            isAttacking = true; //"���� ��"�� ������
            break;

        case 1: //������ �� �� ������
            SetAction(ATTACK_2); //�� ��° ����, ���ӱ� ����
            attackCount++;
            attackInputDelay = ATTACK_DELAY;
            isAttacking = true;
            break;

        case 2:
            SetAction(ATTACK_3);
            attackCount++;
            attackInputDelay = ATTACK_DELAY;
            isAttacking = true;
            break;
        }
        //�ߺ� �ڵ带 ���⿡ �����ؼ� ������ ���� ����
        // -> ���⿡ �ڵ尡 ������ ���� Ƚ���� 3, 4, 5....���� ������
        // ���⼭ �ڵ带 ������ �ؼ� ������ ���̰� ����ϱ�
    }
}

void SampleCharacter::Attack_Run()
{
    //�޸��鼭 ���� �ൿ�� ������ �Լ���

    if (!StageManager::Get()->IsPlay()) return;

    if (curAction != RUN) return;
    if (attackInputDelay != 0) return;

    //�޸��� ���߿� ��Ŭ���� �ϸ�
    if (KEY_DOWN(VK_LBUTTON))
    {
        //�޸��� ������ ���� �޺��� ���� (���߿� ������ �߰��� ����)
        SetAction(RUN_ATTACK);
        attackInputDelay = ATTACK_DELAY;
        isAttacking = true;
    }
}

void SampleCharacter::Attack_GetCombo()
{
    if (attackComboCurrentTime < 0)
    {
        attackComboCurrentTime = 0;
        attackCount = 0;
    }

    if (attackComboCurrentTime == 0) return;
    else attackComboCurrentTime -= DELTA;
}

void SampleCharacter::Attack_InputDelay()
{
    if (attackInputDelay < 0)
    {
        attackInputDelay = 0;
    }

    if (attackInputDelay == 0) return;
    else attackInputDelay -= DELTA;
}

void SampleCharacter::WalkAndRun()
{
    if (!StageManager::Get()->IsPlay()) return;


    if (KEY_DOWN(VK_SHIFT))
    {
        if (!isHighProfile) isHighProfile = true;
    }
    
    if (KEY_UP(VK_SHIFT))
    {
        if (isHighProfile) isHighProfile = false;
    }

    if (KEY_PRESS(VK_LEFT))
    {
        if (!isLeft) isLeft = true;

        if (isHighProfile)
        {
            if (OnGround() && curAction != RUN && !isAttacking) SetAction(RUN);

            if (pos.x < WIN_WIDTH / 4 && StageManager::Get()->GetProcess() > 0)
            {
                // �ڵ� �ܼ�ȭ : �������� �Ŵ����� GetSpeed �Լ��� Move ��� ȣ���Ͽ� �ӵ��� ����
                // (Y �ӵ��� �ʿ��� ���, �ش� �Լ��� �Ű������� �߰��մϴ�)
                // Move �Լ��� ���� ���������Ŵ��� �ۿ��� ȣ������ �ʽ��ϴ�.
                // (StagemManager.cpp 74��° ���� �̾ �������ּ���)

                //�̵��ϴ� �ӵ��� ���������Ŵ����� �־�� �ϹǷ�...
                //�̵��� ���� ���� ���� �������� �Ŵ����� ���� �־�� �մϴ�.
                //(�ڵ尡 �پ�� ���, ȣ���� ���� �þ���ϴ�.)

                //�� ���ǵ� : ���� ȣ�� x �ν��Ͻ��� ��� ���� ���� �ٲ۴�
                StageManager::Get()->SetSpeed(WALK_SPEED * RUN_MULT * DELTA * -1);
            }
            else
            {
                if (Left() > 0) //=�������� ���൵�� 0�� �� ��Ȳ
                {
                    StageManager::Get()->SetSpeed(0); //���� �����̹Ƿ� �������� �ӵ� 0���� ����
                    pos.x -= WALK_SPEED * RUN_MULT * DELTA; //���� float ��� ����
                }
            }
                
        }
        else
        {
            if (OnGround() && curAction != WALK && !isAttacking) SetAction(WALK);

            if (pos.x < WIN_WIDTH / 4 && StageManager::Get()->GetProcess() > 0)
            {
                StageManager::Get()->SetSpeed(WALK_SPEED * DELTA * -1);
            }
            else
            {
                if (Left() > 0)
                {
                    StageManager::Get()->SetSpeed(0);
                    pos.x -= WALK_SPEED * DELTA;
                }
            }
        }
    }

    if (KEY_UP(VK_LEFT))
    {
        SetAction(IDLE);
        StageManager::Get()->SetSpeed(0); //�̵��� ���߸�, ���������� 0�� �ӵ��� ����
    }

    if (KEY_PRESS(VK_RIGHT))
    {
        if (isLeft) isLeft = false;

        if (isHighProfile)
        {
            if (OnGround() && curAction != RUN && !isAttacking) SetAction(RUN);

            if (pos.x > WIN_WIDTH * 3 / 4)
            {
                StageManager::Get()->SetSpeed(WALK_SPEED * RUN_MULT * DELTA * 1);
            }
            else
                pos.x += WALK_SPEED * RUN_MULT * DELTA;
        }
        else
        {
            if (OnGround() && curAction != WALK && !isAttacking) SetAction(WALK);
            
            if (pos.x > WIN_WIDTH * 3 / 4)
            {
                StageManager::Get()->SetSpeed(WALK_SPEED * DELTA * 1);
            }
            else
                pos.x += WALK_SPEED * DELTA;
        }
    }

    if (KEY_UP(VK_RIGHT))
    {
        SetAction(IDLE);
        StageManager::Get()->SetSpeed(0);
    }
}

bool SampleCharacter::OnGround()
{
    return (curAction != JUMP) && (curAction != JUMP_DOWN);
}

void SampleCharacter::AutoAnimation()
{
    // (�̺�Ʈ�� ȣ���� �����ϰ�) �������� �� ���ǿ� ���� �ڵ� �ִϸ��̼� ���
    // ���� ����� ���� : ��������
    // �ٸ� ������ �� ������ ���� ���⼭ ���

    if (curAction == HURT || isAttacking) return;
    if (yVelocity > 0.0f) return;

    if (yVelocity < 0.0f)
    {
        SetAction(JUMP_DOWN); //y�� �̵� �ӵ��� 0���� �۾����� = �������� �ڵ����� "������" ���� ���
    }
    else
    {
        //y�� �̵� �ӵ��� 0�̸�
        yVelocity = 0; //Ȯ�λ��
        if (curAction == JUMP || curAction == JUMP_DOWN) SetAction(IDLE);
        // ������ ���� ���� ����, (���� : ���� ���߿���) �׸��� �������� �������� �߿� �ٴ��� ������ "����"�� ����
        // curAction == JUMP : �������� �ö󰡴ٰ� �������� �ٷ� ���ǿ� ���ڴ�
        //                     -> ���ǿ� ���� �ٴ� ������ ���� ���� ���� ���� �� ������ ����� ���� ����
    }
}

void SampleCharacter::GetHit()
{
    if (isGhost) // ���� ���¸�
    {
        //���¾��� �� �����̴� ������ ���Ž�Ŵ (���İ� �ٲٱ�)

        ghostTime += DELTA;

        if (isIncreaseAlpha)
        {
            alphaValue += ALPHA_SPEED * DELTA;
            if (alphaValue > 255.0f)
                isIncreaseAlpha = false;
        }
        else
        {
            alphaValue -= ALPHA_SPEED * DELTA;
            if (alphaValue < 0.0f)
                isIncreaseAlpha = true;
        }

        //���� �ð��� �������� �Ѿ�� ���� ����(=������)�� ����

        if (ghostTime >= GHOST_TIME)
        {
            isGhost = false;
            alphaValue = 255.0f;
        }
        return;
    }

    if (!StageManager::Get()->CollisionObstacle(this))
        return;

    // ���� ���°� �ƴ� ��� (=�¾Ҵµ� ���� ���� ������ �� ������) �Ʒ� �ڵ带 ����
    // ���� ���·� �����

    SetAction(HURT); //�׼��� "��ġ��"�� �ٲٰ�

    StageManager::Get()->Stop(); //������ ��� �ߴ�

    //���� ���� ����
    isGhost = true;
    ghostTime = 0.0f;
    alphaValue = 255.0f;
    isIncreaseAlpha = false; //ó�� ���¿��� ��������� �ͺ��� ����
}

void SampleCharacter::Die()
{
    //�⺻ : ���� ������ �� �ڵ�� ������� �ʽ��ϴ�.
    if (curAction != DEAD) return;

    //�׾��� �� ����� �ڵ尡 �߰��� �߻��ϸ� ���⿡ �ۼ�

    SetAction(DEAD); //�ױ� �׼� ����

    StageManager::Get()->Stop(); //���� ���߱�� ������
}

void SampleCharacter::EndGetHit()
{
    // ���±� ���� �Լ� (�ݹ� ����) : �ִϸ��̼ǿ� ����ߴٰ� ������ ����

    SetAction(IDLE);
    StageManager::Get()->Play();
}

void SampleCharacter::EndAttack()
{
    // ���� ���� �Լ� (�ݹ� ����) �ִϸ��̼ǿ� ����ߴٰ� ������ ����

    SetAction(IDLE);
    attackComboCurrentTime = ATTACK_COMBO; //�޺� ���� ���� (�޺� �Է��� ������)
    isAttacking = false;
}

void SampleCharacter::SetAction(ActionType type)
{
    if (curAction == type) return;

    curAction = type;
    animations[type]->Play();
}

void SampleCharacter::CreateAnimations()
{
    // ���⼭ �ִϸ��̼��� �̸� ���� ����
    // ���� �ڵ����� index, lastIndex �ۼ��ϸ鼭 �����ߴ� ������ ���⼭ ȣ��� ����

    animations[IDLE] = new Animation(texture->GetFrame()); // ����� �׼��� ȣ�� ��, "������ ������"�� �Ҵ� (�ڵ� ���� ����)
    animations[IDLE]->SetPart(35, 39, true); //�ؽ�ó�� �� �� �������� ����� ���ΰ� (���۰� �� ���� + 3��° �Ű������� �ݺ� ����)

    animations[RUN] = new Animation(texture->GetFrame());
    animations[RUN]->SetPart(49, 54, true);

    animations[WALK] = new Animation(texture->GetFrame());
    animations[WALK]->SetPart(63, 69, true);

    animations[JUMP] = new Animation(texture->GetFrame());
    animations[JUMP]->SetPart(42, 45);

    animations[JUMP_DOWN] = new Animation(texture->GetFrame());
    animations[JUMP_DOWN]->SetPart(45, 46);

    animations[HURT] = new Animation(texture->GetFrame());
    animations[HURT]->SetPart(28, 29);
    animations[HURT]->SetEndEvent(bind(&SampleCharacter::EndGetHit, this));
    // �ִϸ��̼��� ���� ��, Ư�� �Լ��� ȣ���ų �� �ִ�
    // �Լ��� ������� ������, ȣ�� ������ �Է��� �ƴ� ���α׷��� ���ǿ� ���� �ڵ� ȣ��ǵ��� ����Ŵ : �ݹ�

    animations[DEAD] = new Animation(texture->GetFrame());
    animations[DEAD]->SetPart(21, 24);

    animations[ATTACK_1] = new Animation(texture->GetFrame());
    animations[ATTACK_1]->SetPart(0, 3);
    animations[ATTACK_1]->SetEndEvent(bind(&SampleCharacter::EndAttack, this));

    animations[ATTACK_2] = new Animation(texture->GetFrame());
    animations[ATTACK_2]->SetPart(7, 11);
    animations[ATTACK_2]->SetEndEvent(bind(&SampleCharacter::EndAttack, this));

    animations[ATTACK_3] = new Animation(texture->GetFrame());
    animations[ATTACK_3]->SetPart(14, 15);
    animations[ATTACK_3]->SetEndEvent(bind(&SampleCharacter::EndAttack, this));

    animations[RUN_ATTACK] = new Animation(texture->GetFrame());
    animations[RUN_ATTACK]->SetPart(56, 60);
    animations[RUN_ATTACK]->SetEndEvent(bind(&SampleCharacter::EndAttack, this));
}

//ĳ���Ͱ� �ϴ� ��
//������ �ִϸ��̼��� �����϶�� �Լ� ȣ��
//������ �ްų� ���ǿ� ���� �̵�, Ȥ�� �ൿ�� ����Ű��

//ĳ���Ͱ� ���� �ʴ� ��
//�׸� ���
//�ִϸ��̼� ���
//���� ���
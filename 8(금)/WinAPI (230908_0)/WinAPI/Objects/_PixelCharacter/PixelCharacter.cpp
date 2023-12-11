#include "Framework.h"

PixelCharacter::PixelCharacter()
{
    //�ؽ�ó ���
    texture = Texture::Add(L"Textures/_SampleCharacter/_SampleCharacter.bmp", 7, 10);
    imageRect = new ImageRect(texture);

    //ũ�� ����
    size = { 96, 96 };
    imageOffset = { 0, 0 };

    //�ִϸ��̼�
    CreateAnimations();
    animations[curAction]->Play();

    //�Ѿ� �Ŵ��� ȣ�� (�Ѿ� �� �غ�)
    BulletManager::Get();

    skyBrush = CreateSolidBrush(RGB(0, 178, 255));
    skyPen = CreatePen(PS_SOLID, 1,RGB(0, 178, 255));
}

PixelCharacter::~PixelCharacter()
{
    delete imageRect;

    for (pair<ActionType, Animation*> animation : animations)
        delete animation.second;

    BulletManager::Delete();
}

void PixelCharacter::Update()
{
    //�ൿȣ��
    Jump();
    Run();
    Fire();

    //���� �ִϸ��̼�
    FallAnimation();

    //��ġ ���߱�
    imageRect->pos = pos + imageOffset;
    animations[curAction]->Update();

    //�Ѿ� ������Ʈ ȣ��
    BulletManager::Get()->Update();
}

void PixelCharacter::Render(HDC hdc)
{
    //�̹��� ���
    imageRect->Render(hdc, isLeft, Alpha(), animations[curAction]->GetFrame());

    BulletManager::Get()->Render(hdc);
}

void PixelCharacter::Jump()
{
    // ���� Ƚ���� 2ȸ ����, Ű�� ȭ��ǥ �� Ű
    if (jumpCount < 2 && KEY_DOWN(VK_UP))
    {
        yVelocity = JUMP_POWER;
        jumpCount++;

        SetAction(JUMP);
    }

    yVelocity -= GRAVITY * DELTA;
    pos.y -= yVelocity * DELTA;

    //�Ʒ��� üũ
    Vector2 bottomPos = pos;
    bottomPos.y = Bottom() - BOTTOM_CHECK;

    //�ٴ� ���� : ���� ������ ũ��� �ӽ� ����
    // float groundHeight = minHeight;

    // �ٴ� ���� : �޾ƿ� ���� ������ �ȼ� �м� ���̷�
    float groundHeight = curLand->GetPixelHeight(pos, RGB(0, 178, 255));

    //�ٴ� ���� ������ ���߰�
    if (Bottom() > groundHeight)
    {
        if (yVelocity < 0)
        {
            yVelocity = 0.0f;
            jumpCount = 0;
            pos.y = groundHeight - Half().y;
        }
    }
}

void PixelCharacter::Run()
{
    if (KEY_PRESS(VK_LEFT))
    {
        if (!isLeft) isLeft = true;

        if (curAction != RUN && !isFiring && yVelocity == 0) SetAction(RUN);
        if (xVelocity == 0) xVelocity = -WALK_SPEED * DELTA;

        if (pos.x < WIN_WIDTH / 3 &&
            currentProcessInScene > 0)
        {
            currentProcessInScene += xVelocity / 10;
        }
        else if (Left() > 0)
        {
            pos.x += xVelocity;
        }
    }

    if (KEY_PRESS(VK_RIGHT))
    {
        if (isLeft) isLeft = false;

        if (curAction != RUN && !isFiring && yVelocity == 0) SetAction(RUN);
        if (xVelocity == 0) xVelocity = WALK_SPEED * DELTA;

        if (pos.x > WIN_WIDTH * 2 / 3 &&
            currentProcessInScene < maxProcessInScene)
        {
            currentProcessInScene += xVelocity / 10;
        }
        else if (Right() < WIN_WIDTH)
        {
            pos.x += xVelocity;
        }
    }

    //if (KEY_UP(VK_LEFT) || KEY_UP(VK_RIGHT))
    if (!KEY_PRESS(VK_LEFT) && !KEY_PRESS(VK_RIGHT))
    {
        if (curAction == RUN) SetAction(IDLE);
        if (xVelocity != 0) xVelocity = 0;
    }
}

void PixelCharacter::Fire()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        isFiring = true;
        SetAction(FIRE);

        //�÷��̾� ��ġ����, ���콺�� �ִ� ��������, �Ѿ� �߻�
        BulletManager::Get()->Fire(pos, mousePos - pos);
    }

    // �� ������, �Ѿ��� ����� ��򰡿� �¾Ҵٸ�?

    // ���� �ε�ģ �Ѿ� ���ϱ� (�� �������� �Ѿ��� �������⵵ �ϰ�)

    GameObject* bullet = BulletManager::Get()->CollisionLand(curLand);

    // ���࿡ �ε�ģ �Ѿ��� �ִٸ�?
    // if (bullet) ��  �̷��� �Ǵµ� bool ������ �ƴ� ����� �ǹ̸� Ȯ���� �صθ� ����
    if (bullet != nullptr)
    {
        // ���⿡ "�ϴ�" ���� ���� �׷����� �ʹ�
        // �귯�ÿ� ���� �ʿ�

        // ��Ʈ ���� (���� �簢��) : �Ѿ��� ��ġ ����
        int _left = bullet->pos.x - 50 + curLand->OffsetX();
        int _right = bullet->pos.x + 50 + curLand->OffsetX();
        int _top = bullet->pos.y - 50 + curLand->OffsetY();
        int _bottom = bullet->pos.y + 50 + curLand->OffsetY();
        
        // �귯�ÿ� ���� ����
        SelectObject(curLand->GetMemDC(bullet->pos), skyBrush);
        SelectObject(curLand->GetMemDC(bullet->pos), skyPen);

        // �Ѿ��� ���� ���� �׸� �׸��� (��, ���彺�������� ��ǥ ���̰� �߻� ����)
        Ellipse(curLand->GetMemDC(bullet->pos), _left, _top, _right, _bottom);
    }
}

void PixelCharacter::Fire_End()
{
    isFiring = false;
    if (yVelocity > 0) SetAction(JUMP);
    else if (yVelocity < 0)  SetAction(JUMP_DOWN);
    else SetAction(IDLE);
}

void PixelCharacter::FallAnimation()
{
    if (yVelocity > 0.0f) return;

    if (yVelocity < 0.0f)
    {
        SetAction(JUMP_DOWN);
    }
    else
    {
        if (curAction == JUMP_DOWN)
        {
            if (isFiring) isFiring = false;
            SetAction(IDLE);
        }
    }
}

void PixelCharacter::SetAction(ActionType type)
{
    if (curAction == type) return;

    curAction = type;
    animations[type]->Play();
}

void PixelCharacter::CreateAnimations()
{
    // �ִϸ��̼� ����

    animations[IDLE] = new Animation(texture->GetFrame());
    animations[IDLE]->SetPart(35, 39, true);

    animations[RUN] = new Animation(texture->GetFrame());
    animations[RUN]->SetPart(49, 54, true);

    animations[JUMP] = new Animation(texture->GetFrame());
    animations[JUMP]->SetPart(42, 45);

    animations[JUMP_DOWN] = new Animation(texture->GetFrame());
    animations[JUMP_DOWN]->SetPart(45, 45);

    animations[FIRE] = new Animation(texture->GetFrame());
    animations[FIRE]->SetPart(14, 15);
    animations[FIRE]->SetEndEvent(bind(&PixelCharacter::Fire_End, this)); //�̺�Ʈ ���ε�
}
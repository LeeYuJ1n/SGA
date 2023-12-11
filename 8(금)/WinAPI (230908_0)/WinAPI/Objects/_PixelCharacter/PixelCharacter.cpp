#include "Framework.h"

PixelCharacter::PixelCharacter()
{
    //텍스처 등록
    texture = Texture::Add(L"Textures/_SampleCharacter/_SampleCharacter.bmp", 7, 10);
    imageRect = new ImageRect(texture);

    //크기 조정
    size = { 96, 96 };
    imageOffset = { 0, 0 };

    //애니메이션
    CreateAnimations();
    animations[curAction]->Play();

    //총알 매니저 호출 (총알 쏠 준비)
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
    //행동호출
    Jump();
    Run();
    Fire();

    //낙하 애니메이션
    FallAnimation();

    //위치 맞추기
    imageRect->pos = pos + imageOffset;
    animations[curAction]->Update();

    //총알 업데이트 호출
    BulletManager::Get()->Update();
}

void PixelCharacter::Render(HDC hdc)
{
    //이미지 출력
    imageRect->Render(hdc, isLeft, Alpha(), animations[curAction]->GetFrame());

    BulletManager::Get()->Render(hdc);
}

void PixelCharacter::Jump()
{
    // 점프 횟수가 2회 이하, 키는 화살표 위 키
    if (jumpCount < 2 && KEY_DOWN(VK_UP))
    {
        yVelocity = JUMP_POWER;
        jumpCount++;

        SetAction(JUMP);
    }

    yVelocity -= GRAVITY * DELTA;
    pos.y -= yVelocity * DELTA;

    //아래쪽 체크
    Vector2 bottomPos = pos;
    bottomPos.y = Bottom() - BOTTOM_CHECK;

    //바닥 높이 : 현재 윈도우 크기로 임시 지정
    // float groundHeight = minHeight;

    // 바닥 높이 : 받아온 지형 정보의 픽셀 분석 높이로
    float groundHeight = curLand->GetPixelHeight(pos, RGB(0, 178, 255));

    //바닥 위면 점프가 멈추게
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

        //플레이어 위치에서, 마우스가 있는 방향으로, 총알 발사
        BulletManager::Get()->Fire(pos, mousePos - pos);
    }

    // 쏜 다음에, 총알이 배경의 어딘가에 맞았다면?

    // 먼저 부딪친 총알 구하기 (그 과정에서 총알이 없어지기도 하고)

    GameObject* bullet = BulletManager::Get()->CollisionLand(curLand);

    // 만약에 부딪친 총알이 있다면?
    // if (bullet) ←  이래도 되는데 bool 조건이 아닌 경우라면 의미를 확실히 해두면 좋다
    if (bullet != nullptr)
    {
        // 여기에 "하늘" 색의 원을 그려보고 싶다
        // 브러시와 펜이 필요

        // 렉트 정보 (가상 사각형) : 총알의 위치 기준
        int _left = bullet->pos.x - 50 + curLand->OffsetX();
        int _right = bullet->pos.x + 50 + curLand->OffsetX();
        int _top = bullet->pos.y - 50 + curLand->OffsetY();
        int _bottom = bullet->pos.y + 50 + curLand->OffsetY();
        
        // 브러시와 펜을 선택
        SelectObject(curLand->GetMemDC(bullet->pos), skyBrush);
        SelectObject(curLand->GetMemDC(bullet->pos), skyPen);

        // 총알이 닿은 곳에 그림 그리기 (단, 랜드스케이프와 좌표 차이가 발생 예상)
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
    // 애니메이션 지정

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
    animations[FIRE]->SetEndEvent(bind(&PixelCharacter::Fire_End, this)); //이벤트 바인딩
}
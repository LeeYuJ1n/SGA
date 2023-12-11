#include "Framework.h"

SampleCharacter::SampleCharacter()
{
    texture = Texture::Add(L"Textures/_SampleCharacter/_SampleCharacter.bmp", 7, 10);
    imageRect = new ImageRect(texture);
    
    size = { 96, 96 }; // 96 : 이미지의 스프라이트 1컷 크기 기준. 1컷 크기가 바뀔 경우, 이 부분도 바뀌어야 한다
    imageOffset = { 0, 0 }; //캐릭터 설정 위치 (렉트) 와 실제로 그려진 그림의 위치가 다를 경우, 여기서 조정을 하면 된다

    CreateAnimations();   // 애니메이션 생성을 호출
    animations[curAction]->Play(); //애니메이션 "현재 액션(curAction)" 플레이 시작하라
                                   // 함수 원리 : 맵으로 만들어진 애니메이션을 탐색해서
                                   // 첫 번째 자료형(액션 코드)로 찾아지는 모든 동작들을 차례로 출력
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
    // 각 동작은 모두 개별 함수로 만들어두고
    // 업데이트에서는 호출만 + 호출을 통해서 "이 함수를 수행할 상황인지 판단만"

    Jump();
    GetHit();
    Die();

    WalkAndRun();

    Attack();
    Attack_Run();

    Attack_GetCombo();
    Attack_InputDelay();

    AutoAnimation();

    // 그림의 위치 갱신
    imageRect->pos = pos + imageOffset;
    animations[curAction]->Update(); //애니메이션 업데이트 (인덱스++)

    BulletManager::Get()->Update();
}

void SampleCharacter::Render(HDC hdc)
{
    //Rect::LineRender(hdc); //디버그용. 캐릭터가 차지한 영역을 눈에 보이게 그리기

    //이미지 출력
    imageRect->Render(hdc, isLeft, (int)alphaValue, animations[curAction]->GetFrame());

    BulletManager::Get()->Render(hdc);
}

void SampleCharacter::Jump()
{
    // 점프 횟수가 2회 이하, 키는 스페이스바 혹은 화살표 위 키,
    // 게임이 "진행 중" 상태일 것, 공격 중이 아닐 것
    // 위 조건이 모두 충족되면 점프를 하기
    if (jumpCount < 2 && (KEY_DOWN(VK_SPACE)||KEY_DOWN(VK_UP)) &&
        StageManager::Get()->IsPlay() && !isAttacking)
    {
        yVelocity = JUMP_POWER;
        jumpCount++;

        SetAction(JUMP); //이 호출로 액션이 "서 있기" 혹은 "자동 설정된 액션"에서 "점프"로 바뀐다
    }

    // 밑으로 끌어내리는 힘(중력과 시간에 의한 무게 적용) 연산
    yVelocity -= GRAVITY * DELTA;
    pos.y -= yVelocity * DELTA;

    //아래쪽 체크
    Vector2 bottomPos = pos;
    bottomPos.y = Bottom() - BOTTOM_CHECK;
    //아래쪽과 바닥의 관계만 살펴보기 (사각형 충돌 + 방향 체크와 기본적으로 같다 : 아래쪽만 보려는 것)
    float groundHeight = StageManager::Get()->GetGroundHeight(bottomPos);

    //바닥 위면 점프가 멈추게
    if (Bottom() > groundHeight)
    {
        if (yVelocity < 0)
        {
            yVelocity = 0.0f; //떨어지는 속도 0
            jumpCount = 0;    //점프한 횟수도 0
            pos.y = groundHeight - Half().y;

            //"점프 끝내기"는 어디에? - 밑에!
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

    //마우스 좌클릭 시
    if (KEY_DOWN(VK_LBUTTON))
    {
        switch (attackCount)
        {
        case 0: //공격을 한 적이 없으면
            SetAction(ATTACK_1); //최초 공격 실행
            attackCount++; //공격 횟수를 +1
            attackInputDelay = ATTACK_DELAY; //입력 지연 시간을 사전 설정 값으로 만들기
            isAttacking = true; //"공격 중"을 참으로
            break;

        case 1: //공격을 한 번 했으면
            SetAction(ATTACK_2); //두 번째 공격, 연속기 실행
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
        //중복 코드를 여기에 공통해서 만들지 않은 이유
        // -> 여기에 코드가 있으면 공격 횟수가 3, 4, 5....등인 경우까지
        // 여기서 코드를 수행을 해서 조작을 꼬이게 만드니까
    }
}

void SampleCharacter::Attack_Run()
{
    //달리면서 공격 행동을 별도의 함수로

    if (!StageManager::Get()->IsPlay()) return;

    if (curAction != RUN) return;
    if (attackInputDelay != 0) return;

    //달리는 도중에 좌클릭을 하면
    if (KEY_DOWN(VK_LBUTTON))
    {
        //달리기 공격은 현재 콤보가 없다 (나중에 있으면 추가할 수도)
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
                // 코드 단순화 : 스테이지 매니저의 GetSpeed 함수를 Move 대신 호출하여 속도를 변경
                // (Y 속도가 필요할 경우, 해당 함수에 매개변수를 추가합니다)
                // Move 함수는 이제 스테이지매니저 밖에서 호출하지 않습니다.
                // (StagemManager.cpp 74번째 줄을 이어서 참고해주세요)

                //이동하는 속도를 스테이지매니저에 주어야 하므로...
                //이동을 하지 않을 때도 스테이지 매니저에 값을 주어야 합니다.
                //(코드가 줄어든 대신, 호출할 곳이 늘어났습니다.)

                //셋 스피드 : 직접 호출 x 인스턴스의 멤버 변수 값만 바꾼다
                StageManager::Get()->SetSpeed(WALK_SPEED * RUN_MULT * DELTA * -1);
            }
            else
            {
                if (Left() > 0) //=스테이지 진행도가 0이 된 상황
                {
                    StageManager::Get()->SetSpeed(0); //가장 왼쪽이므로 스테이지 속도 0으로 리셋
                    pos.x -= WALK_SPEED * RUN_MULT * DELTA; //강제 float 계산 유도
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
        StageManager::Get()->SetSpeed(0); //이동을 멈추면, 스테이지에 0의 속도를 전달
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
    // (이벤트나 호출을 제외하고) 스테이지 내 조건에 의한 자동 애니메이션 재생
    // 현재 적용된 조건 : 자유낙하
    // 다른 조건이 더 있으면 역시 여기서 재생

    if (curAction == HURT || isAttacking) return;
    if (yVelocity > 0.0f) return;

    if (yVelocity < 0.0f)
    {
        SetAction(JUMP_DOWN); //y축 이동 속도가 0보다 작아지면 = 떨어지면 자동으로 "떨어짐" 동작 재생
    }
    else
    {
        //y축 이동 속도가 0이면
        yVelocity = 0; //확인사살
        if (curAction == JUMP || curAction == JUMP_DOWN) SetAction(IDLE);
        // 점프가 끝난 거의 직후, (현재 : 점프 도중에도) 그리고 점프에서 내려오는 중에 바닥을 만나면 "서기"를 실행
        // curAction == JUMP : 발판으로 올라가다가 걸쳐지면 바로 발판에 서겠다
        //                     -> 발판에 발이 붙는 현상을 보고 싶지 않을 때는 이 조건을 지우는 편이 좋다
    }
}

void SampleCharacter::GetHit()
{
    if (isGhost) // 유령 상태면
    {
        //얻어맞았을 때 깜빡이는 정도를 갱신시킴 (알파값 바꾸기)

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

        //유령 시간이 설정값을 넘어서면 유령 상태(=얻어맞음)를 종료

        if (ghostTime >= GHOST_TIME)
        {
            isGhost = false;
            alphaValue = 255.0f;
        }
        return;
    }

    if (!StageManager::Get()->CollisionObstacle(this))
        return;

    // 유령 상태가 아닌 경우 (=맞았는데 아직 유령 적용이 안 됐으면) 아래 코드를 수행
    // 유령 상태로 만들기

    SetAction(HURT); //액션을 "다치기"로 바꾸고

    StageManager::Get()->Stop(); //게임을 잠깐 중단

    //유령 상태 적용
    isGhost = true;
    ghostTime = 0.0f;
    alphaValue = 255.0f;
    isIncreaseAlpha = false; //처음 상태에서 희미해지는 것부터 시작
}

void SampleCharacter::Die()
{
    //기본 : 죽지 않으면 이 코드는 실행되지 않습니다.
    if (curAction != DEAD) return;

    //죽었을 때 실행될 코드가 추가로 발생하면 여기에 작성

    SetAction(DEAD); //죽기 액션 적용

    StageManager::Get()->Stop(); //게임 멈추기는 설정됨
}

void SampleCharacter::EndGetHit()
{
    // 얻어맞기 종료 함수 (콜백 전용) : 애니메이션에 등록했다가 끝나면 실행

    SetAction(IDLE);
    StageManager::Get()->Play();
}

void SampleCharacter::EndAttack()
{
    // 공격 종료 함수 (콜백 전용) 애니메이션에 등록했다가 끝나면 실행

    SetAction(IDLE);
    attackComboCurrentTime = ATTACK_COMBO; //콤보 시작 적용 (콤보 입력이 쉽도록)
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
    // 여기서 애니메이션을 미리 설정 가능
    // 직접 코딩에서 index, lastIndex 작성하면서 진행했던 연산을 여기서 호출로 지정

    animations[IDLE] = new Animation(texture->GetFrame()); // 선언된 액션을 호출 후, "프레임 따오기"를 할당 (코드 형태 고정)
    animations[IDLE]->SetPart(35, 39, true); //텍스처의 몇 번 프레임을 사용할 것인가 (시작과 끝 지정 + 3번째 매개변수는 반복 여부)

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
    // 애니메이션이 끝날 때, 특정 함수를 호출시킬 수 있다
    // 함수는 만들어져 있지만, 호출 시점은 입력이 아닌 프로그램의 조건에 따라 자동 호출되도록 대기시킴 : 콜백

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

//캐릭터가 하는 것
//설정된 애니메이션을 수행하라고 함수 호출
//조작을 받거나 조건에 따라서 이동, 혹은 행동을 일으키기

//캐릭터가 하지 않는 것
//그림 출력
//애니메이션 출력
//지형 출력
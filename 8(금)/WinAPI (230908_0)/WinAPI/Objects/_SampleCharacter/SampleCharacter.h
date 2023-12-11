#pragma once
class SampleCharacter : public Rect
{
private:

    //액션의 열거형. 저번 주에 int 코드로 사용했던
    // "현재 무슨 일을 하고 있는가?"를 나타내는 자료형
    enum ActionType
    {
        IDLE, RUN, WALK, JUMP, JUMP_DOWN,
        HURT, DEAD,
        ATTACK_1, ATTACK_2, ATTACK_3,
        RUN_ATTACK
    };

    //캐릭터의 기본 스탯. 현재는 샘플이라서 참조 전용으로 상수화
    //...나중에 레벨업 같은 방식으로 스탯이 바뀌어야 한다면 const를 지워야 할 수도
    const float WALK_SPEED = 500.0f; //걷는 속도
    const float RUN_MULT = 1.5f;     //달릴 경우 걷는 속도에 곱할 승수

    const float JUMP_POWER = 750.0f; //도약력
    const float GRAVITY = 1500.0f;   //중력값 (밑으로 떨어뜨리는 상수)
    const float BOTTOM_CHECK = 10.0f; //바닥에 발을 걸쳤는가, 그냥 도달을 못 했는가를 판별할 픽셀 기준

    const float GHOST_TIME = 3.0f;        // 맞았을 때 깜빡이는 시간 (=이런 경우 게임이 잠깐 멈추거나, 캐릭터가 무적이 되는 일이 많다)
    const float ALPHA_SPEED = 1000.0f;    // 깜빡이는 속도

    const float ATTACK_DELAY = 0.1f;  //공격 입력이 연달아 일어나지 못하게 하는 행동 지연 시간
    const float ATTACK_COMBO = 0.5f;  //공격 중 혹은 후에 다음 공격이 이어서 발생할 수 있도록 하는 콤보 허용 시간

public:
    SampleCharacter();
    ~SampleCharacter();

    void Update();
    void Render(HDC hdc);

private:
    void Jump();          // 뛰기
    void GetHit();        // 얻어맞기
    void EndGetHit();     // 얻어맞기 종료 (별도 함수)
    void Die();           // 죽기

    void Attack();              // 공격
    void Attack_Run();          // 달리면서 공격 (별도 함수)
    void Attack_GetCombo();     // 콤보 판정
    void Attack_InputDelay();   // 입력 지연 판정
    void EndAttack();           // 공격 종료 (별도 함수)

    bool OnGround();            // (bool 반환형 있는) 캐릭터가 땅 위에 있는가?
    void WalkAndRun();          // 걷고 달리기 (가로 이동)

    void AutoAnimation();               // 자동 애니메이션 (특정 조건에서 입력이나 함수 호출 없이도 액션이 바뀌어야 할 때 : 자유낙하 등)
    void SetAction(ActionType type);    // 액션을 매개변수에 따라 지정하기

    void CreateAnimations();     // (생성자 중에 호출하는) 애니메이션 만들기

private:
    Texture* texture;           // 이 캐릭터가 사용할 아틀라스 텍스처 (=스프라이트 시트)

    ImageRect* imageRect;       // 이 캐릭터의 텍스처가 출력되기 위한 영역 (이미지 영역)
    Vector2 imageOffset;        // 이미지가 어긋난 경우, 위치를 바로잡기 위한 보정치

    map<ActionType, Animation*> animations;   // 애니메이션 모음 (맵)

    ActionType curAction = IDLE; // 현재의 액션

    bool isLeft = false; // 왼쪽을 보고 있는가?

    float yVelocity = 0.0f; // 세로축 이동 속도
    UINT jumpCount = 0;     // 점프한 횟수

    UINT attackCount = 0;               // 공격한 횟수
    float attackInputDelay = 0;         // 현재 입력 지연 상태
    float attackComboCurrentTime = 0;   // 현재 콤보 입력 상태
    bool isAttacking = false;           // 공격 중인가?

    bool isGhost = false;               // 현재 유령 상태인가? (무적, 혹은 일시 정지)
    float ghostTime = 0.0f;             // 현재 유령 상태인 경우, 상태 종료까지 남은 시간

    float alphaValue = 255;             // 현재 투명도 (=투시불가도. "불투명한 정도")
    bool isIncreaseAlpha = false;       // 다음 알파 연산 때 알파가 늘어날 것인가? (깜빡임 계산에 사용)

    bool isHighProfile = false;         // 현재 "소란스러움" 상태인가?
                                        // 소란스러움 = 게임 캐릭터가 행동을 더 크게, 시끄럽게, 격하게 하는 상태
                                        // 공격 -> 강공격, 걷기 -> 달리기, 일반상태 -> 각성상태

    wstring attacks;                    // 로그 : 공격 횟수 등을 기록하고 싶으면 사용해도 되는 변수 (현재 미사용)
};


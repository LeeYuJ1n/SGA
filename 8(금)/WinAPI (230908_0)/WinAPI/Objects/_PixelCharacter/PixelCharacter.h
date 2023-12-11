#pragma once

class PixelCharacter : public Rect
{
    // 픽셀 충돌 씬 전용 간이 샘플 캐릭터
    // 이동, 점프, "총 쏘기"만 따로 떼어놓았습니다!
    // 더 자세한 움직임 코드나 주석 등은 "샘플 캐릭터"를 참조해주세요!
private:

    enum ActionType
    {
        IDLE, RUN, JUMP, JUMP_DOWN, FIRE
    };

    float WALK_SPEED = 700.0f;
    float JUMP_POWER = 700.0f;
    float GRAVITY = 1500.0f;
    float BOTTOM_CHECK = 10.0f;

public:
    PixelCharacter();
    ~PixelCharacter();

    void Update();
    void Render(HDC hdc);

    float GetSpeedX() { return xVelocity; }
    float GetSpeedY() { return yVelocity; }

    // 씬 내 진행도 설정
    // * 이 방법 외에 "카메라" 클래스가 있다면 더 편하게 배치 가능
    //   ....합니다만 현재는 간소화를 위해 단순한 방법을 쓰겠습니다.
    void SetProcessLimit(float value) { maxProcessInScene = value; }
    float GetProcess() { return currentProcessInScene; }

    // 바닥 정보 받기
    void SetLand(Landscape* target) { curLand = target; }

private:
    //이동 (뛰기, 달리기)
    void Jump();
    void Run();

    //쏘기 (총알은 따로 매니저 있음)
    void Fire();
    void Fire_End();

    //자유낙하
    void FallAnimation();

    //애니메이션 제어 (액션 할당, 애니메이션 초기화)
    void SetAction(ActionType type);
    void CreateAnimations();

private:
    //텍스처와 보정
    Texture* texture;
    ImageRect* imageRect;
    Vector2 imageOffset;

    //알파가 바뀌면 여기서 반영해야 하지만...
    int baseAlpha = 255;
    float texAlpha = 1.0f;
    float Alpha() { return (float)baseAlpha * texAlpha; }

    //애니메이션과 액션
    map<ActionType, Animation*> animations;
    ActionType curAction = IDLE;

    //이동 변수 (왼쪽?, 발사여부, 속도, 점프 횟수)
    bool isLeft = false;
    bool isFiring = false;
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    UINT jumpCount = 0;

    //씬 내 진행도 (캐릭터가 제어하고, 씬과 동기화)
    float currentProcessInScene = 0;
    float maxProcessInScene;

    //임시 데이터 : 맨바닥은 어디지?
    float minHeight = WIN_HEIGHT;

    Landscape* curLand;

    HBRUSH skyBrush;
    HPEN skyPen;
};


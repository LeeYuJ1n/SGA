#pragma once

class TestActor : public SphereCollider
{
    // 테스트 캐릭터 (구체 충돌체로부터 상속 받음)
    // : 조작과 최소한의 상호작용이 가능한 3D 물체 만들기

private:
    const float GRAVITY = 9.8f * 10.0f;        // 중력 (캐릭터에 국한하지 않은 스탯) : 필요하면 매크로 빼야 하는 것

public:
    TestActor();
    ~TestActor();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();

    // 지형 세팅용 함수들
    void SetLevel(TerrainEditor* stage) { level = stage; }          // 터레인이 씬에 있으면 지정하고
    void UseBlockManager(bool value) { usingBlockManager = value; } // 블록매니저 싱글턴 쓸 거면 토글하고

private:
    void Control();
    void Jump();

private:
    float moveSpeed = 10.0f;    // 움직이는 속력 (스탯)
    float rotSpeed = 5.0f;      // 회전 속력
    float jumpPower = 20.0f;    // 도약 능력

    float velocity = 0.0f;      // 현재의 속력 (상황)
    bool isJump = false;        // 현재 점프 중인가?

    // 조작 대비용 변수
    Vector3 prevMousePos;       // 가장 최근의 마우스 포인터 위치 (조작)

    // 대응지형 (현재 : 터레인 에디터 기준으로 -> 나중에 필요하면 변경)
    TerrainEditor* level = nullptr;

    // 대응지형 V2 : 블록매니저
    bool usingBlockManager = false;

    // 나중에 UI가 추가되면 이 밑에

    // 조준선 (쓰지 않음)
    // Quad* crosshair;

    //액터 UI
    ActorUI* ui;

    // UI 조작에 쓰기 위한 위치 별도 지정
    // POINT clickCenterPos = { CENTER_X, CENTER_Y };                 // 미리 지정된 센터 매크로값 사용
    // POINT clickCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT / 2 };      // 2로 나누기
    // POINT clickCenterPos = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f}; // 0.5로 곱하기
    POINT clickCenterPos = { WIN_WIDTH >> 1, WIN_HEIGHT >> 1 };       // 비트 한 칸 밀기
};


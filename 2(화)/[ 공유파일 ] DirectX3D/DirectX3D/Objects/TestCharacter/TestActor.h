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

    void SetLevel(TerrainEditor* stage) { level = stage; }

private:
    void Control();
    void Jump();

private:
    float moveSpeed = 10.0f;    // 움직이는 속력 (스탯)
    float rotSpeed = 5.0f;      // 회전 속력
    float jumpPower = 20.0f;    // 도약 능력

    float velocity = 0.0f;      // 현재의 속력 (상황)
    bool isJump = false;        // 현재 점프 중인가?

    //조작 대비용 변수
    Vector3 prevMousePos;       // 가장 최근의 마우스 포인터 위치 (조작)

    //대응지형 (현재 : 터레인 에디터 기준으로 -> 나중에 필요하면 변경)
    TerrainEditor* level = nullptr;

    //나중에 UI가 추가되면 이 밑에

    //조준선
    Quad* crosshair;
};


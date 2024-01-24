#include "Framework.h"

TestActor::TestActor()
{
    Pos() = { 5, 5, 5 }; // 지형 안에 들어갈 수 있도록 미리 좌표를 약간 "안"으로 만들어주기

    //조준선 생성
    crosshair = new Quad(L"Textures/UI/cursor.png");
    crosshair->Pos() = { CENTER_X, CENTER_Y, 0 };

    // 임시 코드 : 조준선이 플레이어를 기준으로 움직이도록
    //crosshair->SetParent(this); // 부모 정하기 : 현재 코드 구성에서는 꼭 필요하진 않지만, 의미상 사용
    //crosshair->Scale() *= 0.05f; //너무 크게 보이지 않게

    crosshair->UpdateWorld();
}

TestActor::~TestActor()
{
    // 이후 포인터 인스턴스가 할당되면 여기서 삭제
}

void TestActor::Update()
{
    Control(); // 컨트롤 하기
    Jump();    // 조건이 맞으면 점프를 하기

    UpdateWorld(); // 충돌체, (있다면) 그래픽, 트랜스폼 정보 등을 업데이트하기

    // 임시 코드 : 뷰포트 문제 해결까지
    // 플레이어 위치, 시점 방향 기준으로 조준선 이동시키기
    //crosshair->Pos() = Pos() + CAM->Forward() * 10.0f;
    //crosshair->Rot() = CAM->Rot(); // 시야 따라 회전하도록
    //crosshair->UpdateWorld();

    // 2D 이미지를 3D 행렬 공간에서 작성 o, 출력도 일부 가능
    // -> 2D 이미지를 활용한 캐릭터 기능의 확장도 가능

    // -> 충돌에 의한 상호작용 / 데이터 자료구조를 활용한 인벤토리 / 2D 이미지와의 연동
    // -> 픽업 인벤토리
}

void TestActor::Render()
{
    Collider::Render(); // 자기는 현재 내보일 그래픽 없음
}

void TestActor::PostRender()
{
    // 모델 내 UI가 있다면 여기서 작성해서 출력
    // 예 : 머리 위 이름표, 체력바, 슈터 게임이면 조준선...
    crosshair->Render();
}

void TestActor::GUIRender()
{
    // 디버그 패널에서 출력하고 싶은 게 있다면 여기서 작성
}

void TestActor::Control()
{
    if (KEY_PRESS('W'))
        // pos.x += UP() .... 의 3차원 버전
        Pos() += Forward() * moveSpeed * DELTA;
    if (KEY_PRESS('S'))
        Pos() += Back() * moveSpeed * DELTA; // Backward가 맞지만 보통 Back이라고 쓴다
    if (KEY_PRESS('A'))
        Pos() += Left() * moveSpeed * DELTA;
    if (KEY_PRESS('D'))
        Pos() += Right() * moveSpeed * DELTA;

    // 점프가 아니면 스페이스 눌렀을 때 점프를 시작하기
    if (!isJump && KEY_DOWN(VK_SPACE))
    {
        velocity = jumpPower; // 현재 속력 = 점프력
        isJump = true;
    }

    // 마우스 커서를 매번 입력 변화 감지해서 따로 판별하기
    Vector3 delta = mousePos - prevMousePos;
    prevMousePos = mousePos; // 가장 최근 커서 위치 다시 갱신

    // 카메라를 마우스에 대응하기 (추적 카메라 기능 필요)
    CAM->Rot().y += delta.x * rotSpeed * DELTA;
    // 마우스 좌우 이동 = 카메라의 세로축 기준 회전 = 좌우 회전
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
    // 마우스 상하 이동 = 카메라의 가로축 기준 회전 = 상하 회전

    // 카메라의 움직임에 캐릭터를 동기화
    Rot().y = CAM->Rot().y;

// 오늘 작성한 추적 카메라에 대해서 복습하면서...

// 1. 추적 카메라와 자유 카메라가 씬에서 토글될 수 있게 해봅시다.
// 2. 자유 카메라 상태에서만 지형 편집을 할 수 있게 해봅시다.
// 3. 추적 카메라 상태에서만 플레이어 조작을 할 수 있게 해봅시다.
}

void TestActor::Jump()
{
    velocity -= GRAVITY * DELTA; // 매 계산마다 속력에서 중력 차감

    Pos().y += velocity * DELTA;

    float height = 0; //기본 높이 = 0
    if (level)        //레벨이 있다면
        height = level->GetHeightByPos(Pos()); // 자기가 있는 위치를 기준으로 지형 높이 구하기

    //도출된 지형에 닿으면 점프 종료
    if (Pos().y - Radius() < height) // 캐릭터 위치 - 구체(충돌체) 반지름보다 땅이 더 높은 상황
        // = 발이 땅에 닿음
    {
        Pos().y = height + Radius();
        
        velocity = 0;
        isJump = false;
    }
}
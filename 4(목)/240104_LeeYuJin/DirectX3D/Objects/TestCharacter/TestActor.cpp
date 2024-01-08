#include "Framework.h"

TestActor::TestActor()
{
    Pos() = { 5, 5, 5 }; // 지형 안에 들어갈 수 있도록 미리 좌표를 약간 "안"으로 만들어주기

    // winAPI 제공 함수 : 모니터 정보를 스크린에 적용해주는 기능
    ClientToScreen(hWnd, &clickCenterPos);
    // ShowCursor(false);
    // 앱 수행 중에 커서를 보일 것인지 여부

    ui = new ActorUI();
}

TestActor::~TestActor()
{
    delete ui;
}

void TestActor::Update()
{
    Control(); // 컨트롤 하기
    Jump();    // 조건이 맞으면 점프를 하기

    UpdateWorld(); // 충돌체, (있다면) 그래픽, 트랜스폼 정보 등을 업데이트하기

    // UI 조작
    // 좌클릭 : 픽 함수   -> 블록 가져오기 호출
    // 우클릭 : 빌드 함수 -> 쌓기 호출
    if (KEY_DOWN(VK_LBUTTON))
        ui->Pick();

    if (KEY_DOWN(VK_RBUTTON))
        ui->Build();

    ui->Update();
    
}

void TestActor::Render()
{
    Collider::Render(); // 자기는 현재 내보일 그래픽 없음
}

void TestActor::PostRender()
{
    // 모델 내 UI가 있다면 여기서 작성해서 출력
    // 예 : 머리 위 이름표, 체력바, 슈터 게임이면 조준선...
    // crosshair->Render();

    ui->PostRender();
}

void TestActor::GUIRender()
{
    ui->GUIRender();
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


    // ---------------------------------

    // 인벤토리나 블록 상호작용이 있다면 여기서 작성

}

void TestActor::Jump()
{
    velocity -= GRAVITY * DELTA; // 매 계산마다 속력에서 중력 차감

    Pos().y += velocity * DELTA;

    float height = 0; //기본 높이 = 0
    if (level)        //레벨이 있다면
        height = level->GetHeightByPos(Pos()); // 자기가 있는 위치를 기준으로 지형 높이 구하기

    if (usingBlockManager)
        height = BlockManager::Get()->GetHeight(Pos());

    //도출된 지형에 닿으면 점프 종료
    if (Pos().y - Radius() < height) // 캐릭터 위치 - 구체(충돌체) 반지름보다 땅이 더 높은 상황
        // = 발이 땅에 닿음
    {
        Pos().y = height + Radius();
        
        velocity = 0;
        isJump = false;
    }
}
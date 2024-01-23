#include "Framework.h"
#include "LoadingScene.h"

LoadingScene::LoadingScene()
{
    //progressBar = new Quad(L"Textures/yellow.png");
    //progressBar->Pos() = { CENTER_X, CENTER_Y / 2 };

    progressBar = new ProgressBar(L"Textures/yellow.png");
    progressBar->SetPosition( { CENTER_X, CENTER_Y/2 } );

    //pressStart = new Quad(L"Textures/start.png");
    pressStart = new Button(L"Textures/start.png");
    pressStart->Pos() = { CENTER_X, CENTER_Y };

    Init(); //생성과 동시에 초기화
}

LoadingScene::~LoadingScene()
{
    delete progressBar;
    delete pressStart;
}

void LoadingScene::Update()
{
    //시간을 체크

    // 시간이 제한을 못 넘었으면 경과시간 따라 누적
    if (timePassed < timeTotal) timePassed += DELTA;

    // 윗줄 계산을 포함하여, 제한시간을 넘겼으면 총 제한시간에 맞추기
    if (timePassed > timeTotal) timePassed = timeTotal;

    // 다시 윗줄 계산을 포함하여, 제한시간을 맞췄다면 여기서 어떤 코드를 작성해야 할 수도...
    if (timePassed == timeTotal)
    {
        if (!pressStart->Active()) pressStart->Active() = true;
    }

    // 지금 여기서 else if 말고 별개의 if를 쓰고 있는 이유 :
    // 각 조건문을 독립시켜서, 차례로 조건이 만족될 경우 1회 업데이트 내에서 모든 연산이 끝났으면 하고 의도했기 때문
    // -> 그래서 한 번에 하나의 연산만을 수행하고 싶다면 반드시 else를 위에 넣어줘야 한다

    // 그리고 위 조건문의 연산이 어떻든, 해당 연산의 결과를 프로그레스 바의 상태에 반영해주자
    progressBar->Scale() = { timePassed / timeTotal, 1 };

    progressBar->Update(); // 위 계산을 업데이트
    pressStart->Update();


    // 씬 매니저가 잘 되고 있는지 확인 입력
    if (LoadComplete())
    {
        if (KEY_DOWN(VK_RETURN))
        {
            SceneManager::Get()->ChangeScene("PlaneScene");
        }
    }
}

void LoadingScene::Render()
{
    progressBar->Render();
    pressStart->Render();
}

void LoadingScene::PostRender() {}

void LoadingScene::Init()
{
    //다음 번에도 초기화 상황에 이루어져야 할 코드가 있다면 여기서

    //일단 스타트 표시는 숨기기부터
    //진행 바 상황 = 크기 조절
    //지나간 시간도 조절

    pressStart->Active() = false;
    progressBar->Scale() = {0, 1};
    timePassed = 0;

    //스타트 그림이 버튼인 경우, 여기에 함수를 할당
    // pressStart->SetEvent(&LoadingScene::StartPlaneScene); // 함수 포인터는 한 클래스의 멤버 변수에서 그대로 뽑아쓰기 힘들다 (추가조치 필요)
    // -> 함수 포인터가 클래스와 어울리지 못하고 있다면, 클래스를 안 쓰면 되겠네? -> 구식으로 돌아가는 것도 방법(C, C++은 그렇다)

    //pressStart->SetEvent(bind(GlobalEvent(), "Start"));
    // bind : c, c++의 호출대상을 void() 혹은 std::function에서 지정한 포인터 형식인 것처럼 결속하는 역할
    //        특히 포인터 위치 위에 매개변수를 붙여서, 해당 매개변수를 호출 시에 미리 지정
    //        따라서 위 함수를 통한 버튼의 event 변수에 "GlobalEvent("Start")" 이 전체 호출이 할당
    //        -> event(); 이렇게만 호출해도 씬매니저의 장면 전환에 매개변수까지 한 세트로 전부 호출

    pressStart->SetEvent(bind(GlobalEvent(), "LoadScene", "PlaneScene"));
    //bind의 대상에 매개변수가 여러 개일 경우 이렇게 차례로 할당

    // -> 단, bind는 매개변수가 있고 그걸 한 세트로 결속시키는 걸 전제로 한다 -> 매개변수가 없는 걸 불러오면 보통 오류
    //    (그리고 매개변수도 없으면 그냥 그대로 쓰는 편이 더 쉽기도 하다)

    // -> bind도 마찬가지로 멤버 함수에는 그대로는 대응이 안 된다 (다음 번에 계속...)

    //progressBar->Scale() = { timePassed / timeTotal, 1 };
}

void LoadingScene::Quit()
{
    // 이 함수는 장면이 끝났을 때 수행할 코드

    // 만약 이 씬이 두 번 다시 재생될 필요가 없다면, 여기서 동적 할당된 변수를 지울 수도...
    // delete progressBar;
    // delete pressStart;

    // 다만 다시 재생될 수 있는 씬에서 이런 삭제 코드를 수행하면 -> 당연히 오류
    // -> 이 경우 삭제를 하지 않거나, 반대로 초기화에서 (생성자 말고) 각 변수를 생성하거나...
}

void LoadingScene::StartPlaneScene()
{
    SceneManager::Get()->ChangeScene("PlaneScene");
}
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
    // pressStart->SetEvent(&LoadingScene::StartPlaneScene); // 함수 포인터는 다른 클래스의 멤버 변수에서 그대로 뽑아쓰기 힘들다 (추가조치 필요)
    // -> 함수 포인터가 클래스와 어울리지 못하고 있다면, 클래스를 안 쓰면 되겠네? -> 구식으로 돌아가는 것도 방법(C, C++은 그렇다)

    // pressStart->SetEvent(bind(GlobalEvent(), "Start"));
    // bind : c, c++의 호출대상을 void() 혹은 std::function에서 지정한 포인터 형식인 것처럼 결속하는 역할
    //        특히 포인터 위치 위에 매개변수를 붙여서, 해당 매개변수를 호출 시에 미리 지정
    //        따라서 위 함수를 통한 버튼의 event 변수에 "GlobalEvent("Start")" 이 전체 호출이 할당
    //        -> event(); 이렇게만 호출해도 씬매니저의 장면 전환에 매개변수까지 한 세트로 전부 호출

    //pressStart->SetEvent(bind(GlobalEvent(), "LoadScene", "PlaneScene"));
    //bind의 대상에 매개변수가 여러 개일 경우 이렇게 차례로 할당

    // -> 단, bind는 매개변수가 있고 그걸 한 세트로 결속시키는 걸 전제로 한다 -> 매개변수가 없는 걸 불러오면 보통 오류
    //    (그리고 매개변수도 없으면 그냥 그대로 쓰는 편이 더 쉽기도 하다)

    // -> bind도 마찬가지로 멤버 함수에는 그대로는 대응이 안 된다

    // -> 그렇다면, bind도, std::function도, 애초에 함수 포인터 자체가 왜 멤버 함수에 적용이 안 될까?
    
    // -> 멤버 함수의 메모리 주소는 그 함수에만 따르는 것이 아니라, 함수가 들어가 있는 클래스...
    //    그리고 그 클래스를 기반으로 한 인스턴스의 메모리 주소를 따르기 때문
    //    -> 다른 말로, 클래스(와 인스턴스, 혹은 합쳐서 "객체")가 먼저 있고 그 안에 함수도 있다
    //    -> 그런데 함수의 메모리 위치를 무작정 지정하면 컴퓨터가 그 기준을 정확히 모르기 때문

    // 이 부분을 해결할 방안 A. 호출의 문제, 함수 이름을 호출할 때부터 클래스 이름을 써주면 된다

    // 예를 들어서 이 클래스의 StartScene이라는
    // 함수를 불러온다면 StartScene(x) &LoadingScene::StartScene (o)

    // 위 방안과 더불어서 (양자 택일 x) 지정의 문제에서도 구체적으로 지정을 해주면 된다

    // -> 변수 지정 단계에서 확실하게 어디에 있는, 그리고 어떤 형태의 함수를 불러올 것인지 명확히 한다

    //예: 클래스(원본)의 함수를 기준으로 삼아서, 해당 클래스의 함수를 포인터로 받는 변수
    std::function<void(LoadingScene&)> testFuncPtr = &LoadingScene::StartPlaneScene;
    // 인스턴스가 필요하다면 인스턴스를 만든 뒤 그 인스턴스의 위치를 넣어도 된다

    // 버튼의 function<void(void*)>를 이용하고, object 변수를 (기준으로) 활용하기
    pressStart->SetObejct(this);
    //pressStart->SetParamEvent(&LoadingScene::StartPlaneScene); // <- void(void*) 부분과 void(LoadingScene&) 충돌 난다
    pressStart->SetParamEvent(bind(&LoadingScene::StartPlaneScene, this)); // void() 에서 () 자리에 this를 채워서 매개변수형 이벤트를 등록
    // -> 이렇게 하면 나중에 이 이벤트가 호출될 때, 인스턴스에 있는 StartPlaneScene 함수를, object로 등록한 인스턴스를 기준으로, 호출



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
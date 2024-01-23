#include "Framework.h"
#include "TempScene.h"

TempScene::TempScene()
{
    //각 장면에는 만들어질 때 한 번만(한 번은) 반드시 수행되어야 할 코드와,
    //씬이 시작될 때마다 수행되어야 할 "초기화" 코드가 각각 역할별로 존재한다

    // 비행기를 만든다 (혹은 씬에 존재해야 할 유, 무형의 개체를 만든다)
    // -> 씬이 만들어질 때 한번만 수행되면 된다
    // 생성과 존재 : 인스턴스 생성 시에 1회 수행
    plane = new Plane();

    // 현재 비행기가 어디에 있다 (혹은 "눈에 보인다, 보이지 않는다")
    // 사건이 존재한다면 해당 사건이 일어났거나 아직 일어나지 않았다
    // 상태와 행동 : 회차가 수행될 때마다 반복 수행

    // -> 이런 코드가 생성자에서 존재해도 될까?
    // -> 이 코드는 생성이 되었을 때 한 번만 수행되는데?

    // 그래서 초기화 코드를 만든 후, 생성자에서 최초로 초기화 함수를 실행해준다
    Init();

    // 앞으로도 초기화 코드가 필요한 경우, 씬이 바뀔 때, 씬 초기화 코드도 같이 불러준다
}

TempScene::~TempScene()
{
    delete plane;
}

void TempScene::Update()
{
    plane->Update();
}

void TempScene::Render()
{
    plane->Render();
}

void TempScene::PostRender()
{

}

void TempScene::Init()
{
    // 씬이 초기화가 된다면 수행해야 할 "초기화 코드"를 넣는다

    // 이를테면 비행기 위치 지정 등. (상태와 사건을 지정)
    plane->Pos() = { CENTER_X / 2, CENTER_Y / 2 };
}

void TempScene::Quit()
{

}
#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    //기본 렉터. 크기를 주면 화면에 나온다
    rect = new Rect({ 0, 0 }, {200, 200});
    rect->Pos() = { (long)CENTER_X, (long)CENTER_Y };
    rect->Active() = true; //활성화를 true로 맞춰준 다음 렌더하면 나온다

    hBrush = CreateSolidBrush(RGB(0, 255, 0));


    //스폰 해보기
    SpawnManager::Get()->spawnObjects.push_back(new SpawnObject()); //"데이터" 만들기
    SpawnManager::Get()->spawnObjects[0]->Spawn(); //만들어진 데이터의 세부 데이터 세팅

    //1번
    SpawnManager::Get()->spawnObjects.push_back(new SpawnObject());
    SpawnManager::Get()->spawnObjects[1]->Spawn();

    //2번
    SpawnManager::Get()->spawnObjects.push_back(new SpawnObject());
    SpawnManager::Get()->spawnObjects[2]->Spawn();
}

TutorialScene::~TutorialScene()
{
    delete rect;

    DeleteObject(hBrush);
}

void TutorialScene::Update()
{
    int width = WIN_WIDTH;
    int height = WIN_HEIGHT;

    if (GetAsyncKeyState(VK_RIGHT)) // 기본 키보드 입력 받기 (제공함수 사용)
    {
        rect->Pos().x += speed;

        if (rect->Pos().x > width - rect->GetSize().x / 2)
            rect->Pos().x = width - rect->GetSize().x / 2;
    }
    if (KEY_DOWN(VK_LEFT)) //키를 누르면 한 번 실행
    {
        rect->Pos().x -= speed;
        if (rect->Pos().x < rect->GetSize().x / 2)
            rect->Pos().x = rect->GetSize().x / 2;
    }
    if (KEY_UP(VK_UP)) //키를 눌렀다가, 뗄 때 한 번 실행
    {
        rect->Pos().y -= speed;
        if (rect->Pos().y < rect->GetSize().y / 2)
            rect->Pos().y = rect->GetSize().y / 2;
    }
    if (KEY_PRESS(VK_DOWN)) //키를 누르는 동안 계속 실행 (제공과 같다)
    {
        rect->Pos().y += speed;

        if (rect->Pos().y > height - rect->GetSize().y / 2)
            rect->Pos().y = height - rect->GetSize().y / 2;
    }

    // 키를 누르면 활성화가 바뀐다?
    if (GetAsyncKeyState('1'))
        rect->Active() = true;
    if (GetAsyncKeyState('2'))
        rect->Active() = false;

    if (KEY_DOWN(VK_LBUTTON)) // VK_LBUTTON : "왼쪽 버튼" = 좌클릭
    {
        toggle = !toggle; //토글 반전
        rect->Active() = toggle;
    }
}

void TutorialScene::Render(HDC hdc)
{
    SelectObject(hdc, hBrush);
    rect->Render(hdc);
    //나중에도 새로운 물건을 그린다면
    //직접 그릴 수도 있지만... 그냥 게임용 오브젝트를 가져와서
    //오브젝트->Render() 이렇게 해도 된다는 것

    //세부 데이터에 따라 스폰된 물체를 렌더
    SpawnManager::Get()->spawnObjects[0]->Render(hdc);
    SpawnManager::Get()->spawnObjects[1]->Render(hdc);
    SpawnManager::Get()->spawnObjects[2]->Render(hdc);
}

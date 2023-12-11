#include "Framework.h"
#include "SpawnBrute.h"

SpawnBrute::SpawnBrute()
{
    srand(GetTickCount64());

    // 기본 렉터. 크기를 주면 화면에 나온다
    rect = new Rect(Vector2(), Vector2(20, 20));
    rect->Pos() = { (long)CENTER_X, (long)CENTER_Y };
    rect->Active() = true; // 활성화를 true로 맞춰준 다음 렌더하면 나온다

    hBrush = CreateSolidBrush(RGB(0, 255, 0));
}

SpawnBrute::~SpawnBrute()
{
    delete rect;

    DeleteObject(hBrush);
}

void SpawnBrute::Update()
{
    int width = WIN_WIDTH;
    int height = WIN_HEIGHT;

    // 마우스를 이 씬의 사각형이(렉트가) 따라다녀야!
    rect->Pos() = mousePos; // 마우스 위치를 사각형 위치가 받게

    // 좌클릭을 했을 때
    if (KEY_DOWN(VK_LBUTTON)) // 마우스 왼쪽 버튼을 누르면
        // * 정확히 말하면 LBUTTON이 진짜로 의미하는 것
        //   = 마우스의 "주 버튼" (결정 버튼, 0번 버튼)
        //   = 마우스의 이 '주'(=0번) 버튼이 왼쪽에 있어서 왼쪽 버튼이라고 명명하는 것
        //   = 그래s서 마우스의 "물리적인 위치"는 생각을 덜 해도 될까요?
    {
        // 사격형을 스폰해봅시다
        SpawnManager::Get()->spawnObjects.push_back(new SpawnObject()); // 새 객체 추가
        SpawnManager::Get()->spawnObjects[SpawnManager::Get()->spawnObjects.size() - 1]->Spawn();
    }
    // * 마우스 주 버튼을 "왼쪽 버튼"이라고 명명하는 것에는 두 가지 의미가 있습니다
    //   1. 입력 하드웨어가 다르다고 가정할 때(터치 스크린) 역시 똑같은 신호만 줄 수 있으면
    //      마우스 좌클릭과 똑같은 연산을 수행시킬 수 있습니다
    //   2. 왼손잡이 프로그래머가 코딩을 하더라도, 코딩은 오른손잡이한테 맞춰줘야 합니다

    for (int i = 0; i < SpawnManager::Get()->spawnObjects.size(); ++i)
    {
        if (SpawnManager::Get()->spawnObjects[i]->IsCollision(rect)) // 부딪치면
        {
            SpawnManager::Get()->spawnObjects[i]->Destroy(); // 파괴하자
            // 위 함수를 부르면 화면에서 스폰된 사각형이 지워집니다

            // 하지만 동적 할당된 요소들 (자기 포함)을 메모리에서 지워주지는 않아요

            // 그래서 이 동적 할당된 요소까지 모두 지우기 위해서 추가 코드
            SpawnObject* toDelete = SpawnManager::Get()->spawnObjects[i]; // 스폰된 오브젝트의 주소 받기
            SpawnManager::Get()->spawnObjects.erase(SpawnManager::Get()->spawnObjects.begin() + i); // 벡터에서 대상 제거
            delete toDelete; // 미리 받아두었던 주소를 삭제(쓰기 가능한 상태로 변환)

            // 위 세 줄까지 진행하면 사각형이 깨끗하게 지워집니다
        }
    }
}

void SpawnBrute::Render(HDC hdc)
{
    SpawnManager::Get()->Render(hdc);
    rect->Render(hdc);
}

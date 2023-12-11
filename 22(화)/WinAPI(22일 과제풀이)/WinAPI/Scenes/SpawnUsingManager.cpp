#include "Framework.h"
#include "SpawnUsingManager.h"
#include <string.h>

SpawnUsingManager::SpawnUsingManager()
{
    // 기본 렉터. 크기를 주면 화면에 나온다
    rect = new Rect({ 0, 0 }, { 200, 200 });
    rect->Pos() = { (long)CENTER_X, (long)CENTER_Y };
    rect->Active() = true; // 활성화를 true로 맞춰준 다음 렌더하면 나온다

    hBrush = CreateSolidBrush(RGB(0, 255, 0));

    // 생성과 동시에 스폰 매니저도 생성
    SpawnManager::Get(); // 호출만 하고 안 쓰는 거지만 괜찮습니다
                         // 쓰는 게 목적이 아니라, "쓰기 전에 만드는 것" 자체가 목적이니까
}

SpawnUsingManager::~SpawnUsingManager()
{
    delete rect;

    DeleteObject(hBrush);
}

void SpawnUsingManager::Update()
{
    int width = WIN_WIDTH;
    int height = WIN_HEIGHT;

    rect->Pos() = mousePos;

    // 이 렉트가 스폰 매니저 관리대상과 부딪치면 관리대상을 삭제
    SpawnManager::Get()->DestoryObject(rect);
    // 함수 이름과 다르게 진짜로 다 지우는 함수가 아니고
    // 매니저 속 사각형을 판별해서 지울지 말지를 구분하는 역할을 합니다

    // 스폰매니저를 갱신
    SpawnManager::Get()->Update();
}

void SpawnUsingManager::Render(HDC hdc)
{
    SelectObject(hdc, hBrush);
    rect->Render(hdc);

    // 스폰매니저 렌더
    SpawnManager::Get()->Render(hdc);
}

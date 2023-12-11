#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND _hWnd)
{
    //this : "현재 생성된 이 인스턴스의"
    this->hWnd = _hWnd;
    hdc = GetDC(_hWnd);

    //장면을 새로 만들기
    //tsc = new TestScene(_hWnd); //현재 윈도우 정보를 넘겨주면서 새 장면 제작
    //asc = new AngleScene(_hWnd);
    //tac = new TimeAndCoord(_hWnd);
    clk = new ClockScene(_hWnd);
}

void GameManager::GetInput(WPARAM _wParam)
{
    clk->GetInput(_wParam); //간접 실행
}

void GameManager::Render()
{
    //tsc->Render();
    //asc->Render();
    clk->Render();
}

void GameManager::Update()
{
    //tsc->Update();
    //asc->Update();
    clk->Update();
}

void GameManager::GetPoint(LPARAM _lParam)
{
    clk->GetPoint(_lParam);
}


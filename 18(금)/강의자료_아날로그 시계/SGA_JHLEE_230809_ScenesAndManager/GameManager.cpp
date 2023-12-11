#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND _hWnd)
{
    //this : "���� ������ �� �ν��Ͻ���"
    this->hWnd = _hWnd;
    hdc = GetDC(_hWnd);

    //����� ���� �����
    //tsc = new TestScene(_hWnd); //���� ������ ������ �Ѱ��ָ鼭 �� ��� ����
    //asc = new AngleScene(_hWnd);
    //tac = new TimeAndCoord(_hWnd);
    clk = new ClockScene(_hWnd);
}

void GameManager::GetInput(WPARAM _wParam)
{
    clk->GetInput(_wParam); //���� ����
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


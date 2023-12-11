#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND _hWnd)
{
	this->hWnd = _hWnd;
	hdc = GetDC(_hWnd);

	tac = new TimeAndCoord(_hWnd);
}

void GameManager::GetInput(WPARAM _wParam)
{
	tac->GetInput(_wParam);
}

void GameManager::Render()
{
	tac->Render();
}

void GameManager::Update()
{
	tac->Update();
}

void GameManager::GetPoint(LPARAM _lParam)
{
	tac->GetPoint(_lParam);
}
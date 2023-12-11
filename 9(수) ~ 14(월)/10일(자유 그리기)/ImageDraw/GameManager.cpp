#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND _hWnd)
{
	this->hWnd = _hWnd;
	hdc = GetDC(_hWnd);

	tdr = new TankDraw(_hWnd);
}

void GameManager::GetInput(WPARAM _wParam)
{
	tdr->GetInput(_wParam);
}

void GameManager::Render()
{
	tdr->Render();
}

void GameManager::Update()
{
	tdr->Update();
}
#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND _hWnd)
{
	// this : ���� ������ �� �ν��Ͻ���
	this->hWnd = _hWnd;
	hdc = GetDC(_hWnd);

	// ����� ���� �����
	// tsc = new TestScene(_hWnd); // ���� ������ ������ �Ѱ��ָ鼭 �� ��� ����
	// asc = new AngleScene(_hWnd);
	tac = new TimeAndCoord(_hWnd);
}

void GameManager::GetInput(WPARAM _wParam)
{
	// tsc->GetInput(_wParam); // ���� ����
	// asc->GetInput(_wParam); // ���� ����
	tac->GetInput(_wParam);
}

void GameManager::Render()
{
	// tsc->Render();
	// asc->Render();
	tac->Render();
}

void GameManager::Update()
{
	// tsc->Update();
	// asc->Update();
	tac->Update();
}

void GameManager::GetPoint(LPARAM _lParam)
{
	// tsc->GetPoint(_lParam);
	// asc->GetPoint(_lParam);
	tac->GetPoint(_lParam);
}
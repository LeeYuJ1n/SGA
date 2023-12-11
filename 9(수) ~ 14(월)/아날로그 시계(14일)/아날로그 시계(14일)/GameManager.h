#pragma once
#include <Windows.h>

// Çì´õ
#include "TimeAndCoord.h"

class GameManager
{
private:
	GameManager() {}
	~GameManager() {}

	static GameManager* instance;

public:
	static GameManager* Get()
	{
		if (instance == nullptr)
		{
			instance = new GameManager();
			return instance;
		}
		return instance;
	}

	void Delete()
	{
		delete instance;
	}

	void Init(HWND _hWnd);
	void GetInput(WPARAM _wParam);
	void Render();
	void Update();
	void GetPoint(LPARAM _lParam);

private:
	TimeAndCoord* tac;

	WPARAM wParam;

	HWND hWnd;
	HDC hdc;
};


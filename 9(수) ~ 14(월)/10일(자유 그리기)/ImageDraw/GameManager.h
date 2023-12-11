#pragma once
#include <Windows.h>
#include "TankDraw.h"

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

private:
	TankDraw* tdr;
	HWND hWnd;
	WPARAM wParam;
	HDC hdc;
};


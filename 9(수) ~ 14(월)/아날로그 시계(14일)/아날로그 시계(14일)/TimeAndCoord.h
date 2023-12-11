#pragma once
#include <Windows.h>
#include <math.h>

// Çì´õ

class TimeAndCoord
{
public:
	TimeAndCoord(HWND _hWnd);

	void GetInput(WPARAM _wParam);
	void GetPoint(LPARAM _lParam);
	void Render();
	void Update();

private:
	WPARAM wParam;
	HWND hWnd;
	HDC hdc;

	float pointX;
	float pointY;

	WCHAR lstr[101];

	RECT rect1 = { 100, 100, 500, 500 };
	RECT rect2 = { 0, 0, 0, 0 };

	int number;
	RECT rect3 = { 300, 300, 200, 200 };

	SYSTEMTIME st;

	float x0;
	float y0;
	float x2;
	float y2;
	float x3;
	float y3;

	float GetRadian(float degree) { return (degree / 180) * 3.141592f; }
};


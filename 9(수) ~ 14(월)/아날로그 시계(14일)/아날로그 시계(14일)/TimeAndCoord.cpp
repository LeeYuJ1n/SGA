#include "TimeAndCoord.h"

TimeAndCoord::TimeAndCoord(HWND _hWnd)
{
	this->hWnd = _hWnd;
	hdc = GetDC(_hWnd);
	number = 0;
}

void TimeAndCoord::GetInput(WPARAM _wParam)
{

}

void TimeAndCoord::GetPoint(LPARAM _lParam)
{
	pointX = (float)LOWORD(_lParam);
	pointY = (float)LOWORD(_lParam);

	rect2.left = pointX - 10;
	rect2.right = pointX + 10;
	rect2.top = pointY - 10;
	rect2.bottom = pointY + 10;

	InvalidateRect(hWnd, NULL, true);
}

void TimeAndCoord::Render()
{
	Ellipse(hdc, rect1.left, rect1.top, rect1.right, rect1.bottom);
	DrawText(hdc, lstr, -1, &rect1, 0);

	Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);

	DrawText(hdc, TEXT("%d", number), -1, &rect3, 0);

	x0 = 300;
	y0 = 300;
	x2 = x0 + (cos(GetRadian((st.wSecond - 59) * 6)) * 100);
	y2 = y0 + (-sin(GetRadian((st.wSecond - 59) * 6)) * 100);
	x3 = x0 + (cos(GetRadian((st.wSecond - 59) * 6)) * 100);
	y3 = y0 + (-sin(GetRadian((st.wSecond - 59) * 6)) * 100);

	MoveToEx(hdc, x0, y0, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);

}

void TimeAndCoord::Update()
{
	number++;

	GetLocalTime(&st); // 현재 시간을 불러와서 변수에 저장을 해준다
	// 이 구조체에서 볼 수 있는 자료
	st.wYear;
	st.wMonth;
	st.wDay;
	st.wHour;
	st.wMinute;
	st.wSecond;
	InvalidateRect(hWnd, NULL, true);
}
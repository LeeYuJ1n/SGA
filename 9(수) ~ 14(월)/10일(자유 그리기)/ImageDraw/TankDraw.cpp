#include "TankDraw.h"

TankDraw::TankDraw(HWND _hWnd)
{
	this->hWnd = _hWnd;
	hdc = GetDC(_hWnd);
}

void TankDraw::GetInput(WPARAM _wParam)
{
	switch (_wParam)
	{
		// 화살표키 입력을 받았다면 어떻게 할 것인가
	case VK_UP:
		if (text_y > 10)
		{
			text_y -= 10;
		}
		else if (text_y < 10){}
		break;

	case VK_DOWN:
		if (text_y < 680)
		{
			text_y += 10;
		}
		else if (text_y > 680){}
		break;

	case VK_LEFT:
		if (text_x > 10)
		{
			text_x -= 10;
		}
		else if (text_x < 10){}
		break;

	case VK_RIGHT:
		if (text_x < 850)
		{
			text_x += 10;
		}
		else if (text_x > 850){}
		break;
	}

	// 입력에 의한 정보 갱신을 반영하고, 오래된 화면 무효화
	InvalidateRect(hWnd, NULL, true);
}

void TankDraw::Render()
{
	// -----------------------------------------------------

	// 9일 과제

	Rectangle(hdc, rectMap.left, rectMap.top, rectMap.right, rectMap.bottom);

	// -----------------------------------------------------
	
	// 10일 과제 
	
	// 도로

	// 직선
	MoveToEx(hdc, 10, 300, NULL); // 위 직선 시작 위치
	LineTo(hdc, 1200, 300); // 도로 윗줄

	MoveToEx(hdc, 10, 600, NULL); // 아래 직선 시작 위치
	LineTo(hdc, 1200, 600);

	// 사각형
	HBRUSH brush4 = CreateSolidBrush(RGB(0, 0, 0));
	HGDIOBJ oldbrush4 = SelectObject(hdc, brush4);
	Rectangle(hdc, rect16.left, rect16.top, rect16.right, rect16.bottom);
	Rectangle(hdc, rect17.left, rect17.top, rect17.right, rect17.bottom);
	Rectangle(hdc, rect18.left, rect18.top, rect18.right, rect18.bottom);
	Rectangle(hdc, rect19.left, rect19.top, rect19.right, rect19.bottom);
	Rectangle(hdc, rect20.left, rect20.top, rect20.right, rect20.bottom);
	SelectObject(hdc, oldbrush4);
	DeleteObject(brush4);

	// -----------------------------------------------------

	Rectangle(hdc, rect1.left, rect1.top, rect1.right, rect1.bottom);
	hBrush = CreateSolidBrush(RGB(80, 80, 80));
	FillRect(hdc, &rect1, hBrush);

	Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);
	hBrush = CreateSolidBrush(RGB(100, 70, 20));
	FillRect(hdc, &rect2, hBrush);

	Rectangle(hdc, rect3.left, rect3.top, rect3.right, rect3.bottom);
	hBrush = CreateSolidBrush(RGB(100, 70, 20));
	FillRect(hdc, &rect3, hBrush);

	Ellipse(hdc, rect4.left, rect4.top, rect4.right, rect4.bottom);
	Ellipse(hdc, rect5.left, rect5.top, rect5.right, rect5.bottom);
	Ellipse(hdc, rect6.left, rect6.top, rect6.right, rect6.bottom);
	Ellipse(hdc, rect7.left, rect7.top, rect7.right, rect7.bottom);
	Ellipse(hdc, rect8.left, rect8.top, rect8.right, rect8.bottom);
	Ellipse(hdc, rect9.left, rect9.top, rect9.right, rect9.bottom);

	DrawText(hdc, L"김유준 - 도화가의 탱크", -1, &rect10, 0);

	TextOut(hdc, text_x, text_y, L"도화가", 3);

	// -----------------------------------------------------

	//10일 과제

	
	
	// 건물
	HBRUSH brush1 = CreateSolidBrush(RGB(102, 51, 0));
	HGDIOBJ oldBrush1 = SelectObject(hdc, brush1);

	// 건물 1
	Rectangle(hdc, rect11.left, rect11.top, rect11.right, rect11.bottom);

	// 건물 2
	Rectangle(hdc, rect13.left, rect13.top, rect13.right, rect13.bottom);

	SelectObject(hdc, oldBrush1);    // 아까 출력된 기본 출력도구 반환
	DeleteObject(brush1);            // 브러시 복구와 삭제

	// 건물 문
	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 0));
	HGDIOBJ oldBrush2 = SelectObject(hdc, brush2);
	Rectangle(hdc, rect12.left, rect12.top, rect12.right, rect12.bottom);
	Rectangle(hdc, rect14.left, rect14.top, rect14.right, rect14.bottom);
	SelectObject(hdc, oldBrush2);
	DeleteObject(brush2);
	
	// 태양
	HPEN pen1 = CreatePen(PS_SOLID, 10, RGB(255, 153, 153));
	HGDIOBJ oldPen1 = SelectObject(hdc, pen1);
	HBRUSH brush3 = CreateSolidBrush(RGB(255, 0, 0));
	HGDIOBJ oldBrush3 = SelectObject(hdc, brush3);

	Ellipse(hdc, rect15.left, rect15.top, rect15.right, rect15.bottom);
	SelectObject(hdc, oldBrush3);
	DeleteObject(brush3);
	SelectObject(hdc, oldPen1);
	DeleteObject(pen1);

	// -----------------------------------------------------
}

void TankDraw::Update()
{
	
}
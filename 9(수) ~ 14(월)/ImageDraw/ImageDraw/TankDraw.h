#pragma once
#include <Windows.h>

class TankDraw
{
public:
	TankDraw(HWND _hWnd);

	void GetInput(WPARAM _wParam);
	void Render();
	void Update();

private:
	WPARAM wParam;
	HWND hWnd;
	HDC hdc;
	HBRUSH hBrush;

	int text_x = 500;
	int text_y = 500;

	// -----------------------------------------------------
	
	// 9�� ����
	
	// ��
	RECT rectMap = { 10, 10, 1200, 700 };
	
	// ��ũ ��
	RECT rect1 = { 100, 100, 400, 150 };

	// ��ũ �Ӹ�
	RECT rect2 = { 390, 50, 700, 200 };

	// ��ũ ����
	RECT rect3 = { 80, 190, 800, 300 };
	
	// ��ũ ����
	RECT rect4 = { 80, 350, 200, 250 };
	RECT rect5 = { 200, 350, 320, 250 };
	RECT rect6 = { 320, 350, 440, 250 };
	RECT rect7 = { 440, 350, 560, 250 };
	RECT rect8 = { 560, 350, 680, 250 };
	RECT rect9 = { 680, 350, 800, 250 };
	
	// TextDraw(������ - ��ȭ���� ��ũ)
	RECT rect10 = { 1000, 670, 1200, 750 };

	// --------------------------------------------------

	// 10�� ����

	// �ǹ�(�簢��)
	RECT rect11 = { 870, 100, 1000, 300 }; // �ǹ�
	RECT rect12 = { 900, 190, 970, 300 }; // �ǹ� ��

	// �ǹ� 2(�簢��)
	RECT rect13 = { 1030, 100, 1160, 300 }; // �ǹ� 2
	RECT rect14 = { 1060, 190, 1130, 300 }; // �ǹ� �� 2

	// �¾�(Ÿ��, ��)
	RECT rect15 = { 10, 10, 100, 100 };

	// ���� ����
	RECT rect16 = { 10, 400, 200, 450 };
	RECT rect17 = { 250, 400, 440, 450 };
	RECT rect18 = { 490, 400, 680, 450 };
	RECT rect19 = { 730, 400, 920, 450 };
	RECT rect20 = { 970, 400, 1160, 450 };


	// -----------------------------------------------------
};


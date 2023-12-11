#include "TimeAndCoord.h"

TimeAndCoord::TimeAndCoord(HWND _hWnd)
{
	this->hWnd = _hWnd;      // ����� ������(��)
	hdc = GetDC(_hWnd);      // ����� ���(�ϵ����)

	number = 0;
}

void TimeAndCoord::GetInput(WPARAM _wParam)
{

}

void TimeAndCoord::GetPoint(LPARAM _lParam)
{
	// ���ӸŴ����� ���ؼ� �������� l-�Ű����� (=long, �� ������ �Ű����� �޽���) ����

	// ��ǥ
	pointX = (float)LOWORD(_lParam);
	pointY = (float)HIWORD(_lParam);

	// �� �ڵ��� �ǹ� : lParam�� �����쿡�� �� �޽����� �߻����� �� 
	//                 �Ű������� ó���ϴ� "ū �뷮" ��� �����͸� ��Ī (long)
	//                 ���콺 �Է¿��� �� �Ű������� ���̴µ�, ���콺�� ��� �ִ���
	//                 �巡�׸� ������ �巡�װ� ���� � ������� ���� �ȿ� ��´�
	//                 (�ݴ�� "���� �뷮" �� Ű �Է�, ���콺 1ȸ Ŭ�� ���� wParam) (w�� word)

	// ���콺 �Է��� ���� ���� �ٽ� �̷��� ���� "��" �з����͸� �м��ؼ�
	// ��Ǳ��("���� �ڸ�")��  x��, �޺κ��� y�� �����Ѵ�
	// �׷��� WORD�� ��¥ �ڷ����� int�̹Ƿ� ����߿� ������ ���̷��� float���� ����ȯ

	// �� ����Ʈ�� �Ἥ ��ǥ����� �غ��ô�
	
	// �ؽ�Ʈ�� ó������ ������ �Ϸ��� string �ڷ����� �������� ������ ������ �ִ�
	// �� �׳� �� �ٷ� ��¥ ����

	lstrcpy(lstr, TEXT("X : %f, Y : %f", pointX, pointY));
	// lstrcpy : c++ �� c���� ����ߴ� ���ڿ� ���� �Լ��� Ȯ��. 2 Ȥ�� 3����Ʈ �����ڵ忡 �����ϱ� ����
	// TEXT : char Ȥ��wchar ���ڿ��� �� ������Ʈ�� �´� �����ڵ� ���ڿ��� �ٲ��ִ� ��ũ��
	// %f : (%d, %s ��� ����������) ���⿡ ���� �����͸� �����Ѵٴ� �ǹ��� ���Ĺ���. f�� �Ҽ�

	// Ŭ���� ���� �߽��� �簢�� ����
	rect2.left = pointX - 10;
	rect2.right = pointX + 10;
	rect2.top = pointY - 10;
	rect2.bottom = pointY + 10;

	// ����� �����Ͱ� ����������� ȭ�� ��ȿȭ (���� ��ħ)
	InvalidateRect(hWnd, NULL, true);
}

void TimeAndCoord::Render()
{
	// �׸� �����Ͱ� ������ �׸� ����
	// Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
	// DrawText(hdc, logCoord.c_str(), -1, &rect, 0);
	//��Ʈ�� �ڷ��� ���� + c_str() �Լ� = ��Ʈ�� �ڷ����� �����ڵ忡 ���� ���ڿ�(wchar, chat_t)�� �ٲ��ݴϴ�.

	// Ŭ���� ���� �߽��� �簢�� ���
	// Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);

	// 1�ʸ��� ���ŵ� ����
	DrawText(hdc, logTime.c_str(), -1, &rect3, 0);

	// --------------------------------------------------------

	// 2023�� 8�� 14�� ���� : �Ƴ��α� �ð� �׸���

	// �� �׸���
	Ellipse(hdc, rectEx0814.left, rectEx0814.top, rectEx0814.right, rectEx0814.bottom);

	// �ð� ����
	TextOut(hdc, 293, 210, L"12", 2);    // 12��
	TextOut(hdc, 380, 293, L"3", 2);     // 3��
	TextOut(hdc, 293, 380, L"6", 2);     // 6��
	TextOut(hdc, 210, 293, L"9", 2);     // 9��

	// 1�ʸ��� ���ŵǴ� ���� �׸���
	x0 = 300;
	y0 = 300;
	x2 = x0 + (cos(GetRadian(-secondDegree * 6)) * 30);
	y2 = y0 + (-sin(GetRadian(-secondDegree * 6)) * 30);

	HPEN pen1 = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	HGDIOBJ oldPen1 = SelectObject(hdc, pen1);

	MoveToEx(hdc, x0, y0, NULL);
	LineTo(hdc, x2, y2);

	SelectObject(hdc, oldPen1);
	DeleteObject(pen1);

	x2 = x0 + (cos(GetRadian(-minutesDegree * 6)) * 50);
	y2 = y0 + (-sin(GetRadian(-minutesDegree * 6)) * 50);

	HPEN pen2 = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HGDIOBJ oldPen2 = SelectObject(hdc, pen2);

	MoveToEx(hdc, x0, y0, NULL);
	LineTo(hdc, x2, y2);

	SelectObject(hdc, oldPen2);
	DeleteObject(pen2);

	x2 = x0 + (cos(GetRadian(-hourDegree * 30)) * 70);
	y2 = y0 + (-sin(GetRadian(-hourDegree * 30)) * 70);

	HPEN pen3 = CreatePen(PS_SOLID, 3, RGB(100, 0, 100));
	HGDIOBJ oldPen3 = SelectObject(hdc, pen3);

	MoveToEx(hdc, x0, y0, NULL);
	LineTo(hdc, x2, y2);

	SelectObject(hdc, oldPen3);
	DeleteObject(pen3);


	// --------------------------------------------------------

	// 1�ʸ��� ���ŵǴ� ���� �׸���
	// x0 = 300;
	// y0 = 300;
	// x2 = x0 + (cos(GetRadian(-secondDegree * 6)) * 150);
	// y2 = y0 + (-sin(GetRadian(-secondDegree * 6)) * 150);

	// MoveToEx(hdc, x0, y0, NULL);
	// LineTo(hdc, x2, y2);
}

void TimeAndCoord::Update()
{
	// 1�ʸ��� ���⼭ ������Ʈ �Լ� ����
	number++;

	GetLocalTime(&st); // ���� �ð��� �ҷ��ͼ� ������ ������ ���ش�
	// �� ����ü���� �� �� �ִ� �ڷ�
	st.wYear;   // ��
	st.wMonth;  // ��
	st.wDay;    // ��¥
	st.wHour;   // �ð�
	st.wMinute; // ��
	st.wSecond; // ��
	// �� �ڷḦ WORD, �� int�� Ȯ�� ����

	secondDegree = st.wSecond + 45.0f;
	minutesDegree = st.wMinute + 60.0f;
	hourDegree = st.wHour + 60.0f;

	// ������ �� �Լ�����

	// ���⼭�� ȭ�� ��ȿȭ
	InvalidateRect(hWnd, NULL, true);
}
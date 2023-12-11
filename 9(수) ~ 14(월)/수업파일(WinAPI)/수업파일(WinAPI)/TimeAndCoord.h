#pragma once
#include <Windows.h>
#include <math.h>
#include <string>

using namespace std;

class TimeAndCoord
{
public:
	TimeAndCoord(HWND _hWnd);
	void GetInput(WPARAM _wParam); // �Է� �ޱ�
	void GetPoint(LPARAM _lParam); // "����Ʈ" �ޱ�
	void Render();
	void Update();

private:
	// �� ���� ���� ���̳�?
	// �� �ϳ��� ���� ������ ������ ��ǥ�� Ȯ���ϱ� ���� ��
	// �� �ι�°�� ���⼭ �ð��� �޾Ƽ� ����� �غ���

	// �� ù ��°, ��ǥ�� ��� Ȯ���� ���ΰ�?
	//   1. �ڵ忡�� ���, �����ؼ� ȭ������ Ȯ���غ��� �ȴ�
	//   2. �����츦 ���콺�� ������ ����� ��½��Ѻ��� �ȴ�
	//   �� ���콺 �Էµ� �޾ƺ��ô�

	// ���콺 ��ǥ�� �������� ������ ���� �Ǵ°�? �� ������ ���ν������� ���ư��� �Ѵ�
	// �ű⼭ ���콺 �Է��� �ް� ������� ������ ����� �Ѵ�

	// ���ӸŴ������� ���ο� �Լ��� �ʿ��ϰڴ�

	WPARAM wParam;

	// �ʱ�ȭ�� �� ��...ȭ���� ��� ��������? ������� ����?
	HWND hWnd; // � �����쿡 ����ұ�? (�ü�� ���� ����)
	HDC hdc;    // � ȭ��(�ϵ����)���� ����ұ�? (������ ��� ����)

	// �߰� ����
	float pointX;
	float pointY;

	// ���ڿ�
	WCHAR lstr[101];

	RECT rect = {0, 0, 300, 300};
	RECT rect2 = {0, 0, 0, 0};

	// ������Ʈ Ȯ�ο� ������ ���ڿ�
	int number;
	RECT rect3 = {300, 300, 600, 600}; // ���� ���ϴ�, 4��и� ��ġ��

	// �� ���� ���� �ð� ����
	SYSTEMTIME st;

	float x2;
	float y2; // x, y ��ǥ (�ι�°)
	float x0;
	float y0;// x, y ��ǥ (����)

	// �������� ȣ���� �̾� �����ϴ� �Լ�
	float GetRadian(float degree) { return (degree / 180) * 3.141592f; }

	// ��Ʈ�� �ڷ����� ����� ���ڿ� #include <string> �ʿ�
	std::wstring logCoord;
	std::wstring logTime;

	// ------------------------------------------

	// 2023�� 8�� 14�� ���� : �Ƴ��α� �ð� �׸���

	float hourDegree;
	float minutesDegree;
	float secondDegree;

	RECT rectEx0814 = { 200, 200, 400, 400 };

	// ------------------------------------------
};


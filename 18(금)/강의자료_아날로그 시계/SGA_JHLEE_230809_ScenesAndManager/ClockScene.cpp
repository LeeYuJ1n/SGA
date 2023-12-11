#include "ClockScene.h"

ClockScene::ClockScene(HWND _hWnd)
{
	hWnd = _hWnd;
	hdc = GetDC(_hWnd);

	// ���� (�ð� ��ġ)�� ����
	origin.x = 300;
	origin.y = 300;

	//12 ��ġ (y������ -�Ÿ�)
	rect12 = { origin.x - 10 , origin.y - 10 - charDistance, origin.x + 10 , origin.y + 10 - charDistance};
	//3 ��ġ (x������ +�Ÿ�)
	rect3 = { origin.x - 10 + charDistance , origin.y - 10, origin.x + 10 + charDistance , origin.y + 10 };
	//6 ��ġ (y������ +�Ÿ�)
	rect6 = { origin.x - 10 , origin.y - 10 + charDistance, origin.x + 10 , origin.y + 10 + charDistance };
	//9 ��ġ (y������ -�Ÿ�)
	rect9 = { origin.x - 10 - charDistance , origin.y - 10, origin.x + 10 - charDistance , origin.y + 10 };

	dateRect = { 0, 0, 50, 20 };
	timeRect = { 0, 20, 50, 40 };

	//----------------------------------------------

	//�����ڿ� ������Ʈ ���� (���� 1ȸ) ����

	// (���� 1) �ð� �����͸� �ޱ�
	GetLocalTime(&systemTime);

	// (���� 2) �޾Ƴ� �ð� �����Ϳ��� �ؽ�Ʈ �����ϱ�
	//          Ȯ�ο� �� ������ ��¿�

	timeText = std::to_wstring(systemTime.wHour) + L"�� "
		+ std::to_wstring(systemTime.wMinute) + L"�� "
		+ std::to_wstring(systemTime.wSecond) + L"�� ";
		// + std::to_wstring(systemTime.wMilliseconds) + L"�и���";

	dateText = std::to_wstring(systemTime.wYear) + L"�� "
		+ std::to_wstring(systemTime.wMonth) + L"�� "
		+ std::to_wstring(systemTime.wDay) + L"�� "
		+ DayofWeek(systemTime.wDayOfWeek); //����



	// �ɼ� : 12�ñ��� �� ��������
	ReadyFullHour();
}

void ClockScene::GetInput(WPARAM _wParam)
{

}

void ClockScene::GetPoint(LPARAM _lParam)
{

}

void ClockScene::Render()
{
	// (���� 4) ����


	// ������ �� �ϳ� �׸���

	Ellipse(hdc, origin.x - 220, origin.y - 220, origin.x + 220, origin.y + 220);

	//--------------------------------------


	//�ؽ�Ʈ (�ð����� �� 12, 3, 6, 9 �����)

	DrawText(hdc, dateText.c_str(), -1, &dateRect, DT_NOCLIP);
	DrawText(hdc, timeText.c_str(), -1, &timeRect, DT_NOCLIP);

	DrawText(hdc, cha12.c_str(), -1, &rect12, DT_NOCLIP);
	DrawText(hdc, cha3.c_str(), -1, &rect3, DT_NOCLIP);
	DrawText(hdc, cha6.c_str(), -1, &rect6, DT_NOCLIP);
	DrawText(hdc, cha9.c_str(), -1, &rect9, DT_NOCLIP);

	// �ɼ� : 12�ñ��� �� ��������
	RenderFullHour();

	//--------------------------------------

	//��ħ �׸���
	HPEN penHour = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
	HGDIOBJ oldPen = SelectObject(hdc, penHour);

	//��ǥ ������ ��ǥ ���� (�⺻ ���) : ��ħ�� 1�ð��� 30���� �����Դϴ�. (360 / 12)
	angle = GetClockAngle(GetRadian(systemTime.wHour) * 30.0f);
	// angle = (GetRadian(systemTime.wHour) * 30.0f - PHI / 2; // ������ ǥ��
	x = origin.x + (-cos(angle) * lengthHour);
	y = origin.y + (-sin(angle) * lengthHour);
	// ���� x = cos(x) * -1�� ���� ����
	// x ���� -cos�� : �ð�ٴ� ȸ�� ���ذ� ������ �Ϲ� �۵�(�ݽð����)�� �ݴ��Դϴ�.
	//				  �׷��Ƿ� x�� ������ ������ �ٲ��ָ� "�ð����"�� ������ �� �־��.

	//�ٸ��� ��ǥ��(������) ���� ���
	//GetAngleForHour();
	GetAngleForHourSmooth();

	//��ǥ�� �׸���
	MoveToEx(hdc, origin.x, origin.y, NULL);
	LineTo(hdc, x, y);

	//�� �׸��� ��� ���� �� �� �����
	SelectObject(hdc, oldPen);
	DeleteObject(penHour);

	//--------------------------------------

	//��ħ �׸���
	HPEN penMinute = CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
	oldPen = SelectObject(hdc, penMinute);
	//oldPen ��� ��� (������ ������ε�)

	//��ǥ ������ ��ǥ ���� (�⺻ ���) : ��ħ�� 1�п� 6���� �����Դϴ� (360 / 60)
	angle = GetClockAngle(GetRadian(systemTime.wMinute) * 6.0f);
	x = origin.x + (-cos(angle) * lengthMinute);
	y = origin.y + (-sin(angle) * lengthMinute);

	//�ٸ��� ��ǥ��(������) ���� ���
	//GetAngleForMintue();
	GetAngleForMinuteSmooth();

	//��ǥ�� �׸���
	MoveToEx(hdc, origin.x, origin.y, NULL);
	LineTo(hdc, x, y);

	//�� �׸��� ��� ���� �� �� �����
	SelectObject(hdc, oldPen);
	DeleteObject(penMinute);

	//--------------------------------------

	//��ħ �׸���
	HPEN penSecond = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	oldPen = SelectObject(hdc, penSecond);

	//��ǥ ������ ��ǥ ���� (�⺻ ���) : ��ħ�� 1�ʿ� 6���� �����Դϴ� (360 / 6)
	angle = GetClockAngle(GetRadian(systemTime.wSecond) * 6.0f);
	x = origin.x + (-cos(angle) * lengthSecond);
	y = origin.y + (-sin(angle) * lengthSecond);

	//�ٸ��� ��ǥ��(������) ���� ���
	GetAngleForSecondSmooth();

	//��ǥ�� �׸���
	MoveToEx(hdc, origin.x, origin.y, NULL);
	LineTo(hdc, x, y);

	//�� �׸��� ��� ���� �� �� �����
	SelectObject(hdc, oldPen);
	DeleteObject(penSecond);
}

void ClockScene::Update()
{

	// �ð� ������Ʈ
	//------------------------------------------

	// (���� 1) �ð� �����͸� �ޱ�
	GetLocalTime(&systemTime);

	// (���� 2) �޾Ƴ� �ð� �����Ϳ��� �ؽ�Ʈ �����ϱ�
	//          Ȯ�ο� �� ������ ��¿�

	timeText = Get12HourText(systemTime.wHour) + L"�� "
		+ std::to_wstring(systemTime.wMinute) + L"�� "
		+ std::to_wstring(systemTime.wSecond) + L"�� ";
		//+ std::to_wstring(systemTime.wMilliseconds) + L"�и���";

	dateText = std::to_wstring(systemTime.wYear) + L"�� "
		+ std::to_wstring(systemTime.wMonth) + L"�� "
		+ std::to_wstring(systemTime.wDay) + L"�� "
		+ DayofWeek(systemTime.wDayOfWeek); //����

	// (���� 3) �޾Ƴ� �����͸� Render()���� �����մϴ�.

	InvalidateRect(hWnd, NULL, true); //ȭ�� ��ȿȭ�� �ϰ��.
}

//-----------------------------------------------------------------













// ���ǿ��� ���� °��°�� �Ƴ��α� �ð� ������ ����

// ������ �ð�� ��ħ�� �����̴� ���� ��ħ��,
// ��ħ�� �����̴� ���� ��ħ�� �����Դϴ�.
// ��, ��, ��ħ�� �� ������ �Ƴ��α� �ð谡 ������ Ư������ (��ΰ�...)

// ���� ���� �ð� �������� �����Ϸ���?
// ��ħ�� �����ӿ� ��, ��ħ�� �����ӿ� �ʸ� ���� ����ϸ� �˴ϴ�.

// �Ƴ��α׿����� ������ ��ϸ� �� �����ϸ� �ذ�� ���� (���� ���� ����������)
// �����п��� ��꿡 ����� ���ؾ� �Ѵٴ� ��... ������ ���̷����մϴ�.

void ClockScene::GetAngleForHour()
{
	//�ô� 60�и��� 30���� �����Դϴ�.
	//�׷��Ƿ� 1�и��� (30�� / 60��)�� �����̰���.
	//�׸��� 1�ʸ��� /60�ʸ�ŭ �� ������ �̴ϴ�.

	float tmpAngle = GetClockAngle(GetRadian((float)systemTime.wHour) * 30.0f
		+ GetRadian((float)systemTime.wMinute) * (30.0f / 60.0f)
		+ GetRadian((float)systemTime.wSecond) * (30.0f / 60.0f / 60.0f));
	//������ ���ڸ� float���� Ȯ���� ǥ���ؼ� �Ҽ������� ����� ��������!

	x = origin.x + (-cos(tmpAngle) * lengthHour);
	y = origin.y + (-sin(tmpAngle) * lengthHour);

	TextOut(hdc, 0, 100, std::to_wstring(tmpAngle).c_str(), 8);
}

void ClockScene::GetAngleForMintue()
{
	//��ħ�� 60�ʸ��� 360���� �����Դϴ�. 1�ʿ��� 6�� ������ �̴ϴ�.
	//�׷��� 1�ʸ��� ���������� (360�� / 60�� / 60��)��ŭ ������ �̴ϴ�.
	float tmpAngle = GetClockAngle(GetRadian((float)systemTime.wMinute) * 6.0f
		+ GetRadian((float)systemTime.wSecond) * (6.0f / 60.0f));

	x = origin.x + (-cos(tmpAngle) * lengthMinute);
	y = origin.y + (-sin(tmpAngle) * lengthMinute);

	TextOut(hdc, 0, 150, std::to_wstring(tmpAngle).c_str(), 8);
}

// ���� ���̴� �ε巯�� �ð� ������ ����

// ����������, ��ħ�� °��°�� �������� �ʰ� ������ �����̴� �ð赵 ����.
// �̷� �ð踦 �����Ϸ���, �� ����� ���ʷ� �ؼ� �ű⿡ �и��ʱ��� �� �� ����� �ϸ� �ǰ���.
	 
void ClockScene::GetAngleForHourSmooth()
{
	//�и��ʸ� ����غ���...
	//�Ƹ� ��ħ�� 1�ʿ� 30��/60��/60��/1000�и��ʸ�ŭ ����...��?
	float tmpAngle = GetClockAngle(GetRadian((float)systemTime.wHour) * 30.0f
		+ GetRadian((float)systemTime.wMinute) * (30.0f / 60.0f)
		+ GetRadian((float)systemTime.wSecond) * (30.0f / 60.0f / 60.0f)
		+ GetRadian((float)systemTime.wMilliseconds) * (30.0f / 60.0f / 60.0f / 1000.0f));

	x = origin.x + (-cos(tmpAngle) * lengthHour);
	y = origin.y + (-sin(tmpAngle) * lengthHour);

	TextOut(hdc, 0, 100, std::to_wstring(tmpAngle).c_str(), 8);
}

void ClockScene::GetAngleForMinuteSmooth()
{
	float tmpAngle = GetClockAngle(GetRadian((float)systemTime.wMinute) * 6.0f
		+ GetRadian((float)systemTime.wSecond) * (6.0f / 60.0f)
		+ GetRadian((float)systemTime.wMilliseconds) * (6.0f / 60.0f / 1000.0f));

	x = origin.x + (-cos(tmpAngle) * lengthMinute);
	y = origin.y + (-sin(tmpAngle) * lengthMinute);

	TextOut(hdc, 0, 150, std::to_wstring(tmpAngle).c_str(), 8);
}

void ClockScene::GetAngleForSecondSmooth()
{
	float tmpAngle = GetClockAngle(GetRadian((float)systemTime.wSecond) * 6.0f
		+ GetRadian((float)systemTime.wMilliseconds) * (6.0f / 1000.0f));

	x = origin.x + (-cos(tmpAngle) * lengthSecond);
	y = origin.y + (-sin(tmpAngle) * lengthSecond);

	TextOut(hdc, 0, 200, std::to_wstring(tmpAngle).c_str(), 8);
}
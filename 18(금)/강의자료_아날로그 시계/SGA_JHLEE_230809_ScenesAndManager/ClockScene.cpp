#include "ClockScene.h"

ClockScene::ClockScene(HWND _hWnd)
{
	hWnd = _hWnd;
	hdc = GetDC(_hWnd);

	// 원점 (시계 위치)를 조정
	origin.x = 300;
	origin.y = 300;

	//12 위치 (y축으로 -거리)
	rect12 = { origin.x - 10 , origin.y - 10 - charDistance, origin.x + 10 , origin.y + 10 - charDistance};
	//3 위치 (x축으로 +거리)
	rect3 = { origin.x - 10 + charDistance , origin.y - 10, origin.x + 10 + charDistance , origin.y + 10 };
	//6 위치 (y축으로 +거리)
	rect6 = { origin.x - 10 , origin.y - 10 + charDistance, origin.x + 10 , origin.y + 10 + charDistance };
	//9 위치 (y축으로 -거리)
	rect9 = { origin.x - 10 - charDistance , origin.y - 10, origin.x + 10 - charDistance , origin.y + 10 };

	dateRect = { 0, 0, 50, 20 };
	timeRect = { 0, 20, 50, 40 };

	//----------------------------------------------

	//생성자에 업데이트 내용 (최초 1회) 실행

	// (순서 1) 시간 데이터를 받기
	GetLocalTime(&systemTime);

	// (순서 2) 받아낸 시간 데이터에서 텍스트 추출하기
	//          확인용 겸 디지털 출력용

	timeText = std::to_wstring(systemTime.wHour) + L"시 "
		+ std::to_wstring(systemTime.wMinute) + L"분 "
		+ std::to_wstring(systemTime.wSecond) + L"초 ";
		// + std::to_wstring(systemTime.wMilliseconds) + L"밀리초";

	dateText = std::to_wstring(systemTime.wYear) + L"년 "
		+ std::to_wstring(systemTime.wMonth) + L"월 "
		+ std::to_wstring(systemTime.wDay) + L"일 "
		+ DayofWeek(systemTime.wDayOfWeek); //요일



	// 옵션 : 12시까지 다 나오려면
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
	// (순서 4) 렌더


	// 바탕에 원 하나 그리기

	Ellipse(hdc, origin.x - 220, origin.y - 220, origin.x + 220, origin.y + 220);

	//--------------------------------------


	//텍스트 (시간정보 및 12, 3, 6, 9 계기판)

	DrawText(hdc, dateText.c_str(), -1, &dateRect, DT_NOCLIP);
	DrawText(hdc, timeText.c_str(), -1, &timeRect, DT_NOCLIP);

	DrawText(hdc, cha12.c_str(), -1, &rect12, DT_NOCLIP);
	DrawText(hdc, cha3.c_str(), -1, &rect3, DT_NOCLIP);
	DrawText(hdc, cha6.c_str(), -1, &rect6, DT_NOCLIP);
	DrawText(hdc, cha9.c_str(), -1, &rect9, DT_NOCLIP);

	// 옵션 : 12시까지 다 나오려면
	RenderFullHour();

	//--------------------------------------

	//시침 그리기
	HPEN penHour = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
	HGDIOBJ oldPen = SelectObject(hdc, penHour);

	//목표 각도와 좌표 내기 (기본 방식) : 시침은 1시간에 30도씩 움직입니다. (360 / 12)
	angle = GetClockAngle(GetRadian(systemTime.wHour) * 30.0f);
	// angle = (GetRadian(systemTime.wHour) * 30.0f - PHI / 2; // 수학적 표현
	x = origin.x + (-cos(angle) * lengthHour);
	y = origin.y + (-sin(angle) * lengthHour);
	// 현재 x = cos(x) * -1과 같은 상태
	// x 값을 -cos로 : 시계바늘 회전 기준과 방향은 일반 작도(반시계방향)과 반대입니다.
	//				  그러므로 x값 변경의 방향을 바꿔주면 "시계방향"을 구현할 수 있어요.

	//다르게 좌표를(각도를) 내는 방법
	//GetAngleForHour();
	GetAngleForHourSmooth();

	//좌표로 그리기
	MoveToEx(hdc, origin.x, origin.y, NULL);
	LineTo(hdc, x, y);

	//다 그리면 백업 복구 후 펜 지우기
	SelectObject(hdc, oldPen);
	DeleteObject(penHour);

	//--------------------------------------

	//분침 그리기
	HPEN penMinute = CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
	oldPen = SelectObject(hdc, penMinute);
	//oldPen 계속 사용 (어차피 백업용인데)

	//목표 각도와 좌표 내기 (기본 방식) : 분침은 1분에 6도씩 움직입니다 (360 / 60)
	angle = GetClockAngle(GetRadian(systemTime.wMinute) * 6.0f);
	x = origin.x + (-cos(angle) * lengthMinute);
	y = origin.y + (-sin(angle) * lengthMinute);

	//다르게 좌표를(각도를) 내는 방법
	//GetAngleForMintue();
	GetAngleForMinuteSmooth();

	//좌표로 그리기
	MoveToEx(hdc, origin.x, origin.y, NULL);
	LineTo(hdc, x, y);

	//다 그리면 백업 복구 후 펜 지우기
	SelectObject(hdc, oldPen);
	DeleteObject(penMinute);

	//--------------------------------------

	//초침 그리기
	HPEN penSecond = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	oldPen = SelectObject(hdc, penSecond);

	//목표 각도와 좌표 내기 (기본 방식) : 초침도 1초에 6도씩 움직입니다 (360 / 6)
	angle = GetClockAngle(GetRadian(systemTime.wSecond) * 6.0f);
	x = origin.x + (-cos(angle) * lengthSecond);
	y = origin.y + (-sin(angle) * lengthSecond);

	//다르게 좌표를(각도를) 내는 방법
	GetAngleForSecondSmooth();

	//좌표로 그리기
	MoveToEx(hdc, origin.x, origin.y, NULL);
	LineTo(hdc, x, y);

	//다 그리면 백업 복구 후 펜 지우기
	SelectObject(hdc, oldPen);
	DeleteObject(penSecond);
}

void ClockScene::Update()
{

	// 시계 업데이트
	//------------------------------------------

	// (순서 1) 시간 데이터를 받기
	GetLocalTime(&systemTime);

	// (순서 2) 받아낸 시간 데이터에서 텍스트 추출하기
	//          확인용 겸 디지털 출력용

	timeText = Get12HourText(systemTime.wHour) + L"시 "
		+ std::to_wstring(systemTime.wMinute) + L"분 "
		+ std::to_wstring(systemTime.wSecond) + L"초 ";
		//+ std::to_wstring(systemTime.wMilliseconds) + L"밀리초";

	dateText = std::to_wstring(systemTime.wYear) + L"년 "
		+ std::to_wstring(systemTime.wMonth) + L"월 "
		+ std::to_wstring(systemTime.wDay) + L"일 "
		+ DayofWeek(systemTime.wDayOfWeek); //요일

	// (순서 3) 받아낸 데이터를 Render()에서 렌더합니다.

	InvalidateRect(hWnd, NULL, true); //화면 무효화는 하고요.
}

//-----------------------------------------------------------------













// 현실에서 보는 째깍째깍 아날로그 시계 분위기 내기

// 현실의 시계는 초침이 움직이는 동안 분침이,
// 분침이 움직이는 동안 시침도 움직입니다.
// 시, 분, 초침이 딱 고정된 아날로그 시계가 오히려 특이하죠 (비싸고...)

// 현실 흔한 시계 움직임을 구현하려면?
// 시침의 움직임에 분, 분침의 움직임에 초를 같이 계산하면 됩니다.

// 아날로그였으면 오히려 톱니만 잘 조립하면 해결될 일이 (설계 말고 조립이지만)
// 디지털에선 계산에 계산을 더해야 한다는 게... 조금은 아이러니합니다.

void ClockScene::GetAngleForHour()
{
	//시는 60분마다 30도씩 움직입니다.
	//그러므로 1분마다 (30도 / 60분)씩 움직이겠죠.
	//그리고 1초마다 /60초만큼 더 움직일 겁니다.

	float tmpAngle = GetClockAngle(GetRadian((float)systemTime.wHour) * 30.0f
		+ GetRadian((float)systemTime.wMinute) * (30.0f / 60.0f)
		+ GetRadian((float)systemTime.wSecond) * (30.0f / 60.0f / 60.0f));
	//나누는 숫자를 float으로 확실히 표기해서 소수점까지 결과가 나오도록!

	x = origin.x + (-cos(tmpAngle) * lengthHour);
	y = origin.y + (-sin(tmpAngle) * lengthHour);

	TextOut(hdc, 0, 100, std::to_wstring(tmpAngle).c_str(), 8);
}

void ClockScene::GetAngleForMintue()
{
	//분침은 60초마다 360도씩 움직입니다. 1초에는 6도 움직일 겁니다.
	//그러면 1초마다 마찬가지로 (360도 / 60분 / 60초)만큼 움직일 겁니다.
	float tmpAngle = GetClockAngle(GetRadian((float)systemTime.wMinute) * 6.0f
		+ GetRadian((float)systemTime.wSecond) * (6.0f / 60.0f));

	x = origin.x + (-cos(tmpAngle) * lengthMinute);
	y = origin.y + (-sin(tmpAngle) * lengthMinute);

	TextOut(hdc, 0, 150, std::to_wstring(tmpAngle).c_str(), 8);
}

// 가끔 보이는 부드러운 시계 분위기 내기

// 가끔이지만, 초침이 째깍째깍 움직이지 않고 스르륵 움직이는 시계도 있죠.
// 이런 시계를 구현하려면, 위 계산을 기초로 해서 거기에 밀리초까지 싹 다 계산을 하면 되겠죠.
	 
void ClockScene::GetAngleForHourSmooth()
{
	//밀리초를 계산해보면...
	//아마 시침은 1초에 30도/60분/60초/1000밀리초만큼 가겠...죠?
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
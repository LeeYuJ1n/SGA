#pragma once
#include <Windows.h>
#include <math.h>
#include <string>

using namespace std;

class TimeAndCoord
{
public:
	TimeAndCoord(HWND _hWnd);
	void GetInput(WPARAM _wParam); // 입력 받기
	void GetPoint(LPARAM _lParam); // "포인트" 받기
	void Render();
	void Update();

private:
	// 이 씬은 무슨 씬이냐?
	// → 하나는 만든 윈도우 내에서 좌표를 확인하기 위한 씬
	// → 두번째는 여기서 시간을 받아서 출력을 해보자

	// → 첫 번째, 좌표를 어떻게 확인할 것인가?
	//   1. 코드에서 찍고, 실행해서 화면으로 확인해보면 된다
	//   2. 윈도우를 마우스로 찍어봐서 어딘지 출력시켜보면 된다
	//   → 마우스 입력도 받아봅시다

	// 마우스 좌표를 받으려면 어디까지 가야 되는가? → 윈도우 프로시저까지 돌아가야 한다
	// 거기서 마우스 입력을 받고 여기까지 전달을 해줘야 한다

	// 게임매니저에도 새로운 함수가 필요하겠다

	WPARAM wParam;

	// 초기화를 할 때...화면을 어떻게 지정하지? 윈도우는 어디고?
	HWND hWnd; // 어떤 윈도우에 출력할까? (운영체제 내의 영역)
	HDC hdc;    // 어떤 화면(하드웨어)으로 출력할까? (물리적 출력 수단)

	// 추가 변수
	float pointX;
	float pointY;

	// 문자열
	WCHAR lstr[101];

	RECT rect = {0, 0, 300, 300};
	RECT rect2 = {0, 0, 0, 0};

	// 업데이트 확인용 변ㅅ와 문자열
	int number;
	RECT rect3 = {300, 300, 600, 600}; // 대충 우하단, 4사분면 위치쯤

	// 이 씬을 위한 시간 변수
	SYSTEMTIME st;

	float x2;
	float y2; // x, y 좌표 (두번째)
	float x0;
	float y0;// x, y 좌표 (원점)

	// 각도에서 호도를 뽑아 적용하는 함수
	float GetRadian(float degree) { return (degree / 180) * 3.141592f; }

	// 스트링 자료형을 사용한 문자열 #include <string> 필요
	std::wstring logCoord;
	std::wstring logTime;

	// ------------------------------------------

	// 2023년 8월 14일 과제 : 아날로그 시계 그리기

	float hourDegree;
	float minutesDegree;
	float secondDegree;

	RECT rectEx0814 = { 200, 200, 400, 400 };

	// ------------------------------------------
};


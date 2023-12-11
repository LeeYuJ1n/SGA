#pragma once
#include <Windows.h>

#define PHI 3.141592 // 원주율 미리 매크로로 정의
                     // * 경우에 따라서 이 글자를 PI로 표기하기도...

class AngleScene
{
public:
	AngleScene(HWND _hWnd); // 초기화는 생성자로

	// "게임"에 추가로 필요한 것 (프로그램의 입장에서 3가지)
	// 입력, 출력, 갱신
	void GetInput(WPARAM _wParam);
	void Render();
	void Update();

private:
	WPARAM wParam;

	// 초기화를 할 때...화면을 어떻게 지정하지? 윈도우는 어디고?
	HWND hWnd; // 어떤 윈도우에 출력할까? (운영체제 내의 영역)
	HDC hdc;    // 어떤 화면(하드웨어)으로 출력할까? (물리적 출력 수단)

	// 변수 작성
	float x;
	float y;
	// x, y 좌표를 쓰려는데 float인 이유 : 앞으로 소수 계산 등이 들어갈 때 오차를 줄이기 위해서

	// 아래 두 변수는 둘 다 각도를 뜻하는 단어
	float degree = 1 / 3.11592;    // ← 각도
	float radian = 1;              // ← 호도

	float angle = radian;

	float GetDegree(float _rawDegree);
	// 매개변수로 우리가 생각하는 각도값을 넣어주면 컴퓨터에게 똑같은 각도 단위의 값을 전달
	// * 컴퓨터가 호도로 각도를 계산하므로, 각도를 "호도"로 컴퓨터에게 바꾸어서 인식시킴
	// "60도"를 입력했을 때, 호도가 아닌 각도로 (약) 60도를 컴퓨터에게 전하는 역할
};


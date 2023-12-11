#pragma once
#include <Windows.h>

class TestScene
{
	// 테스트 씬 (장면)
	// 사람 눈에 보이는 실제 "장면"

public:
	TestScene(HWND _hWnd); // 초기화는 생성자로

	// "게임"에 추가로 필요한 것 (프로그램의 입장에서 3가지)
	// 입력, 출력, 갱신
	void GetInput(WPARAM _wParam);
	void Render();
	void Update();

private:
	// 게임매니저의 변수들

	// 입력을 어떻게 받지?
	WPARAM wParam;

	// 초기화를 할 때...화면을 어떻게 지정하지? 윈도우는 어디고?
	HWND hWnd; // 어떤 윈도우에 출력할까? (운영체제 내의 영역)
	HDC hdc;    // 어떤 화면(하드웨어)으로 출력할까? (물리적 출력 수단)

	// 여기서 입력과 출력들을 해봅시다

	// 텍스트 출력 위치
	int text_x;
	int text_y;

	// 오늘부터는 도형을 만들어봅시다
	// 그 중에서도 windows 환경에서 제일 만만하게 도전할 수 있는 도형

	// 1. 직사각형 (rectangle, 렉탱글)
	// 2. 타원(ellipse, 일립스)

	// → 도형의 원래 기본은 정사각형과 원이어야 하지 않나?
	//   그렇게 볼 수도 있지만, 직사각형과 타원은... 가로 세로 길이에 제약이 없어서
	//   변수로 제작하기 편하다 (어차피 가로세로 길이가 같아지면 그게 정사각형이고 원인데)

	// 그 직사각형과 타원을 만들기 위한 자료 구조체
	// "RECT"

	RECT rect1 = {0, 0, 100, 100};
	RECT rect2 = {100, 100, 300, 300};
	RECT rect3 = { 300, 300, 400, 400 };

	// RECT는 숫자 네 개로 이루어진 구조체
	// 여기서 각 숫자는 순서대로 다음 뜻을 가진다
	// 왼쪽, 위, 오른쪽, 아래

	// 각각 4방향의 최대 크기 한계를 나타내는데, 직사각형을 그리는 경우라면 아래처럼 이해해도 된다
	// "왼쪽 위 꼭지점의 x-y와, 오른쪽 아래 꼭지점의 x-y좌표"

	// 이 구조체를 어떻게 쓸지 (그림을 어떻게 그릴지) → cpp에서

	// --------------------------------------

	// 과제 복습을 위한 새로운 사각형 영역
	RECT textArea = {0, 0, 250, 50};

	// --------------------------------------

};


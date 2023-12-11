#pragma once
#include <Windows.h>

// 헤더
#include "TestScene.h" // 테스트 씬을 불러와서 사용 (나중에는 코드 위치가 달라질 수 있음)
#include "AngleScene.h"
#include "TimeAndCoord.h"

class GameManager
{
	// 게임 매니저 : 게임에 사용하기 위한 각 기능 중에서
	//              (싱글턴 이용이나 독립 배치가 불가능하고) 큰 틀에서 (전역변수, main등) 배치해야 할
	//              그런 중요 기능들을 묶어서 한 번에 관리하기 위한 클래스
	//              (게임의 시작과 끝, "장면", 전개, 캐릭터 관리 등등)

	// = main을 대신하는 사실상의 게임 그 자체라고 생각해도 좋습니다

	// 그래서 싱글턴으로 만들 겁니다

private:
	GameManager() {} // 생성자 (정의까지)
	~GameManager() {} // 소멸자

	static GameManager* instance;

public:
	static GameManager* Get()
	{
		if (instance == nullptr)
		{
			instance = new GameManager();
			return instance;
		}
		return instance;
	}

	void Delete()
	{
		delete instance; // 인스턴스 삭제
	}

	// 게임매니저의 역할 : 장면 연출이 아니라, 장면의 관리를 할 것
	// 그러므로 여기서 함수는 실제 연산이 아니라
	// 등록된 장면에 함수를 전달해서 간접 실행하는 역할

	void Init(HWND _hWnd); // 초기화
	
	// "게임"에 추가로 필요한 것 (프로그램의 입장에서 3가지)
	// 입력, 출력, 갱신
	void GetInput(WPARAM _wParam);
	void Render();
	void Update();

	// 새로운 함수 : "포인트" 받기
	void GetPoint(LPARAM _lParam);

private:
	// 게임매니저의 변수들

	// 어떤 장면이 들어가지?
	TestScene* tsc;
	AngleScene* asc;
	TimeAndCoord* tac;
	
	// 입력을 어떻게 받지?
	WPARAM wParam;

	// 초기화를 할 때...화면을 어떻게 지정하지? 윈도우는 어디고?
	HWND hWnd; // 어떤 윈도우에 출력할까? (운영체제 내의 영역)
	HDC hdc;    // 어떤 화면(하드웨어)으로 출력할까? (물리적 출력 수단)
};


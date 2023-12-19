#pragma once
#include "Construction.h"                // 전체적인 맵
#include "Construction_Building.h"       // 건물 배치
#include "EventMap_1.h"                  // 건물 내부 1

class Task_230828 : public Scene
{
public:
	Task_230828();     // 생성자
	~Task_230828();    // 소멸자

	Construction* CTR;          // 전체적인 맵
	Construction_Building* CTB; // 건물
	EventMap_1* EMap1;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// HBITMAP → 플레이어 캐릭터
	HBITMAP character1;       // 플레이어 스탠딩 모션
	HBITMAP character1WALK;   // 플레이어 걷기 모션
	HBITMAP character1ATK;    // 플레이어 공격 모션
	HBITMAP character1DEAD;   // 플레이어 죽는 모션

	// HBITMAP → 구조물
	HBITMAP background;      // 게임 배경
	HBITMAP Building1;       // 건물1
	HBITMAP BuildingTile;    // 건물 바닥
	HBITMAP BuildingWall;    // 건물 벽
	HBITMAP Road;            // 길
	HBITMAP Long_Road;       // 가로로 긴 길

	HDC memDC;
	HDC stretchDC;

	POINT characterPosition;
	Rect* characterArea;

	int actCode; // 0 : 서 있기, 1 : 걷기
	int actIndex1;
	int actIndex1Walk;
	int actIndex1Run;
	int actIndex1Atk;

	bool isReversIndex1;
	bool isReversIndex1Walk;
	bool isReversIndex1Run;

	bool isLeft = false; // 왼쪽을 보고 있는가? (true : 왼쪽을 보는 중 / false : 오른쪽을 보는 중) 
	bool isAtk = false;  // 공격 중인가? (true : 공격 중 / false : 공격은 안 하는 중)

	int lastIndex1 = 4;
	int lastIndex1Walk = 5;
	int lastIndex1Run = 5;
	int lastIndex1Atk1 = 4;

	float animationSpeed;
	float walkSpeed = 10.0f;

	float currentTimeElapsed; // 현재 경과 시간
	float interval;           // 시간 간격

	float moveSpeed = 10.0f;

	// ********************************************************************

	// 상호작용을 위한 사각형
	Rect* platform[6];
	bool Collision = false;

	// 충돌의 방향을 알기 위한 변수와 함수
	int directionForm_Code; // ← 각 충돌 방향을 코드화해서 빠르게, 정확하게 구분 가능

	enum COL_DIRECTION // ← 위와 같은 의미를 열거형을 써서 나중에 알아보기 쉽게 만든 것
	{
		NONE,
		LEFT,
		RIGHT,
		ABOVE,
		BENEATH
	};

	// 위에 있는 열거형을 써서 충돌 방향을 알 수 있는 연산을 만들자
	// 이들의 충돌 형태가 수직에 가까운가, 수평에 가까운가를 보고자 한다
	COL_DIRECTION GetCollisionDirection(Rect* rect_one, Rect* rect_two)
	{
		float _left = rect_one->Left() > rect_two->Left() ? rect_one->Left() : rect_two->Left();
		float _right = rect_one->Right() < rect_two->Right() ? rect_one->Right() : rect_two->Right();
		float _top = rect_one->Top() > rect_two->Top() ? rect_one->Top() : rect_two->Top();
		float _bottom = rect_one->Bottom() < rect_two->Bottom() ? rect_one->Bottom() : rect_two->Bottom();

		// 위 연산을 통해, 두 사각형의 겹치는 영역 중 최대한 작은 영역 = 교집합을 구할 수 있다

		// 그리고 교집합의 모양을 판별해서

		bool collideHorizontal;

		if (_right - _left > _bottom - _top) // 잡은 (가상) 사각형의 가로가 세로보다 크면
		{
			collideHorizontal = false; // 수직으로 충돌했다 (위 아래 위치 = 그래서 교집합이 납작하다)
		}
		else collideHorizontal = true; // 수평 충돌 (왼쪽 오른쪽 위치)

		if (collideHorizontal) // 수평 충돌이다
		{
			// 서로 왼쪽 선분끼리 비교해서 더 왼쪽에 있는 쪽이 왼쪽
			if (rect_one->Left() < rect_two->Left())
			{
				return LEFT; // rect_one은 rect_two의 왼쪽이다
			}
			else
			{
				return RIGHT;
			}
		}
		else
		{
			if (rect_one->Bottom() < rect_two->Bottom())
			{
				if (_bottom - _top > 90) return NONE; // 충돌 영역 크기가 커도 나무 크다

				return ABOVE; // 위
			}
			else
			{
				return BENEATH; // 아래
			}
		}
	}

	// 위 결과를 받기 위한 변수 추가 (옵션)
	COL_DIRECTION singleDir; // 한 명의 캐릭터가, 하나의 물건에 대해 가지는 방향값
	BLENDFUNCTION blend;     // 알파 블렌드 데이터
	// BLENDFUNCTION : 그림 조합(특히 투명도 등)에 사용된 데이터 구조체

	// ********************************************************************
};


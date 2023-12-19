#pragma once

class BitmapScene : public Scene
{
public:
	BitmapScene();
	~BitmapScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	// 비트맵 씬
	// 비트맵 : 화면에서 각 픽셀이 어떤 색을 가지고 있는지를 구성한 자료의 집합(위치와 색 정보로 이루어진 map)
	//          → 컴퓨터에서 그림을 나타내는 가장 단순하고 정확한 방식

	// 비트맵이 출력되려면? 그림 데이터가 필요하다

	// 앱에서 말하는 그림 데이터는 크게 두 가지를 뜻한다

	// 1. 그림 그 자체 (로raw 데이터라고도 하고, 자원resource(리소스) 데이터라고도 한다)
	// 2. 그 실제 그림을 앱에서 코드의 형태로 등록한 것 (등록된 변수)
	
	// 위의 1과 2까지 모두 합쳐서 그림 데이터라고 한다

	// 그림은 탐색기로 폴더에 넣었으니, 등록할 변수를 코드에서 만들자

	HBITMAP artist; // 도화가 그림
	HBITMAP human;  // 사람 그림
	// HBITMAP : 그림 파일을 앱에서 쓰기 위해 등록하는 자료형

	HBITMAP humanRun; // 달리는 사람 그림
	HBITMAP humanATK; // 내려치는 사람 그림

	// 동작들을 구분하기 위해 만든 동작의 번호
	int actCode; // 0 : 서 있음, 1 : 달리기, 2 : 내쳐리기

	HBITMAP human2;

	// 그리고 한 가지가 더 필요하다
	
	// 지금 우리가 윈도우에서 화면을 2개로 나누어서 번갈아 출력 중(실제 + 가상)
	// → 깜빡임, 실시간 처리에 의한 시간 비효율 등을 줄이기 위해서

	// → 똑같은 이유로, 그림을 처리해줄 가상의 출력 장소가 또 하나 더 필요하다

	HDC memDC;     // 그림을 처음 그려준 (눈에 안 보이는) 출력 장소
	HDC stretchDC; // 그림을 중간에 (스트레치 블릿으로) 작업할 출력 장소
	HDC alphaDC;   // 그림의 투명도를 작업하기 위한 가장 1단계의 (혹은 안 쓰이는) 출력장소

	// ---------------------------------------------

	// 씬 내에서 바로 캐리터 움직여보기 (22일 과제)

	// 캐릭터를 표현한다는 것 : 비트맵에서 기준점을 시작으로 캐릭터의 "표현하고 싶은 크기만큼 보여주기"
	// 그 크기가 일정할 경우, 순번에 따라 캐릭터의 동작에 동등한 순번을 매겨줄 수 있다
	// → 법칙성 있는 공식에 따라, 캐릭터의 순번에 따른 동작을 출력할 수 있다
	
	// 캐릭터의 동작 순번

	int actIndex1;  // 1번 캐릭터의 동작 번호
	int actIndex1Run;
	int actIndex1ATK;
	int actIndex2;  // 2번 캐릭터의 동작 번호

	// 애니메이션이 루프인가, 왕복인가
	// 왕복인 경우 "역행" 변수가 추가로 또 필요할 수 있다

	// 역행인가?
	bool isReverseIndex1;
	bool isReverseIndex1Run;
	// 공격은 역핼을 안 만들 것

	bool isReverseIndex2;

	int lastIndex1 = 5; // 1번 캐릭터의 마지막 동작의 순번
	int lastIndex1Run = 7;
	int lastIndex1ATK = 3;
	int lastIndex2 = 2; // 2번 캐릭터의 마지막 동작의 순번
	// (혹은 위 값을 정할 때 곧바로 그림의 개수를 적어도 괜찮습니다)

	// ---------------------------------------------

	// 위 동작 순번을 이용해서 
	// 캐릭터의 움직임이 자동으로 이루어지도록 하는 것도 가능할까? → 가능!

	// 시간 관리자 클래스를 사용해서 시간의 경과를 찾으려고 하는데
	// (시간에 대한 윈도우 기능을 미리 정리한 사전 클래스)

	// 원리 : 일정 시간이 지날 때마다 기록된 시간의 차이를 시간관리자로부터 받아와서
	// 이곳 클래스의 지정한 변수에 계속해서 누적시킨다

	// → 결과적으로 "시간이 지난 정도"라는 숫자가 클래스에 기록된다
	// → 그리고 이 "경과된 시간"이 일정 기준을 넘을 때마다,
	//   캐릭터의 순번을 +1 올린다

	// 그래서 필요한 변수는 두 개
	float currentTimeElapsed; // 현재 경과된 시간
	float interval;           // (시간의) 간격. 이 간격을 경과 시간이 넘으면 캐릭터 순번이 돈다
	
	// 캐릭터가 너무 빠르면 간격을 늘리거나... 경과 시간을 수집할 때 추가로 보정을 가할 수 있다
	float animateSpeed;       // 재생 속도

	// 캐릭터 중 하나를 움직여보겠습니다
	float moveSpeed = 10.0f;
	float jumpPower = 5.0f;
	float jumpSpeed = 10.0f; // 점프 속도 (임시로 만들기만 함)
	int jumpCount = 0;       // 점프 횟수 (현재 0)
	
	// 점프에 횟수가 있다면? → 그 횟수를 살린 게임의 몇 가지 추가 동작을 구현 가능
	//                       공중 점프, "해당 스테이지에서 가능한 총 점프 횟수"

	bool isLeft = true; // 이 캐릭터는 왼쪽을 보고 있습니까? (초기 값 : 거짓)

	// 캐릭터가 왼쪽을 보고 있는지 아닌지는 게임마다 설정할 필요성이 다릅니다
	// 스프트라이트 시트(그림)의 경우에도, 게임에 따라 왼쪽을 그리는 게임이 있는가 하면
	// 그리지 않는 게임도 있습니다. 왼쪽 그림이 있는 게임은 굳이 이런 변수가 필요없을 수도 있죠
	// 캐릭터에게 방향이 굳이 필요 없는 경우에도요

	// * 다만 여기선 게임 안에서도 방햐잉 필요하고, 그림에는 왼쪽을 보는 그림이 없는 상황을 가정합니다

	POINT characterPosition; // 캐릭터의 위치
	Rect* characterArea;     // 캐릭터가 현재 차지한 영역 (포인터 인스턴스)
	Rect* characterHit;      // 캐릭터의 그림이 실제로 차지하는 영역 (캐릭터가 정말로 닿는 곳)

	bool isJumping = false; // 지금 캐릭터가 점프 중인가?
	bool isATKing = false;  // 지금 캐릭터가 공격 중인가?

	// 캐릭터를 움직일 때 영향을 끼칠 환경 변수 임의로 설정하겠습니다
	float gravity = 5.0f;

	// 아래 변수는 캐릭터의 움직임이 환경의 영향을 받아 만든 최종 결과입니다
	float downForce; // 밑으로 잡아끄는 힘

	HitFX* fx; // 타격 효과를 가상 구현하는 사각형

	// human2가 맞았다
	bool human2isHit = false;
	bool isFading = false;     // "희미해지는 중"
	float currentAlpha = 255;  // 현재의 투명도

	// 아래 변수의 값 1은 "히트 FX"의 주기값(1)을 따온 것입니다
	float span = 1;
	float hitTime = 0;

	// --------------------------------------

	// 발판 변수
	Rect* platform;

	void UpdateHitToAreaPos() // "히트"라는 영역을 다른 영역 위치로
	{
		characterHit->Pos() = Vector2(characterArea->Pos().x,
			characterArea->Bottom() - characterHit->GetSize().y / 2);
	}

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
				if (_bottom - _top > 10) return NONE; // 충돌 영역 크기가 커도 나무 크다

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
};


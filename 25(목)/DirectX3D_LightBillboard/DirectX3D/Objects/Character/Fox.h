#pragma once

class Fox : public ModelAnimator
{
private:
	// 주요 멤버 데이터
	enum State
	{
		IDLE, RUN
	};

	// * 이 처럼 캐릭터에게 상태부터 부여한 다음, 상태를 바꿈에 따라 동작(그래픽), 함수 등을
	//   뒤따라 실행시키는 방법이 있는가 하면, 각 행동을 기준으로 제시해서 행동을 수행할 때마다
	//   반대로 상태를 바꾸거나, 후속 함수를 호출하는 방법도 있다

	// 캐릭터가 달리기를 한다면
	// -> A : 달리기라는 상태가 먼저 오고, 달리기를 위한 애니메이션을 재생할 것인가?
	// -> B : 달리기라는 함수를 먼저 실행하고, 그 안에서 애니메이션을 재생할 것인가?

	// A와 B 사이에 정확한 우열은 없다
	// -> A 방법의 경우 : 캐릭터가 가질 수 있는 현상의 범위를 정해놓고 통제할 수 있다
	//                   그리고 상태를 바꿔주는 절차를 통일시켜서 이 후 유지보수를 쉽게 해줄 수 있다
	// -> B 방법의 경우 : 캐릭터가 가져야 할 고유의 행동들의 대한 세부적인 후속 조치를 구체화할 수 있다
	//                   그리고 하나의 행동에 따른 시작과 끝에 대한 개발과 관리를 한 눈에 볼 수 있다

	// 그래서 보통 프로그래밍을 하면 설계단계에서 캐릭터가 A 스타일로 개발될지 B 스타일로 개발될지
	// 어느정도 일관성을 갖추고 개발을 시작하면 좋다
	// -> B 스타일은 의식하지 않아도 보통 잘 만들어주기 때문에
	//    강의 중에서는 A 스타일을 조금 더 자주 보여주는 경향은 있다

	// 더불어서 (B 스타일은 없지만) A 스타일 개발은 특별히 지칭하는 이름이 있다

	// "유한 상태 기계" 혹은 "유한 상태 절차" (Finite State Machine)
	// -> 대상이 가지는 행동 혹은 현상을 절차(혹은 기계, a machine)로 지칭하고
	//    해당 절차나 현상을 나열한 다음 상태라고 지칭하면,
	//    조건에 따른 상태 이전의 과정으로서 대상의 전체 행동을 설명하는 개발 방법

	// 지금 만든 이 여우 클래스(여우 캐릭터)를 보면
	// 1. 달리기와 가만히 있기라는 두 가지 절차와 상태가 있고
	// 2. 여우는 조건에 따라 이 두 상태 중 하나로만 존재하며
	// 3. 역시 조건에 따라 이 두 상태 중 하나에서 다른 하나로 상태를 이전할 수있다
	// -> 이런 식으로 여우를 설명하는 것이 바로 FSM, 유한 상태 기계

public:
	// 호출용 함수

	Fox();
	~Fox();

	void Update();
	void Render();

	// 캐릭터와 배경, 길찾기 클래스를 상호 연결하는 함수
	void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
	void SetAStar(AStar* aStar) { this->aStar = aStar; }

private:
	// 멤버 함수
	
	void Control();
	void Move();
	void Rotate();

	void SetState(State State); // 상태 설정 함수 : FSM식 개발의 핵심
	void SetPath();

private:
	// 멤버 변수

	State curState = IDLE; // 현재 상태 + 기본값

	float moveSpeed = 100.0f;
	float rotSpeed  = 10.0f;

	Vector3 velocity;

	// 길 찾기용 데이터
	Vector3 destPos;      // 목적지
	vector<Vector3> path; // 경로

	Terrain* terrain; // 지형(배경)
	AStar* aStar;     // 길 찾는 알고리즘
};


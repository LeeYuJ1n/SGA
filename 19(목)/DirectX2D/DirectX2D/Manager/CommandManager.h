#pragma once

class CommandManager : public Singleton<CommandManager>
{
private:
	friend class Singleton;

	CommandManager();
	~CommandManager();

public:
	void Update();
	// void Render(); // <- 커맨드 매니저는 자기가 뭘 출력할 거리가 없어서 안 쓴다

	// 퍼블릭이면 외부 호출 가능 대상, 프라이빗이면 Update로 자기가 입력을 따로 받아야 한다
	// 커맨드 쌓기 함수
	void StackCommand(int key); // 매개변수를 통해 커맨드를 입력받는 기능
	// 함수 명칭은 Stack 혹은 Push가 흔히 쓰이는데, 전자는 기획 중심, 후자는 자료구조 중심 명명

	// 커맨드 등록 함수
	void RegisterCommand(void* source = nullptr);
	// 매개변수는 자료형을 어떻게 받을 지 몰라서 포인터 지정만 해두기
	// * 기본형은 그냥 이 함수 자체에 직접 커맨드를 작성해서 넣으면 된다 (매개변수는 지금은 있지만 하고 안 쓴다)

private:
	void CheckCommand(); // 만들어진 커맨드가 실행될 것인지 체크

	// 변수들

	// 당장 입력받은 커맨드
	queue<int> commandQueue; // 커맨드 큐

	// 벡터가 아니고 큐인 이유 : 나중에 이 커맨드 체크 후나 도중에 삭제할 때 앞에서 삭제할 경우도 염두에 두고 싶어서
	// 큐의 데이터(커맨드 받는 자료형)가 int인 이유 : 꼭 정수일 필요는 없었지만 키 입력은 보통 하거나, 표현할 때 숫자가 들어오거나 언습되는 경우가 많아서

	// 입력받은 커맨드가 어떤 의미인지 판별하기 위한 사전 정의 목록
	
	unordered_map<string, int> commandTable; // 자동 정렬 없는 맵으로 커맨드 테이블 만들기

	// (옵션) 커맨드가 입력 상한이 필요할 경우 그 범위를 지정하기 위한 변수

	UINT maxCommandLength = 0;
};


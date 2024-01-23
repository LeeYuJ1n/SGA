#include "Framework.h"

CommandManager::CommandManager()
{
	// 우선 커맨드 등록을 진행
	RegisterCommand();
	// 만약 다른 그닝이 추가된다면 여기서 작성
}

CommandManager::~CommandManager() {}


void CommandManager::Update()
{
	// 테스트용 입력 (나중에 외부에서도 호출은 가능)
	if (KEY_DOWN(VK_LEFT))
	{
		// StackCommand('0' + 4); // 기존 숫자가 아닌 "끝 자리"에 숫자 더하기

		// 만약 (if) 닌자가 왼쪽을 보고 있으면, 왼쪽 화살표가 "앞" (6)이 된다
		// 아니면? 왼쪽 = 4

		// 닌자의 방향을 사용하려는 이상, 커맨드 매니저에서 바로 입력을 하기는 힘들다
		// 이제 좌우 입력은 닌자로 넘기도록 하겠다 (복잡하지만 알아보기 위한 것이 목적이므로)
	}

	if (KEY_DOWN(VK_RIGHT))
	{
		// StackCommand('0' + 6);

		// 닌자가 왼쪽이면 이 키가 4, 오른쪽을 보면 이 키가 6
	}

	if (KEY_DOWN(VK_UP))
	{
		StackCommand('0' + 8);
	}

	if (KEY_DOWN(VK_DOWN))
	{
		StackCommand('0' + 2);
	}

	if (KEY_DOWN('X'))
	{
		StackCommand('0' + 1);
		CheckCommand();
	}
}

void CommandManager::RegisterCommand(void* source)
{
	// 매개변수가 있는 경우와 없는 경우를 나누기
	if (source != nullptr)
	{
		// TODO : 외부 등록 커맨드가 있을 경우 자료형을 맞추어서 큐에 등록한다
		// (*TODO : things to do의 마지막 네 글자 = "앞으로 이렇게 할 것" = "지금은 더 뭘 하지 않겠다")
	}
	else
	{
		// 여기로 왔다면 매개변수를 거치지 않고 수동으로 커맨드 테이블을 등록하겠다는 뜻
		
		// 테스트용 커맨드 등록
		// 아래 + 앞(오른쪽) + 공격 = 장풍
		commandTable["261"] = 12;
		commandTable["661"] = 10; // 앞 + 앞 + 공격

		// "261" : 방향키와 버튼 입력이 있을 경우, 해당 방향과 기타 버튼을 나타내는 표기법의 한 가지
		//         이 경우 2, 4, 6, 8을 각각 키패드의 아래, 왼쪽, 오른쪽, 위에 대응하고, 1과 0응 버튼으로 표현한다는 뜻

		// 다른 표기로는 키패드의 1 ~ 9까지를 모두 방향으로 나타내고, 0와 .를 각각 버튼에 대응하는 표기도 있다 (8방향이 지원되는 복잡한 게임에서 쓰기 좋다)
		// 혹은 시계방향으로 1 ~ C까지의 방향을 (혹은 0 ~ B까지) 지정하고, P와 K를 지정하기도 한다 (12방향. P, K는 각각 펀치와 킥에 대응)
		// ...혹은 8방향에 P, K 등의 표기를 쓰는 등, 널리 퍼진 방향 표기법조차 한 둘이 아니다
		//    (이후 이런 커맨드 표기법 등을 공유할 때는 방향 표기 원칙 같은 것들도 공유하거나 지침을 따라주면 좋다는 이야기)
		// * 여기서 246810방향 표기법을 쓰는 이유 : 이 방법은 int만으로도 표현이 충분이 가능하기 때문에
		//   + 더불어 이 표기법에는 안 쓰는 숫자가 더 있어서 (3, 6도 있고...) 안 쓰는 키를 추가 키에 대응할 수도 있다

		// 여기서 테이블의 값은 Ninja.h의 액션 타임 enum 값	
	}

	// 여기까지 오면 커맨드 등록이 끝난 것

	// 입력 상한을 커맨드 테이블에 맞춰서 지정하기
		// (그래서 정해진 것보다 입력이 과도하게 많아지면 앞부분부터 무시할 수 있도록)
	for (pair<string, int> command : commandTable)
	{
		if (command.first.size() > maxCommandLength) // 커맨드 길이가 최대 허용보다 길다면
		{
			// 길이 범위 갱신
			maxCommandLength = command.first.size();
		}
	}
}

void CommandManager::StackCommand(int key)
{
	// 커맨드 입력 받기
	// -> 큐에 값을 하나 푸시하는 것으로 충분

	commandQueue.push(key);

	// 입력이 허용 범위를 넘어갔다면 (너무 길다면) 들어온 순서대로(오래된 키부터) 날려버리기
	if (commandQueue.size() > maxCommandLength) commandQueue.pop();
}

void CommandManager::CheckCommand()
{
	// 입력받은 커맨드가 테이블과 (전체 혹은 일부가) 일치하는지 확인 후
	// 조건에 일치하면 정해진 역할 수행

	// 커맨드 큐를 map의 스트링에 대응시키기 위한 임시 변수
	string curCommand; // 현재 입력이 저장될 데이터

	while (commandQueue.size() > 0) // 커맨드 큐를 검사하면서 하나씩 스트링에 넣기
	{
		curCommand += commandQueue.front(); // 스트링을 쓰면 더하기 가능, 제한적으로 타 자료형 가능
		commandQueue.pop(); // 입력해서 보낸 커맨드는 큐에서 지우기
	}

	// 여기까지 왔을 때 curCommand가 정리가 완료

	while (curCommand.size() > 0)
	{
		// 테이블을 검사해서 (현재 : 전부가) 일치하는 내용이 있다면
		if (commandTable.count(curCommand) > 0)
		{
			// 지정된 역할 수행
			// if문이나 별도 함수를 통해서 직접 수행을 할 수도 있고 / 함수 포인터를 쓸 수도..

			// 함수 포인터를 쓸 경우, 현재 프레임워크의 OBserver 클래스에도 비슷한 인터페이스가 있다

			Observer::Get()->ExcuteIntParamEvent("Skill", commandTable[curCommand]);

			return;
		}

		// 커맨드 내용 정리 (하니씩 커맨드를 빼가면서 새로 비교 해야 하니까)
		curCommand.erase(curCommand.begin()); // 시작부분의 문자 지우기
	}

	// 여기까지 왔다면 일치하는 커맨드가 없었던 것
	// -> 그러므로 여기서 그냥 끝
}
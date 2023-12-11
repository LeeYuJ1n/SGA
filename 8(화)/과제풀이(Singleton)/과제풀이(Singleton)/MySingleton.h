#pragma once
#include "Calculator.h"

class MySingleton
{
private:
// 어차피 안에 내용 안 들어갈 건데 그냥정의까지
	MySingleton();
	~MySingleton();

	static MySingleton* instance;

public:
	static MySingleton* Instance()
	{
		if (Instance == nullptr)
		{
			instance = new MySingleton();
			return instance; // 인스턴스가 없으면 만들어서 반환
		}

		return instance; // 있으면 있는 걸 반환
	}

	// * 추가 코드 팁 : 클래스에서 접근권 지정은 여러 번 나누어서 쓸 수 있습니다
	// private 밑에 public, 다시 그 밑에 private을 지정할 수 있습니다
	// 같은 private인데 의미가 약간 다르거나, 우선 순위에 차이가 있다고 생각되면
	// 다른 곳에 적어도 괜찮습니다

	// 이렇게 여러 번 중복된 접근권 지정이 있을 경우,
	// 각 코드의 실제 접근권은 위쪽으로 제일 가까운 지정을 따릅니다

private:
	// 이 밑으로 작성되는 코드는 다시 private이 됩니다
	// 다시 이 밑에 public이 선언되면, 그 밑에 작성된 코드는 다시 public이 됩니다

	// 계산기 (private)
	Calculator* calc;

public:
	void Init();          // 초기화
	void RunCalculator(); // 계산기 실제 실행
};


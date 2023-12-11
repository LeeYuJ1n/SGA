#include "MySingleton.h"


MySingleton* MySingleton::instance = nullptr;

MySingleton::MySingleton() {}
MySingleton::~MySingleton() {}

void MySingleton::Init() // 싱글턴의 초기화
{
	calc = new Calculator(); // 계산기의 초기화이면서, 계산기의 첫 입력을 받는 것

	// 계산기 초기화도 했겠다 안내도 해봅시다 (입출력은 계산기에서 포함돼있음)
	cout << "**계산기가 초기화되고 값이 저장되었습니다**" << endl;
}

void MySingleton::RunCalculator() // 사용자는 이 함수를 실행하는 거고
{
	calc->Run(); // 컴퓨터는 명령을 받아서 계산기를 간접 실행해주는 것
}
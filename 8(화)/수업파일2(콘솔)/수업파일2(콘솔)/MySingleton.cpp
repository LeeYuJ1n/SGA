#include "MySingleton.h"

using namespace std;

// instance를 맨 처음에 nullptr로 초기화
MySingleton* MySingleton::instance = nullptr;

MySingleton::MySingleton() {}

MySingleton::~MySingleton()
{
	// 소멸자가 호출된다 = 클래스 instance가 지워진다는 뜻
	// 이 때 클래스 안에서 instance를 제외하고 추가로 동적 할당한 멤버 변수 등이 있으면
	// 이 소멸자 안에서 delete 시켜주면 됩니다 (아래 Delete 함수처럼)
}

// 다 쓴 싱글턴의 instance 삭제
void MySingleton::Delete()
{
	delete instance; // instance 데이터의 메모리 점거 해제
	                 // 쓴다고 바로 데이터가 사라지진 않는다
					 // 다만 컴퓨터가 나중에 이 메모리를 덮어씌울 수 있을 뿐

	// WinAPI 등에서 추가된 삭제 기능이 있을 경우 해당 코드로 대신하는 것도 가능
}

void MySingleton::Init(int _x, int _y)
{
	x = _x;
	y = _y;
}

void MySingleton::Add(int _x, int _y)
{
	x = _x;
	y = _y;

	result = x + y;
}

void MySingleton::Sub(int _x, int _y)
{
	x = _x;
	y = _y;

	result = x - y;
}

void MySingleton::Mult(int _x, int _y)
{
	x = _x;
	y = _y;

	result = x * y;
}

void MySingleton::Div(int _x, int _y)
{
	x = _x;
	y = _y;

	result = x / y;
}
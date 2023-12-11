#include "MyClass.h"

// 여기서 헤더에서 작성된 클래스의 함수를 정의 가능

// 정의하는 방법

// 클래스명::함수명

int MyClass::Add(int x, int y)
{
	return x + y;
}

int MyClass::Mult(int x, int y)
{
	return x * y;
}

// std::cout...도 std라는 클래스(혹은 비슷한 집합)에 속했던 다른 함수(정확히는 클래스지만)

void MyClass::Init(int _a, float _f, int _id, int _xx)
{
	// 여기서 변수를 다 넣도록 한다

	a = _a;
	f = _f;
	id = _id;
	xx = _xx;

	// 나중에도 변수가 늘면 그 늘어난 변수만큼 여기서 초기화를 한다
	// 역서 말하는 초기화는 변수 자체의 초기화를 뜻하기도 하지만 
	// 클래스 사용을 위해 "초기 상태"를 수동 설정한다는 뜻도 된다
}
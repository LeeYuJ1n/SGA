#pragma once
#include "Data.h"

class Calculator : public Data // 데이터의 자식 클래스
{
protected:
	// 아까 본 대로면 이제 이 클래스에서도 부모 클래스와 같지만 다른 코드를 작성할 수 있는데
	// "클래스에서 부모와 별개의 코드를 작성합니다" ← 어떤 코드를 이렇게 만들 수 있을까?

	// int number1; ← 원본에서 똑같이 받는 건데 굳이 변수를?
	
public:
	Calculator()
	{
		Data();
	}
	
	// 자식 클래스에서 흔히 사용되는 "같은 코드 작성"의 대상은
	// 바로 "함수"이다

	// Data의 함수를 가져오되, 내용을 바꾸자
	// 함수의 용도를 출력하는 대신 직접 연산 후 값을 반환하도록
	int Add(int x, int y)
	{
		return x + y;
	}

	int Sub(int x, int y)
	{
		// 시간 관계상 매개변수만 써서 연산 후 반환
		return x - y;
	}

	int Mult(int x, int y)
	{
		return x * y;
	}

	int Div(int x, int y)
	{
		if (y != 0)
		{
			return x / y;
		}
		else
		{
			return 0;
		}
		
	}

	int Nam(int x, int y)
	{
		if (y != 0)
		{
			return x % y;
		}
		else
		{
			return 0;
		}
	}
};


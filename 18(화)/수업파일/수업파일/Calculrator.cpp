#include "Calculrator.h"

int Calculrator::Add(int x, int y)
{
	// 번거롭지만, 데이터를 변수에 넣은 후 계산

	integer1 = x;
	integer2 = y;

	return integer1 + integer2;
}

int Calculrator::Sub(int x, int y)
{
	integer1 = x;
	integer2 = y;

	return integer1 - integer2;
}

int Calculrator::Mult(int x, int y)
{
	integer1 = x;
	integer2 = y;

	return integer1 * integer2;
}

int Calculrator::Div(int x, int y)
{
	integer1 = x;
	integer2 = y;

	if (integer2 != 0)
	{
		return integer1 / integer2;
	}

	else return 0;
}

int Calculrator::Nam(int x, int y)
{
	integer1 = x;
	integer2 = y;

	if (integer2 != 0)
	{
		return integer1 % integer2;
	}

	else return 0;
}

float Calculrator::Add(float x, float y)
{
	singleNumber1 = x;
	singleNumber2 = y;

	return singleNumber1 + singleNumber2;
}

float Calculrator::Sub(float x, float y)
{
	singleNumber1 = x;
	singleNumber2 = y;

	return singleNumber1 - singleNumber2;
}

float Calculrator::Mult(float x, float y)
{
	singleNumber1 = x;
	singleNumber2 = y;

	return singleNumber1 * singleNumber2;
}

float Calculrator::Div(float x, float y)
{
	singleNumber1 = x;
	singleNumber2 = y;

	if (singleNumber2 != 0)
	{
		return singleNumber1 / singleNumber2;
	}

	else return 0;
}

int Calculrator::Add(int add)
{
	// 매개변수 한 개짜리로 더하기를 한다는 건 어떤 의미인가?
	// → 이미 다른 숫자 두 개로 더하기를 한 게 있겠지
	// 그러니 그 결과에 추가로 뭔가를 더하고자 하겠지

	if (sum == 0)
	{
		int first = Add(integer1, integer2); // 데이터에 저장된 기존 숫자를 써서 더하기를 1차 도출

		// (옵션)
		sum = first + add;
	}
	else sum += add; // sum에 값이 있으면 sum에 곧바로 add 더하기

	return sum; // 저장된 합계를 반환하기
}

int Calculrator::Add(int x, int y, int z)
{
	// 테스트용이라 데이터를 쓰지 않고 곧바로 코딩
	return x + y + z;
}

int Calculrator::Add(float x, float y, float z)
{
	// int 함수에 매개변수 float 여러 개를 쓰기
	return (int)(x + y + z); // x + y + z를 먼저 계산한 후 (int)를 적용
}

int Calculrator::Sub(int _sub)
{
	if (sub == 0)
	{
		int first = Sub(integer1, integer2);

		sub = first - _sub;
	}
	else sub -= _sub;

	return sub;
}
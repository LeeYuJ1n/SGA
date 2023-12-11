#pragma once
#include <iostream>

class Data
{
protected:

	// 데이터용 데이터
	int number1;
	int number2;
	int number3;

	float float1;
	float float2;
	float float3;

public:
	Data()
	{
		number1 = 0;
		number2 = 0;
		number3 = 0;
		float float1 = 0;
		float float2 = 0;
		float float3 = 0;
	}

	// 데이터에 미리 "이 데이터로 할 수 있는 함수"의 기본 안내를 작성
	int Add(int x, int y)
	{
		std::cout << "이 함수는 더하기를 위해 만들었습니다." << std::endl;
		return 0;
	}

	int Sub(int x, int y)
	{
		std::cout << "이 함수는 빼기를 위해 만들었습니다." << std::endl;
		return 0;
	}

	int Mult(int x, int y)
	{
		std::cout << "이 함수는 곱하기를 위해 만들었습니다." << std::endl;
		return 0;
	}

	int Div(int x, int y)
	{
		std::cout << "이 함수는 나누기를 위해 만들었습니다." << std::endl;
		return 0;
	}

	int Nam(int x, int y)
	{
		std::cout << "이 함수는 나머지 도출을 위해 만들었습니다." << std::endl;
		return 0;
	}
};


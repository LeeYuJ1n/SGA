#pragma once
#include <iostream>

class Arithmetic_Class
{
public:
	// public에 생성자와 소멸자 생성
	Arithmetic_Class();         // 생성자
	~Arithmetic_Class();        // 소멸자

	// 실체 전달용 instance
	static Arithmetic_Class* instance;

	static Arithmetic_Class* Get()
	{
		// 현재 instance가 지정된 것이 없다면
		if (instance == nullptr)
		{
			// 자기 자신의 instance를 생성
			instance = new Arithmetic_Class();
		}

		// instance 반환
		return instance;
	}

	// 사칙연산 함수
	void Add(int _x, int _y);              // 더하기
	void Sub(int _x, int _y);              // 빼기
	void Mult(int _x, int _y);             // 곱하기
	void Div(int _x, int _y);              // 나누기
	void Remainder(int _x, int _y);        // 나머지

	// 연산에 필요한 변수
	int x = 0, y = 0;

	// 다 쓴 instance를 지울 때 사용
	void Delete();
};


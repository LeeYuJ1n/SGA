#pragma once
#include <iostream>

using namespace std;

class Calculator
{
private:
	int record;    // 저장된 숫자
	int input;     // 입력으로 넣은 숫자
	char opCode;   // 입력으로 넣은 연산자

	// 계산 함수
	void Add(int value); // (미리 정해진 어떤 변수에) 추가로 뭔가를 더하기
	void Sub(int value);       // 빼기
	void Mult(int value);      // 곱하기
	void Div(int value);       // 나누기
	void Remain(int value);    // 나머지

public:
	Calculator();

	void Run(); // 실행이라는 함수 하나만 밖으로 공개
};


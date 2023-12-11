#pragma once
#include <iostream>
#include <list>

using namespace std;

class ListClass
{
public:
	ListClass() {}

	// 호출
	void Call(int _number1, list<int> lc);

	// 출력
	void Print(list<int> lc);

	// 삽입
	void Insert(int _number1, list<int>& lc, int _input);

	// 삭제
	void Erase(int _number1, list<int>& lc);

	// 추가 
	void Emplace(int _number1, list<int>& lc, int _input);
};


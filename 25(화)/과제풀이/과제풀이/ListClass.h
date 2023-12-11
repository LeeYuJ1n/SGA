#pragma once
#include <iostream>
#include <list>

using namespace std;

class ListClass
{
private:
	// 시험용 리스트
	list<int> test;

	// 리스트를 순번으로 쓸 수 있도록 하기 위한 함수들

	// 값 호출하기
	int GetElement(list<int> source, int idx);
	// source : 어느 배열에서 가져올 거냐
	// idx : 순번(index)의 약자

	// 값 추가하기
	void insertBtIndex(list<int>* target, int idx, int value);
	// target : 어느 배열에 추가할 거냐 (직접 추가해야 되니까 포인터로)
	// idx : 순번
	// value : 추가할 값

	// 값 삭제하기
	void EraseByIndex(list<int>* target, int idx);

public:
	ListClass() {}

	void Start();
};


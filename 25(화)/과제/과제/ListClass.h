#pragma once
#include <iostream>
#include <list>

using namespace std;

class ListClass
{
public:
	ListClass() {}

	// ȣ��
	void Call(int _number1, list<int> lc);

	// ���
	void Print(list<int> lc);

	// ����
	void Insert(int _number1, list<int>& lc, int _input);

	// ����
	void Erase(int _number1, list<int>& lc);

	// �߰� 
	void Emplace(int _number1, list<int>& lc, int _input);
};


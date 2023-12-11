#include "ListClass.h"

using namespace std;

// < 출력 >
void ListClass::Call(int _number1, list<int> lc)
{
	cout << "input number : " << _number1 << endl;

	list<int>::iterator iter = lc.begin();

	for (int i = 0; i < _number1; ++i)
	{
		iter++;
	}
	cout << "output list number : " << * iter << endl;
}

// 출력
void ListClass::Print(list<int> lc)
{
	list<int> ::iterator iter = lc.begin();

	for (iter; iter != lc.end(); ++iter)
	{
		cout << *iter << "\t";
	}
	cout << endl;
}

// 삽입
void ListClass::Insert(int _number1, list<int>& lc, int _input)
{
	list<int>::iterator iter = lc.begin();

	for (int i = 0; i < _number1; ++i)
	{
		iter++;
	}
	lc.insert(iter, _input);
}

// 삭제
void ListClass::Erase(int _number1, list<int>& lc)
{
	list<int>::iterator iter = lc.begin();

	for (int i = 0; i < _number1; ++i)
	{
		iter++;
	}
	lc.erase(iter);
}

// 추가
void ListClass::Emplace(int _number1, list<int>& lc, int _input)
{
	list<int>::iterator iter = lc.begin();

	for (int i = 0; i < _number1; ++i)
	{
		iter++;
	}
	lc.emplace(iter, _input);
}
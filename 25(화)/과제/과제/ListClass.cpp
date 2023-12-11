#include "ListClass.h"

using namespace std;

// < ��� >
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

// ���
void ListClass::Print(list<int> lc)
{
	list<int> ::iterator iter = lc.begin();

	for (iter; iter != lc.end(); ++iter)
	{
		cout << *iter << "\t";
	}
	cout << endl;
}

// ����
void ListClass::Insert(int _number1, list<int>& lc, int _input)
{
	list<int>::iterator iter = lc.begin();

	for (int i = 0; i < _number1; ++i)
	{
		iter++;
	}
	lc.insert(iter, _input);
}

// ����
void ListClass::Erase(int _number1, list<int>& lc)
{
	list<int>::iterator iter = lc.begin();

	for (int i = 0; i < _number1; ++i)
	{
		iter++;
	}
	lc.erase(iter);
}

// �߰�
void ListClass::Emplace(int _number1, list<int>& lc, int _input)
{
	list<int>::iterator iter = lc.begin();

	for (int i = 0; i < _number1; ++i)
	{
		iter++;
	}
	lc.emplace(iter, _input);
}
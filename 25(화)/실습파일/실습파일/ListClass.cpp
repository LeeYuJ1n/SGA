#include "ListClass.h"
#include <iostream>
#include <list>
#include <Windows.h>

using namespace std;

void ListClass::Start(int _first)
{
	// < switch문 제어 >
	int input = 0;

	// < 리스트 선언 >
	list<int> intList(_first);

	cout << "iter(리스트) 순번 출력" << endl;
	cout << endl;

	// < 값을 채우기 >
	for (int i = 0; i < 10; ++i)
	{
		intList.push_back(i + 1); // 1부터 10까지
	}

	// < 리스트를 초기화 >
	list<int>::iterator iter = intList.begin();

	for (int i = 0; i < 10; ++i)
	{
		// < iter 초기화 >
		iter = intList.begin();

		// < iter(리스트) 순번 출력 >
		for (int j = 0; j < i; ++j)
		{
			iter++;
		}
		cout << *iter << endl;
	}

	// < iter(리스트) 초기화 >
	iter = intList.begin();

	while (true)
	{
		cout << "메뉴 선택" << endl;
		cout << "1. 현재 iter(리스트) 값 출력" << endl;
		cout << "2. 현재 iter(리스트) 값 호출" << endl;
		cout << "3. 현재 iter(리스트) 값 삽입" << endl;
		cout << "4. 현재 iter(리스트) 값 삭제" << endl;
		cout << "입력 : ";
		cin >> input;

		switch (input)
		{
		case 0:
			system("cls");

			cout << "현재 iter(리스트) 값을 출력합니다" << endl;

			for (int i = 0; i < 10; ++i)
			{
				// < iter 초기화 >
				iter = intList.begin();

				// < iter(리스트) 순번 출력 >
				for (int j = 0; j < i; ++j)
				{
					iter++;
				}
				cout << *iter << endl;
			}
			break;
		}
		continue;
	}
}
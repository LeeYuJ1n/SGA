#include "ListClass.h"
#include <iostream>
#include <list>
#include <Windows.h>

using namespace std;

void ListClass::Start(int _first)
{
	// < switch�� ���� >
	int input = 0;

	// < ����Ʈ ���� >
	list<int> intList(_first);

	cout << "iter(����Ʈ) ���� ���" << endl;
	cout << endl;

	// < ���� ä��� >
	for (int i = 0; i < 10; ++i)
	{
		intList.push_back(i + 1); // 1���� 10����
	}

	// < ����Ʈ�� �ʱ�ȭ >
	list<int>::iterator iter = intList.begin();

	for (int i = 0; i < 10; ++i)
	{
		// < iter �ʱ�ȭ >
		iter = intList.begin();

		// < iter(����Ʈ) ���� ��� >
		for (int j = 0; j < i; ++j)
		{
			iter++;
		}
		cout << *iter << endl;
	}

	// < iter(����Ʈ) �ʱ�ȭ >
	iter = intList.begin();

	while (true)
	{
		cout << "�޴� ����" << endl;
		cout << "1. ���� iter(����Ʈ) �� ���" << endl;
		cout << "2. ���� iter(����Ʈ) �� ȣ��" << endl;
		cout << "3. ���� iter(����Ʈ) �� ����" << endl;
		cout << "4. ���� iter(����Ʈ) �� ����" << endl;
		cout << "�Է� : ";
		cin >> input;

		switch (input)
		{
		case 0:
			system("cls");

			cout << "���� iter(����Ʈ) ���� ����մϴ�" << endl;

			for (int i = 0; i < 10; ++i)
			{
				// < iter �ʱ�ȭ >
				iter = intList.begin();

				// < iter(����Ʈ) ���� ��� >
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
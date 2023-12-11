#include <iostream>
#include <vector>
#include <string.h>
#include "UserCert.h"

using namespace std;

void UserCert::Start()
{
	// ù ��° �ι� ���
	vector<string> firstList = 
	{
		"�ֺ���",
		"�̽±�",
		"�ɻ���",
		"������",
		"������",
		"��ȣĥ",
	};

	// �� ��° ���
	vector<string> secondList = 
	{
		"������",
		"���׿�",
		"�̽±�",
		"����",
		"���켮",
		"������",
	};

	// ��ġ�ϴ� ���
	vector<string> matchedList;

	// ��ġ�� ��� ��
	int matched = 0; // 0���� ����

	// �� �迭�� ���� �ݺ��� ������
	for (int i = 0; i < firstList.size(); ++i)
	{
		// �� ���� �ٸ� �� �迭�� �� ������ ������ ���� �ݺ���
		for (int j = 0; j < secondList.size(); ++j)
		{
			// ù ����� i��°�� �� ��° ����� j��°�� ��
			// *���߹迭�� �ƴ϶� �� �迭�� �̷� ������ �� ����

			int match = firstList[i].compare(secondList[j]);

			if (match == 0) // �� compare�� "��ġ"���� ������ 0�� �ȴٴ� ���� ����
			{
				matched++; // ��ġ �ο� �� +1
				matchedList.push_back(secondList[j]); // ��ܿ� �̸� �߰�
			}
		}
	}

	// ������� ���� ��ġ�ϴ� ����� ��ܰ� �ο� ���� ���� ��

	// ���
	cout << "��ġ�ϴ� �ο� �� : " << matched << endl;
	cout << "��� : ";

	for (int i = 0; i < matchedList.size(); ++i)
	{
		cout << matchedList[i] << ", ";
	}
}
#include <iostream>
#include "Josephus.h"
#include "UserCert.h"

using namespace std;

// ����Ǯ�� + ���

// ����Ǯ�̿� �ռ��� �迭 ���
void Josephus::PrintVector(vector<int> data)
{
	// ���� ũ�⿡ ���߾ ���
	for (int i = 0; i < data.size(); ++i)
	{
		cout << data[i] << "\t"; // �� ���� ������ �� ����
	}
	cout << endl; // �� ������ �� �ٲٱ�
}

// ��¥ ���� Ǯ��
void Josephus::Start()
{
	// �Էº��� �ޱ�
	cout << "������ ũ�⸦ �Է����ּ��� : ";
	cin >> sizeOfArray;

	cout << "���� ������ �Է����ּ��� : ";
	cin >> interval;

	// ù ��° ���͸� �����
	for (int i = 0; i < sizeOfArray; ++i)
	{
		firstData.push_back(i + 1); // push_back ���
		// 1���� ������ ũ����� ���ڰ� ���ʷ� �� ��
	}

	// �� ���� �迭 ���
	cout << "���� �迭 : ";
	PrintVector(firstData);

	cout << "�似Ǫ�� ���� : ";
	PrintVector(answer);

	cout << endl;

	// ���ĺ��� ��¥ ��� ����
	// for (int i = 0; i < sizeOfArray; ++i) // ����. �� �� ��꿡  "ù �迭"���� ���� �� ���� �ݵ�� �������ϱ�
	// {
	// 
	// }

	while (firstData.size() > 0) // ���� �迭�� ���ڰ� ���� �� ������ ���� �ݺ���
	{
		// �ȳ� �� ��� ����

		// �� ��° ����ΰ�?
		cout << "<" << count << "��° ��� >"  << endl;
		cout << endl;

		// int next�� �ʿ��ѵ� ������� ����ڽ��ϴ�

		// ���⼭ next : ������ ���� ����
		next = next + interval - 1; // �����̴ϱ� 1�� ���� ��� (0���� �����ϴϱ�)

		// next�� ù ������ ũ�⺸�� Ŀ����, "�� ���� ���Ƽ� ó��"���� ���� �Ѵ�
		// �� ù ������ ũ�⺸�� ū ���� ������ ���� ũ�⸸ŭ �������� �ȴ�
		while (next >= firstData.size())
		{
			// ũ�� ���� ������ ���� = �� ��ü�� ������ ũ�⸦ �Ѿ�ٴ� ��
			next = next - firstData.size();
		}

		// ������ ������ ������ �����͸� ���� �� ���Ϳ� ����
		// answer.push_back(firstData.at(next)); // �� ���� �� �� �Լ��� Ȱ��
		answer.push_back(firstData[next]);

		// �̾ �ش� ��ġ�� ù ���Ϳ��� ����
		firstData.erase(firstData.begin() + next);

		// * ����� �� �� ����� �ƴ϶�, �� ��� �Ŀ� ������ �մϴ�
		// �� �׷��� ���� ����ؾ� �Ǵµ� �����Ͱ� �̹� �������� �����ϴ�

		// �� ������ ���
		cout << "���� �迭 : ";
		PrintVector(firstData);

		cout << "�似Ǫ�� ���� : ";
		PrintVector(answer);

		// Ƚ���� 1 �ø��� �ݺ�
		count++;
	}
}
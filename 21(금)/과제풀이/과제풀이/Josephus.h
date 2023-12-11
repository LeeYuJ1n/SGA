#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Josephus
{
private:
	// �似Ǫ�� ������ �ʿ��� ����

	// 1. �迭(����)
	vector<int> firstData; // ó�� �迭
	vector<int> answer;    // ���� �� �迭

	// 2. �Է��� �޾Ƽ� ���� ����
	int sizeOfArray; // ó�� ������ ũ��
	int interval;    // ����

	// 2-1. ���� ����(�ʿ���)
	int next;

	// 3. �ʿ� ���µ� �׳� �ְ� �; �ִ� ����
	// * �ڵ� �׽�Ʈó�� �ӵ��� �߿��� ���� �̷� �� ������ ���ô�
	// * ��� �������� ������Ʈ��� �̷��� �峭�� �ĺ��� �͵� �����ϴ�
	int count; // ���� ��� �� ��°�ΰ�

	// �迭 �����ֱ�� �Լ��� �̸� ���� ������ ȣ��
	void PrintVector(vector<int> data);

public:
	// �Լ� �θ���
	void Start();

	// ������ (�Է��� ���� ���� �Ŷ� �����ڿ��� �� �� �ʿ䰡 ����
	Josephus()
	{
		count = 1; // ù ��° ����̴ϱ� 1
		next = 0;  // ������ ���� ����

		// 0 �ʱ�ȭ
		sizeOfArray = 0;
		interval = 0;
	}
};


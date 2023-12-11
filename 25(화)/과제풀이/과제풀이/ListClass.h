#pragma once
#include <iostream>
#include <list>

using namespace std;

class ListClass
{
private:
	// ����� ����Ʈ
	list<int> test;

	// ����Ʈ�� �������� �� �� �ֵ��� �ϱ� ���� �Լ���

	// �� ȣ���ϱ�
	int GetElement(list<int> source, int idx);
	// source : ��� �迭���� ������ �ų�
	// idx : ����(index)�� ����

	// �� �߰��ϱ�
	void insertBtIndex(list<int>* target, int idx, int value);
	// target : ��� �迭�� �߰��� �ų� (���� �߰��ؾ� �Ǵϱ� �����ͷ�)
	// idx : ����
	// value : �߰��� ��

	// �� �����ϱ�
	void EraseByIndex(list<int>* target, int idx);

public:
	ListClass() {}

	void Start();
};


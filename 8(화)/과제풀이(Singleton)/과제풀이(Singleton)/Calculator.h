#pragma once
#include <iostream>

using namespace std;

class Calculator
{
private:
	int record;    // ����� ����
	int input;     // �Է����� ���� ����
	char opCode;   // �Է����� ���� ������

	// ��� �Լ�
	void Add(int value); // (�̸� ������ � ������) �߰��� ������ ���ϱ�
	void Sub(int value);       // ����
	void Mult(int value);      // ���ϱ�
	void Div(int value);       // ������
	void Remain(int value);    // ������

public:
	Calculator();

	void Run(); // �����̶�� �Լ� �ϳ��� ������ ����
};


#include "Calculator.h"

// ������ �� ù ��° �������� �� ����� ��
Calculator::Calculator()
{
	// ���� ������ �ȳ�
	cout << "���� ���� ���⸦ �����մϴ�" << endl;
	cout << endl;
	
	cout << "ù ��° ���ڸ� �Է����ּ��� : ";
	cin >> record; // ����� ������ ó������ �Ҵ�ޱ�

	// �� ���� �̸� �ʱ�ȭ (�ʿ�� ���µ� �׳� �� ���Ϸ���)
	input = 0;
	opCode = ' ';
}

// �� ���� �Լ�
void Calculator::Run()
{
	// ���⼭ �������� ���⸦ ���� ����
	while (true)
	{
		cout << endl;

		cout << "��������� ���ڿ� �߰��� ������ ���ڸ� �Է����ּ���" << endl;
		cout << "�Է� : ";
		cin >> input;

		cout << "�����Ϸ��� ����� �����ڷ� �Է����ּ���" << endl;
		cout << "�Է� : ";
		cin >> opCode;

		switch (opCode)
		{
		case '+':
			Add(input); // �Է¹��� ���ڸ� �־ ���ϱ�
			break;

		case '-':
			Sub(input);
			break;

		case '*':
			Mult(input);
			break;

		case '/':
			Div(input);
			break;

		case '%':
			Remain(input);
			break;
		}
	}
}

// ����� (��±���)
void Calculator::Add(int value)
{
	cout << endl;

	cout << record << "��" << value << "�� ���� : " << record + value << "�Դϴ�" << endl;

	// ���� ������ �ݿ�
	record += value;
}

void Calculator::Sub(int value)
{
	cout << endl;

	cout << record << "��" << value << "�� ����� : " << record - value << "�Դϴ�" << endl;

	// ���� ������ �ݿ�
	record -= value;
}

void Calculator::Mult(int value)
{
	cout << endl;

	cout << record << "��" << value << "�� ���ϱ�� : " << record * value << "�Դϴ�" << endl;

	// ���� ������ �ݿ�
	record *= value;
}

void Calculator::Div(int value)
{
	if (value != 0)
	{
		cout << endl;

		cout << record << "��" << value << "�� ������ : " << record / value << "�Դϴ�" << endl;

		// ���� ������ �ݿ�
		record /= value;
	}
	else
	{
		cout << endl;

		cout << "0���δ� ���� �� �����ϴ�" << endl;
	}
}

void Calculator::Remain(int value)
{
	if (value != 0)
	{
		cout << endl;

		cout << record << "��" << value << "�� �������� : " << record % value << "�Դϴ�" << endl;

		// ���� ������ �ݿ�
		record %= value;
	}
	else
	{
		cout << endl;

		cout << "0���δ� ���� �� �����ϴ�" << endl;
	}
}


void Run(); // �����̶�� �Լ� �ϳ��� ������ ����
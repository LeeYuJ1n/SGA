#include "Arithmetic_Class.h"

using namespace std;

// instance�� nullptr�� �ʱ�ȭ
Arithmetic_Class* Arithmetic_Class::instance = nullptr;

// ������
Arithmetic_Class::Arithmetic_Class() {}

// �Ҹ���
Arithmetic_Class::~Arithmetic_Class() {}

// ���ϱ�
void Arithmetic_Class::Add(int _x, int _y)
{
	x = _x;
	y = _y;

	cout << "�Է��� ù ��° ���� : " << x << endl;
	cout << "�Է��� �� ��° ���� : " << y << endl;
	cout << "�� ���� ���ϱ� ��� : " << x + y << endl;
}

// ����
void Arithmetic_Class::Sub(int _x, int _y)
{
	x = _x;
	y = _y;

	cout << "�Է��� ù ��° ���� : " << x << endl;
	cout << "�Է��� �� ��° ���� : " << y << endl;
	cout << "�� ���� ���� ��� : " << x - y << endl;
}

// ���ϱ�
void Arithmetic_Class::Mult(int _x, int _y)
{
	x = _x;
	y = _y;

	cout << "�Է��� ù ��° ���� : " << x << endl;
	cout << "�Է��� �� ��° ���� : " << y << endl;
	cout << "�� ���� ���ϱ� ��� : " << x * y << endl;
}

// ������
void Arithmetic_Class::Div(int _x, int _y)
{
	x = _x;
	y = _y;

	cout << "�Է��� ù ��° ���� : " << x << endl;
	cout << "�Է��� �� ��° ���� : " << y << endl;
	cout << "�� ���� ������ ��� : " << x / y << endl;
}

// ������
void Arithmetic_Class::Remainder(int _x, int _y)
{
	x = _x;
	y = _y;

	if (x == 0 || y == 0)
	{
		cout << "0���δ� ���� �� �����ϴ�. �ٽ� �Է����ּ���." << endl;
	}
	else
	{
		cout << "�Է��� ù ��° ���� : " << x << endl;
		cout << "�Է��� �� ��° ���� : " << y << endl;
		cout << "�� ���� ������ ��� : " << x % y << endl;
	}
}

// �� �� isntance ����
void Arithmetic_Class::Delete()
{
	delete instance;
}
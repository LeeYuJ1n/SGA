#include "Singleton_Class.h"

// instance�� nullptr�� �ʱ�ȭ
Singleton_Class* Singleton_Class::instance = nullptr;

// ������
Singleton_Class::Singleton_Class() {}

// �Ҹ���
Singleton_Class::~Singleton_Class() {}

// ���� ������ Ŭ���� ȣ�� �� ���
void Singleton_Class::ArithmeticZip()
{
	Add(x, y);
	Sub(x, y);
	Mult(x, y);
	Div(x, y);
	Remainder(x, y);

	cout << "��� ������ �������ϴ�" << endl;
}

// ����� ���� Singleton�� instance ����
void Singleton_Class::Delete()
{
	delete instance;
}
#include "MySingleton.h"

using namespace std;

// instance�� �� ó���� nullptr�� �ʱ�ȭ
MySingleton* MySingleton::instance = nullptr;

MySingleton::MySingleton() {}

MySingleton::~MySingleton()
{
	// �Ҹ��ڰ� ȣ��ȴ� = Ŭ���� instance�� �������ٴ� ��
	// �� �� Ŭ���� �ȿ��� instance�� �����ϰ� �߰��� ���� �Ҵ��� ��� ���� ���� ������
	// �� �Ҹ��� �ȿ��� delete �����ָ� �˴ϴ� (�Ʒ� Delete �Լ�ó��)
}

// �� �� �̱����� instance ����
void MySingleton::Delete()
{
	delete instance; // instance �������� �޸� ���� ����
	                 // ���ٰ� �ٷ� �����Ͱ� ������� �ʴ´�
					 // �ٸ� ��ǻ�Ͱ� ���߿� �� �޸𸮸� ����� �� ���� ��

	// WinAPI ��� �߰��� ���� ����� ���� ��� �ش� �ڵ�� ����ϴ� �͵� ����
}

void MySingleton::Init(int _x, int _y)
{
	x = _x;
	y = _y;
}

void MySingleton::Add(int _x, int _y)
{
	x = _x;
	y = _y;

	result = x + y;
}

void MySingleton::Sub(int _x, int _y)
{
	x = _x;
	y = _y;

	result = x - y;
}

void MySingleton::Mult(int _x, int _y)
{
	x = _x;
	y = _y;

	result = x * y;
}

void MySingleton::Div(int _x, int _y)
{
	x = _x;
	y = _y;

	result = x / y;
}
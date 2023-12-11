#include "Calculrator.h"

int Calculrator::Add(int x, int y)
{
	// ���ŷ�����, �����͸� ������ ���� �� ���

	integer1 = x;
	integer2 = y;

	return integer1 + integer2;
}

int Calculrator::Sub(int x, int y)
{
	integer1 = x;
	integer2 = y;

	return integer1 - integer2;
}

int Calculrator::Mult(int x, int y)
{
	integer1 = x;
	integer2 = y;

	return integer1 * integer2;
}

int Calculrator::Div(int x, int y)
{
	integer1 = x;
	integer2 = y;

	if (integer2 != 0)
	{
		return integer1 / integer2;
	}

	else return 0;
}

int Calculrator::Nam(int x, int y)
{
	integer1 = x;
	integer2 = y;

	if (integer2 != 0)
	{
		return integer1 % integer2;
	}

	else return 0;
}

float Calculrator::Add(float x, float y)
{
	singleNumber1 = x;
	singleNumber2 = y;

	return singleNumber1 + singleNumber2;
}

float Calculrator::Sub(float x, float y)
{
	singleNumber1 = x;
	singleNumber2 = y;

	return singleNumber1 - singleNumber2;
}

float Calculrator::Mult(float x, float y)
{
	singleNumber1 = x;
	singleNumber2 = y;

	return singleNumber1 * singleNumber2;
}

float Calculrator::Div(float x, float y)
{
	singleNumber1 = x;
	singleNumber2 = y;

	if (singleNumber2 != 0)
	{
		return singleNumber1 / singleNumber2;
	}

	else return 0;
}

int Calculrator::Add(int add)
{
	// �Ű����� �� ��¥���� ���ϱ⸦ �Ѵٴ� �� � �ǹ��ΰ�?
	// �� �̹� �ٸ� ���� �� ���� ���ϱ⸦ �� �� �ְ���
	// �׷��� �� ����� �߰��� ������ ���ϰ��� �ϰ���

	if (sum == 0)
	{
		int first = Add(integer1, integer2); // �����Ϳ� ����� ���� ���ڸ� �Ἥ ���ϱ⸦ 1�� ����

		// (�ɼ�)
		sum = first + add;
	}
	else sum += add; // sum�� ���� ������ sum�� ��ٷ� add ���ϱ�

	return sum; // ����� �հ踦 ��ȯ�ϱ�
}

int Calculrator::Add(int x, int y, int z)
{
	// �׽�Ʈ���̶� �����͸� ���� �ʰ� ��ٷ� �ڵ�
	return x + y + z;
}

int Calculrator::Add(float x, float y, float z)
{
	// int �Լ��� �Ű����� float ���� ���� ����
	return (int)(x + y + z); // x + y + z�� ���� ����� �� (int)�� ����
}

int Calculrator::Sub(int _sub)
{
	if (sub == 0)
	{
		int first = Sub(integer1, integer2);

		sub = first - _sub;
	}
	else sub -= _sub;

	return sub;
}
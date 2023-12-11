#pragma once
#include "Data.h"

class Calculator : public Data // �������� �ڽ� Ŭ����
{
protected:
	// �Ʊ� �� ��θ� ���� �� Ŭ���������� �θ� Ŭ������ ������ �ٸ� �ڵ带 �ۼ��� �� �ִµ�
	// "Ŭ�������� �θ�� ������ �ڵ带 �ۼ��մϴ�" �� � �ڵ带 �̷��� ���� �� ������?

	// int number1; �� �������� �Ȱ��� �޴� �ǵ� ���� ������?
	
public:
	Calculator()
	{
		Data();
	}
	
	// �ڽ� Ŭ�������� ���� ���Ǵ� "���� �ڵ� �ۼ�"�� �����
	// �ٷ� "�Լ�"�̴�

	// Data�� �Լ��� ��������, ������ �ٲ���
	// �Լ��� �뵵�� ����ϴ� ��� ���� ���� �� ���� ��ȯ�ϵ���
	int Add(int x, int y)
	{
		return x + y;
	}

	int Sub(int x, int y)
	{
		// �ð� ����� �Ű������� �Ἥ ���� �� ��ȯ
		return x - y;
	}

	int Mult(int x, int y)
	{
		return x * y;
	}

	int Div(int x, int y)
	{
		if (y != 0)
		{
			return x / y;
		}
		else
		{
			return 0;
		}
		
	}

	int Nam(int x, int y)
	{
		if (y != 0)
		{
			return x % y;
		}
		else
		{
			return 0;
		}
	}
};


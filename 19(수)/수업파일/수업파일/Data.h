#pragma once
#include <iostream>

class Data
{
protected:

	// �����Ϳ� ������
	int number1;
	int number2;
	int number3;

	float float1;
	float float2;
	float float3;

public:
	Data()
	{
		number1 = 0;
		number2 = 0;
		number3 = 0;
		float float1 = 0;
		float float2 = 0;
		float float3 = 0;
	}

	// �����Ϳ� �̸� "�� �����ͷ� �� �� �ִ� �Լ�"�� �⺻ �ȳ��� �ۼ�
	int Add(int x, int y)
	{
		std::cout << "�� �Լ��� ���ϱ⸦ ���� ��������ϴ�." << std::endl;
		return 0;
	}

	int Sub(int x, int y)
	{
		std::cout << "�� �Լ��� ���⸦ ���� ��������ϴ�." << std::endl;
		return 0;
	}

	int Mult(int x, int y)
	{
		std::cout << "�� �Լ��� ���ϱ⸦ ���� ��������ϴ�." << std::endl;
		return 0;
	}

	int Div(int x, int y)
	{
		std::cout << "�� �Լ��� �����⸦ ���� ��������ϴ�." << std::endl;
		return 0;
	}

	int Nam(int x, int y)
	{
		std::cout << "�� �Լ��� ������ ������ ���� ��������ϴ�." << std::endl;
		return 0;
	}
};


#pragma once
#include "Data.h"

class Add : public Data
{
public:
	Add() {}

	virtual void Calcs()
	{
		std::cout << std::endl;
		std::cout << "���ϱ� ����� �����մϴ�" << std::endl;
		std::cout << "[ ��� ��� ] " << number1 << " + " << number2 << " = " << number1 + number2 << std::endl;
		std::cout << std::endl;

		return;
	}
};


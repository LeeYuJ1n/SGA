#pragma once
#include "Data.h"

class Div : public Data
{
public:
	Div() {}

	virtual void Calcs()
	{
		std::cout << std::endl;
		std::cout << "������ ����� �����մϴ�" << std::endl;
		std::cout << "[ ��� ��� ] " << number1 << " / " << number2 << " = " << number1 / number2 << std::endl;
		std::cout << std::endl;

		return;
	}
};


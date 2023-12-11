#pragma once
#include "Data.h"

class Sub : public Data
{
public:
	Sub() {}

	virtual void Calcs()
	{
		std::cout << std::endl;
		std::cout << "빼기 계산을 시작합니다" << std::endl;
		std::cout << "[ 계산 결과 ] " << number1 << " - " << number2 << " = " << number1 - number2 << std::endl;
		std::cout << std::endl;

		return;
	}
};


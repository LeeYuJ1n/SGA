#pragma once
#include <iostream>

class Data
{
protected:
	int number1 = 10;
	int number2 = 5;
	
public:
	virtual void Calcs() = 0;

	Data() {}
};


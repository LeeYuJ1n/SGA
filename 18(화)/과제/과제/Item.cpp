#include <iostream>
#include "Item.h"

void Item::strengthUp_Result()
{
	std::cout << "ü�� ����(100)" << std::endl;

	int heal = 100;

	strength += heal;
}
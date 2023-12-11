#include <iostream>
#include "Item.h"

void Item::strengthUp_Result()
{
	std::cout << "체력 물약(100)" << std::endl;

	int heal = 100;

	strength += heal;
}
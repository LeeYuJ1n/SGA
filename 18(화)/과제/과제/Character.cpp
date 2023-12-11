#include <iostream>
#include "Character.h"

void Character::PrintStat()
{
	if (id == 1)
	{
		std::cout << std::endl;
		std::cout << "도화가" << std::endl;
	}
	else if (id == 2)
	{
		std::cout << std::endl;
		std::cout << "기상술사" << std::endl;
	}
	std::cout << "레벨 : " << level << std::endl;
	std::cout << "체력 : " << strength << std::endl;
	std::cout << "공격력 : " << power << std::endl;
	std::cout << "아이템 : " << item << std::endl;
}

void Character::Attack(Character* target)
{
	
}

void Character::SpecUp()
{
	if (id == 1)
	{
		if (strength <= 500)
		{
			strengthUp_Result();
		}
		else
		{
			std::cout << "조건이 충족되지 않아 아이템을 사용할 수 없습니다" << std::endl;
		}
	}
}
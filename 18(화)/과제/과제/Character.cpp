#include <iostream>
#include "Character.h"

void Character::PrintStat()
{
	if (id == 1)
	{
		std::cout << std::endl;
		std::cout << "��ȭ��" << std::endl;
	}
	else if (id == 2)
	{
		std::cout << std::endl;
		std::cout << "������" << std::endl;
	}
	std::cout << "���� : " << level << std::endl;
	std::cout << "ü�� : " << strength << std::endl;
	std::cout << "���ݷ� : " << power << std::endl;
	std::cout << "������ : " << item << std::endl;
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
			std::cout << "������ �������� �ʾ� �������� ����� �� �����ϴ�" << std::endl;
		}
	}
}
#pragma once
#include <iostream>
#include "Character.h"

class Character_Group
{
private:
	// ĳ���� ����
	Character* avatar1;
	Character* avatar2;

public:
	// Character�⺻ ������
	Character_Group()
	{
		avatar1 = new Character();
		avatar2 = new Character();

		avatar1 = nullptr;
		avatar2 = nullptr;

		avatar1 = new Character(1, 50, 1000, 100);
		avatar2 = new Character(1, 50, 1000, 100);

		std::cout << "1 ĳ���� ���̵� : " << avatar1->GetId() << std::endl;
		std::cout << "1 ĳ���� ������ ���� : " << avatar1->GetLevel() << std::endl;
		std::cout << "1 ĳ���� ü�� : " << avatar1->GetStrength() << std::endl;
		std::cout << "1 ĳ���� ���ݷ� : " << avatar1->GetPower() << std::endl;

		delete avatar1;
		delete avatar2;
	}

	~Character_Group()
	{
		delete avatar1;
		delete avatar2;
	}
};
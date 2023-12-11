#pragma once
#include <iostream>
#include "Character.h"

class Character_Group
{
private:
	// 캐릭터 구현
	Character* avatar1;
	Character* avatar2;

public:
	// Character기본 생성자
	Character_Group()
	{
		avatar1 = new Character();
		avatar2 = new Character();

		avatar1 = nullptr;
		avatar2 = nullptr;

		avatar1 = new Character(1, 50, 1000, 100);
		avatar2 = new Character(1, 50, 1000, 100);

		std::cout << "1 캐릭터 아이디 : " << avatar1->GetId() << std::endl;
		std::cout << "1 캐릭터 아이팀 레벨 : " << avatar1->GetLevel() << std::endl;
		std::cout << "1 캐릭터 체력 : " << avatar1->GetStrength() << std::endl;
		std::cout << "1 캐릭터 공격력 : " << avatar1->GetPower() << std::endl;

		delete avatar1;
		delete avatar2;
	}

	~Character_Group()
	{
		delete avatar1;
		delete avatar2;
	}
};
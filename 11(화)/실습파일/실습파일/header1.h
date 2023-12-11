#pragma once
#include <iostream>
#include <Windows.h>

void Print()
{
	struct Character
	{
		int rawID;
		char character[20];
		int strength;
		int attack;
		
		const int* id = &rawID;
	};

	Character chara;
	chara.rawID = 1;
	chara.strength = 100;
	chara.attack = 10;
	chara.id;

	std::cout << "캐릭터 : " << *chara.id << std::endl;
	std::cout << "체력 : " << chara.strength << std::endl;
	std::cout << "공격력 : " << chara.attack << std::endl;

	std::cout << std::endl;

	Character chara2;
	chara2.rawID = 2;
	chara2.strength = 200;
	chara2.attack = 10;
	chara2.id;

	std::cout << "캐릭터 : " << *chara2.id << std::endl;
	std::cout << "체력 : " << chara2.strength << std::endl;
	std::cout << "공격력 : " << chara2.attack << std::endl;

	std::cout << std::endl;
}
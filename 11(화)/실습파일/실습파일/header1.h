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

	std::cout << "ĳ���� : " << *chara.id << std::endl;
	std::cout << "ü�� : " << chara.strength << std::endl;
	std::cout << "���ݷ� : " << chara.attack << std::endl;

	std::cout << std::endl;

	Character chara2;
	chara2.rawID = 2;
	chara2.strength = 200;
	chara2.attack = 10;
	chara2.id;

	std::cout << "ĳ���� : " << *chara2.id << std::endl;
	std::cout << "ü�� : " << chara2.strength << std::endl;
	std::cout << "���ݷ� : " << chara2.attack << std::endl;

	std::cout << std::endl;
}
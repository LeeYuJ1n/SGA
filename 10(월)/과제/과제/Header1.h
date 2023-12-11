#pragma once
#include <iostream>
#include <Windows.h>

void Print()
{
	int loop = true;

	struct Character
	{
		// 수정 가능한 캐릭터 공유 변수
		int rawID;
		int health;
		int attack;

		// 수정이 불가능 "상수 포인터"
		const int* id = &rawID;
	};

	// 캐릭터 1
	Character chara;
	chara.rawID = 1;
	chara.health = 100;
	chara.attack = 10;
	chara.id;

	std::cout << "캐릭터 : " << *chara.id << std::endl;
	std::cout << "체력 : " << chara.health << std::endl;
	std::cout << "공격력 : " << chara.attack << std::endl;

	std::cout << std::endl;

	// 캐릭터 2
	Character chara2;
	chara2.rawID = 2;
	chara2.health = 100;
	chara2.attack = 15;
	chara2.id;

	std::cout << "캐릭터 : " << *chara2.id << std::endl;
	std::cout << "체력 : " << chara2.health << std::endl;
	std::cout << "공격력 : " << chara2.attack << std::endl;

	std::cout << std::endl;

	// 캐릭터 3
	Character chara3;
	chara3.rawID = 3;
	chara3.health = 100;
	chara3.attack = 20;
	chara3.id;

	std::cout << "캐릭터 : " << *chara3.id << std::endl;
	std::cout << "체력 : " << chara3.health << std::endl;
	std::cout << "공격력 : " << chara3.attack << std::endl;
};
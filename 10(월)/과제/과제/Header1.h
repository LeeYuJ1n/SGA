#pragma once
#include <iostream>
#include <Windows.h>

void Print()
{
	int loop = true;

	struct Character
	{
		// ���� ������ ĳ���� ���� ����
		int rawID;
		int health;
		int attack;

		// ������ �Ұ��� "��� ������"
		const int* id = &rawID;
	};

	// ĳ���� 1
	Character chara;
	chara.rawID = 1;
	chara.health = 100;
	chara.attack = 10;
	chara.id;

	std::cout << "ĳ���� : " << *chara.id << std::endl;
	std::cout << "ü�� : " << chara.health << std::endl;
	std::cout << "���ݷ� : " << chara.attack << std::endl;

	std::cout << std::endl;

	// ĳ���� 2
	Character chara2;
	chara2.rawID = 2;
	chara2.health = 100;
	chara2.attack = 15;
	chara2.id;

	std::cout << "ĳ���� : " << *chara2.id << std::endl;
	std::cout << "ü�� : " << chara2.health << std::endl;
	std::cout << "���ݷ� : " << chara2.attack << std::endl;

	std::cout << std::endl;

	// ĳ���� 3
	Character chara3;
	chara3.rawID = 3;
	chara3.health = 100;
	chara3.attack = 20;
	chara3.id;

	std::cout << "ĳ���� : " << *chara3.id << std::endl;
	std::cout << "ü�� : " << chara3.health << std::endl;
	std::cout << "���ݷ� : " << chara3.attack << std::endl;
};
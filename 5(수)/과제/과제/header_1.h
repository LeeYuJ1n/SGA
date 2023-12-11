#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>


// 구조체(캐릭터 정보)
struct Character1
{
	int level = 1; // 레벨
	int strength = 1000; // 체력
	int power = 50; // 공격력
};

// Character_1에 대한 인스턴스 생성
Character1 Cha1;

struct Character2
{
	int level = 1; // 레벨
	int strength = 900; // 체력
	int power = 50; // 공격력
};

// Character_2에 대한 인스턴스 생성
Character2 Cha2;

void Cha1_atk(int* Cha2_strength, int* Cha1_power)
{
	while (true)
	{
		int inputSelect;

		std::cout << "게임을 시작합니다" << std::endl;
		std::cout << std::endl;
		std::cout << "1. 전투시작 / 2. 게임종료" << std::endl;
		std::cout << "입력 : ";
		std::cin >> inputSelect;

		switch (inputSelect)
		{
		case 1:
			system("cls");
			std::cout << "레벨 : " << Cha1.level << std::endl;
			std::cout << "체력 : " << Cha1.strength << std::endl;
			std::cout << "체력 : " << Cha1.power << std::endl;
			std::cout << std::endl;
			std::cout << "3초뒤 전투를 시작합니다" << std::endl;

			Sleep(3000);
			system("cls");

			while (true)
			{
				if (Cha1.strength > Cha2.strength)
				{
					std::cout << "---------------------------------------------------" << std::endl;
					std::cout << "상대방에게 공격을 시도합니다" << std::endl;
					std::cout << std::endl;

					std::cout << "공격을 성공하였습니다" << std::endl;
					std::cout << std::endl;

					std::cout << "상대방 체력이 " << *Cha2_strength << "에서 공격을 받아 ";;

					*Cha2_strength = *Cha2_strength - *Cha1_power;

					std::cout << *Cha2_strength << "이(가) 남았습니다" << std::endl;
					std::cout << "---------------------------------------------------" << std::endl;
					Sleep(1000);
				}
				else if (Cha1.strength < Cha2.strength)
				{

				}
				else if (Cha2.strength <= 0)
				{
					std::cout << "승리" << std::endl;
					false;
					break;
				}
				continue;
			}

		case 2:
			std::cout << "게임종료" << std::endl;
			false;
			break;

		default:
			std::cout << std::endl;
			std::cout << "잘못된 입력입니다." << std::endl;
			Sleep(3000);
			system("cls");
			break;
		}
		continue;
	}
}
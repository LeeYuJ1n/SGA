#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>


// ����ü(ĳ���� ����)
struct Character1
{
	int level = 1; // ����
	int strength = 1000; // ü��
	int power = 50; // ���ݷ�
};

// Character_1�� ���� �ν��Ͻ� ����
Character1 Cha1;

struct Character2
{
	int level = 1; // ����
	int strength = 900; // ü��
	int power = 50; // ���ݷ�
};

// Character_2�� ���� �ν��Ͻ� ����
Character2 Cha2;

void Cha1_atk(int* Cha2_strength, int* Cha1_power)
{
	while (true)
	{
		int inputSelect;

		std::cout << "������ �����մϴ�" << std::endl;
		std::cout << std::endl;
		std::cout << "1. �������� / 2. ��������" << std::endl;
		std::cout << "�Է� : ";
		std::cin >> inputSelect;

		switch (inputSelect)
		{
		case 1:
			system("cls");
			std::cout << "���� : " << Cha1.level << std::endl;
			std::cout << "ü�� : " << Cha1.strength << std::endl;
			std::cout << "ü�� : " << Cha1.power << std::endl;
			std::cout << std::endl;
			std::cout << "3�ʵ� ������ �����մϴ�" << std::endl;

			Sleep(3000);
			system("cls");

			while (true)
			{
				if (Cha1.strength > Cha2.strength)
				{
					std::cout << "---------------------------------------------------" << std::endl;
					std::cout << "���濡�� ������ �õ��մϴ�" << std::endl;
					std::cout << std::endl;

					std::cout << "������ �����Ͽ����ϴ�" << std::endl;
					std::cout << std::endl;

					std::cout << "���� ü���� " << *Cha2_strength << "���� ������ �޾� ";;

					*Cha2_strength = *Cha2_strength - *Cha1_power;

					std::cout << *Cha2_strength << "��(��) ���ҽ��ϴ�" << std::endl;
					std::cout << "---------------------------------------------------" << std::endl;
					Sleep(1000);
				}
				else if (Cha1.strength < Cha2.strength)
				{

				}
				else if (Cha2.strength <= 0)
				{
					std::cout << "�¸�" << std::endl;
					false;
					break;
				}
				continue;
			}

		case 2:
			std::cout << "��������" << std::endl;
			false;
			break;

		default:
			std::cout << std::endl;
			std::cout << "�߸��� �Է��Դϴ�." << std::endl;
			Sleep(3000);
			system("cls");
			break;
		}
		continue;
	}
}
#pragma once

#include <iostream>
#include <windows.h>

void TaitanicExit()
{
	int loop = true;

	// ����
	int numBoat = 0; // �ּ� ��Ʈ ��
	int boatPeopleMax = 2; // ��Ʈ�� ž���� �� �ִ� �ִ� �ο�
	int boatWeigth = 0; // ���� ���� �Ǹ� ����
	int boatPeople = 0; // ���� ���� Ÿ�� �ִ� ���
	int boatMaxWeight = 100; // �ִ� �����Ը� 100kg���� ����

	// 10���� ����� �����Ը� 1���� �迭�� �����
	int weight[10] = { 10, 10, 10, 10, 10, 10, 10, 70, 40, 50 };

	while (loop)
	{
		for (int i = 0; i < 10; i++)
		{
			if (boatPeople < boatPeopleMax && boatWeigth + weight[i] <= boatMaxWeight)
			{
				// ���� ���� ����� �� �¿� �� �ִ� ���

				// ���� ���� �Ǹ� ���� += ������
				boatWeigth += weight[i];
				
				// ���� ���� Ÿ�� �ִ� ��� ��
				boatPeople++;

				// �ּ� ��Ʈ �� = ���� ��Ʈ�� Ÿ�� �ִ� ���
				numBoat = boatPeople;
			}
			else
			{
				// �ٸ� ��� �¿��� �� ���

				// �ּ� ��Ʈ ��
				numBoat++;

				// ���� ��Ʈ�� Ÿ�� �ִ� ��� = ������
				boatPeople = weight[i];

				// ���� ��Ʈ�� Ÿ�� �ִ� ���
				boatPeople = 1;
			}
		}

		if (boatPeople > 0)
		{
			// ������ �谡 ���� �̿ϼ��� ���

			// �ּ� ��Ʈ ��
			numBoat + 1;
		}

		loop = false;

		system("cls");

		std::cout << "2023�� 7�� 7�� ���� : Ÿ��Ÿ�� Ż��" << std::endl;
		std::cout << "��� : �ּ� " << numBoat << "�� �ʿ�" << std::endl;
	}
}
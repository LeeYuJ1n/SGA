#pragma once

#include <iostream>
#include <windows.h>

void TaitanicExit()
{
	int loop = true;

	// 설정
	int numBoat = 0; // 최소 보트 수
	int boatPeopleMax = 2; // 보트에 탑승할 수 있는 최대 인원
	int boatWeigth = 0; // 현재 배의 실린 무게
	int boatPeople = 0; // 현재 배의 타고 있는 사람
	int boatMaxWeight = 100; // 최대 몸무게를 100kg으로 지정

	// 10명의 사람의 몸무게를 1차원 배열로 만들기
	int weight[10] = { 10, 10, 10, 10, 10, 10, 10, 70, 40, 50 };

	while (loop)
	{
		for (int i = 0; i < 10; i++)
		{
			if (boatPeople < boatPeopleMax && boatWeigth + weight[i] <= boatMaxWeight)
			{
				// 현재 배의 사람을 더 태울 수 있는 경우

				// 현재 배의 실린 무게 += 몸무게
				boatWeigth += weight[i];
				
				// 현재 배의 타고 있는 사람 수
				boatPeople++;

				// 최소 보트 수 = 현재 보트에 타고 있는 사람
				numBoat = boatPeople;
			}
			else
			{
				// 다른 배로 태워야 할 경우

				// 최소 보트 수
				numBoat++;

				// 현재 보트에 타고 있는 사람 = 몸무게
				boatPeople = weight[i];

				// 현재 보트에 타고 있는 사람
				boatPeople = 1;
			}
		}

		if (boatPeople > 0)
		{
			// 마지막 배가 아직 미완성인 경우

			// 최소 보트 수
			numBoat + 1;
		}

		loop = false;

		system("cls");

		std::cout << "2023년 7월 7일 과제 : 타이타닉 탈출" << std::endl;
		std::cout << "결과 : 최소 " << numBoat << "대 필요" << std::endl;
	}
}
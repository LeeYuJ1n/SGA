// 2023년 6월 21일 수요일 과제
// 김유준

#include <iostream>
#include <windows.h>
#include <stdlib.h>

int main()
{
	int cardGame = true;
	int playerScore = 0, computerScore = 0;


	while (cardGame)
	{
		int playerCard1, playerCard2, playerCard3, computerCard1, computerCard2;
		int playerCardResult1 = 0, playerCardResult2 = 0, playerCardResult3 = 0, computerCardResult1 = 0, computerCardResult2 = 0;
		int playerResult = 0, computerResult = 0;
		int select;

		std::cout << "게임을 시작합니다." << std::endl;
		std::cout << "" << std::endl;

		std::cout << "플레이어 점수 : " << playerScore << std::endl;
		std::cout << "" << std::endl;
		std::cout << "상대 점수 : " << computerScore << std::endl;
		std::cout << "" << std::endl;

		int card[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

		srand(GetTickCount64());

		playerCard1 = rand() % 12 + 1;
		playerCard2 = rand() % 12 + 1;
		computerCard1 = rand() % 12 + 1;
		computerCard2 = rand() % 12 + 1;

		std::cout << "잠시 후 플레이어와 상대방에게 2장씩 카드가 지급됩니다" << std::endl;
		playerCardResult1 = (playerCard1 / 10) % 10;
		playerCardResult2 = playerCard2 % 10;

		computerCardResult1 = (computerCard1 / 10) % 10;
		computerCardResult2 = computerCard2 % 10;

		playerResult = playerCardResult1 + playerCardResult2;
		computerResult = computerCard1 + computerCard2;

		Sleep(1000);

		std::cout << "-----------------------------------------------------------------------------------" << std::endl;
		std::cout << "카드 지급이 완료되었습니다." << std::endl;
		std::cout << "-----------------------------------------------------------------------------------" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "-----------------------------------------------------------------------------------" << std::endl;
		std::cout << "플레이어 카드 : " << "[ " << playerCardResult1 << " ]" << ", " << "[ " << playerCardResult2 << " ]" << std::endl;
		std::cout << "플레이어의 카드 합 : " << playerResult << std::endl;
		std::cout << "-----------------------------------------------------------------------------------" << std::endl;
		std::cout << "자신의 숫자가 크다 : 1" << std::endl;
		std::cout << "컴퓨터의 숫자가 크다 : 2" << std::endl;
		std::cout << "나의 숫자와 컴퓨터의 숫자가 같다 : 3" << std::endl;
		std::cout << "-----------------------------------------------------------------------------------" << std::endl;
		std::cout << "입력 : ";
		std::cin >> select;
		

		switch (select)
		{
		case 1:
			if (playerResult < computerResult)
			{
				std::cout << "틀렸습니다." << std::endl;
				std::cout << "컴퓨터의 카드 합 : " << computerResult << std::endl;
				computerScore++;
				Sleep(3000);
				system("cls");
				break;
			}
			else if (playerResult > computerResult)
			{
				std::cout << "정답입니다." << std::endl;
				std::cout << "컴퓨터의 카드 합 : " << computerResult << std::endl;
				playerScore++;
				Sleep(3000);
				system("cls");
				break;
			}

		case 2:
			if (playerResult < computerResult)
			{
				std::cout << "정답입니다." << std::endl;
				std::cout << "컴퓨터의 카드 합 : " << computerResult << std::endl;
				playerScore++;
				Sleep(3000);
				system("cls");
				break;
			}
			else if (playerResult > computerResult)
			{
				std::cout << "틀렸습니다" << std::endl;
				std::cout << "컴퓨터의 카드 합 : " << computerResult << std::endl;
				computerScore++;
				Sleep(3000);
				system("cls");
				break;
			}

		case 3:
			if (playerResult == computerResult)
			{
				std::cout << "정답입니다." << std::endl;
				std::cout << "컴퓨터의 카드 합 : " << computerResult << std::endl;
				playerScore++;
				Sleep(3000);
				system("cls");
				break;
			}
			else
			{
				std::cout << "틀렸습니다" << std::endl;
				std::cout << "컴퓨터의 카드 합 : " << computerResult << std::endl;
				computerScore++;
				Sleep(3000);
				system("cls");
				break;
			}

		case 4:
			if (playerResult <= 6)
			{
				std::cout << "카드 한장을 더 뽑은 결과입니다." << std::endl;
				playerCard3 = rand() % 12 + 1;
				playerCardResult3 = (playerCard3 / 10) % 10;
				std::cout << "플레이어 카드 : " << "[ " << playerCardResult1 << " ]" << ", " << "[ " << playerCardResult2 << " ]" << "[ " << playerCardResult3 << " ]" << std::endl;
				break;
			} 
		}

		if (playerScore == 3)
		{
			std::cout << "게임에서 승리하였습니다." << std::endl;
			std::cout << "플레이어 : " << playerScore << std::endl;
			std::cout << "컴퓨터 : " << computerScore << std::endl;
			break;
		}
		else if (computerScore == 3)
		{
			std::cout << "게임에서 패배하였습니다." << std::endl;
			std::cout << "플레이어 : " << playerScore << std::endl;
			std::cout << "컴퓨터 : " << computerScore << std::endl;
			break;
		}
	}
}
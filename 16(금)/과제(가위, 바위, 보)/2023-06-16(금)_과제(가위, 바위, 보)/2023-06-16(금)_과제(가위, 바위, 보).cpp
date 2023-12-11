// 2023년 6월 16일 금요일 과제 (가위, 바위, 보)
// 김유준

#include <iostream>
#include <Windows.h>
#include <stdlib.h>

int main()
{
    int j = 0, score = 0, ai_score = 0;

    std::cout << "가위, 바위, 보 게임을 시작합니다" << std::endl;
    std::cout << "0 = 가위" << std::endl;
    std::cout << "1 = 바위" << std::endl;
    std::cout << "2 = 보" << std::endl;
    std::cout << "" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        int randomNumber = rand();
        srand(GetTickCount64());
        randomNumber = rand() % 2;
        
        std::cout << "[ 플레이어 현재 점수 ] : " << score << std::endl;
        std::cout << "[ 컴퓨터 점수 ] : " << ai_score << std::endl;
        std::cout << "[ 상대방 ] : " << randomNumber << std::endl;
        std::cout << "숫자를 입력해주세요 : ";
        std::cin >> j;
        
        if ((j < 0 || j > 2))
        {
            std::cout << "" << std::endl;
            std::cout << "[ 주의 ] 0 ~ 2까지의 숫자를 입력해주세요" << std::endl;
            std::cout << "" << std::endl;
            --i;
        }

        if ((j == 0 && randomNumber == 2) || (j == 1 && randomNumber == 0) || (j == 2 && randomNumber == 1))
        {
            std::cout << "이겼습니다" << std::endl;
            std::cout << "" << std::endl;
            score = score + 1;
        }
        else if ((j == 0 && randomNumber == 1) || (j == 1 && randomNumber == 2) || (j == 2 && randomNumber == 0))
        {
            std::cout << "졌습니다." << std::endl;
            std::cout << "" << std::endl;
            ai_score = ai_score + 1;

        }
        else if ((j == 0 && randomNumber == 0) || (j == 1 && randomNumber == 1) || (j == 2 && randomNumber == 2 ))
        {
            std::cout << "비겼습니다." << std::endl;
            std::cout << "" << std::endl;
        }

        if (i == 2)
        {
            std::cout << "" << std::endl;

            if (score > ai_score)
            {
                std::cout << "[ 승리 ] 당신이 " << score << " : " << ai_score << "으로 이겼습니다!" << std::endl;
                break;
            }
            else if (score < ai_score)
            {
                std::cout << "[ 패배 ] 당신은 " << score << " : " << ai_score << "으로 졌습니다..." << std::endl;
                break;
            }
            else
            {
                std::cout << "[ 무승부 ] 당신은 " << score << " : " << ai_score << "으로 비겼습니다!" << std::endl;
                break;
            }
        }
    }
}
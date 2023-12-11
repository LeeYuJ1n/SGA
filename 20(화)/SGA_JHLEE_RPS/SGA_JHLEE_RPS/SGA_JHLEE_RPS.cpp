#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    srand(GetTickCount64());

    //점수
    int playerScore = 0;
    int computerScore = 0;

    //가위 바위 보 게임

    for (int i = 0; i < 3; ++i)
    {
        int computerChoice = rand() % 3;
        //값이 0, 1, 2 중 하나
        // 0 : 가위, 1 : 바위, 2 : 보

        int playerChoice;

        std::cout << "가위 바위 보 게임" << std::endl;
        std::cout << "0, 1, 2 중 한 가지 숫자를 입력해주세요" << std::endl;
        std::cout << "입력 : ";
        std::cin >> playerChoice;

        //조건문을 구성하는 방법
        // 1. 내가 무슨 입력을 했고, 컴퓨터가 또 무슨 입력을 했는지 한 번에 비교
        // 2. 내가 무슨 입력을 했는지에 대해서 조건문을 하나 쓰고, 그 안에서 컴퓨터의 입력을 또 확인
        // 여기서는 2번 방법을 사용

        // if (playerChoice == 0 && computerChoice == 1) : 1번 방법

        if (playerChoice == 0)
        {
            if (computerChoice == 0)
            {
                std::cout << "비겼습니다." << std::endl;
            }
            else if (computerChoice == 1)
            {
                std::cout << "컴퓨터가 이겼습니다." << std::endl;
                computerScore++;
                //computerScore += 1;
                //computerScore = computerScore + 1;
            }
            else if (computerChoice == 2)
            {
                std::cout << "여러분이 이겼습니다." << std::endl;
                playerScore++;
            }
        }
        else if (playerChoice == 1)
        {
            if (computerChoice == 0)
            {
                std::cout << "여러분이 이겼습니다." << std::endl;
                playerScore++;
            }
            else if (computerChoice == 1)
            {
                std::cout << "비겼습니다." << std::endl;
            }
            else if (computerChoice == 2)
            {
                std::cout << "컴퓨터가 이겼습니다." << std::endl;
                computerScore++;
            }
        }
        else if (playerChoice == 2)
        {
            if (computerChoice == 0)
            {
                std::cout << "컴퓨터가 이겼습니다." << std::endl;
                computerScore++;
            }
            else if (computerChoice == 1)
            {
                std::cout << "여러분이 이겼습니다." << std::endl;
                playerScore++;
            }
            else if (computerChoice == 2)
            {
                std::cout << "비겼습니다." << std::endl;
            }
        }
        else // 입력을 할 때, 0, 1, 2 이외의 다른 뭔가를 입력한 경우 (가위바위보 불성립)
        {
            std::cout << "입력이 틀렸습니다. 무효 처리합니다." << std::endl;
        }
    }

    //반복문이 끝나고 나오면 점수를 서로 비교

    std::cout << "최종 점수 비교" << std::endl;
    std::cout << "내 점수 : ";
    std::cout << playerScore << std::endl;
    std::cout << "컴퓨터 점수 : " << computerScore << std::endl;
    // cout 코드는 <<를 여러 번 반복해서 계속 데이터를 다르게 출력하는 것도 가능

    //점수 비교에 따른 최종 승자 확인

    if (playerScore > computerScore)
    {
        std::cout << "여러분이 마지막에 이겼습니다." << std::endl;
    }
    else if (computerScore > playerScore)
    {
        std::cout << "컴퓨터가 마지막에 이겼습니다." << std::endl;
    }
    else //두 값이 같은 경우뿐
    {
        std::cout << "비겼습니다." << std::endl;
    }
}
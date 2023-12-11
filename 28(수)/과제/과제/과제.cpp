#include <iostream>
#include <Windows.h>
#include <stdlib.h>

int main()
{
    srand(GetTickCount64());

    char input_Char_Select;
    int input_Number_Select;
    int randomNumber_1 = 0, inputNumber_1 = 0, playerScore = 0;
    bool randomNumber_view_1;

    randomNumber_1 = rand() % 37;

    std::cout << "숫자 맞추기 게임" << std::endl;
    std::cout << std::endl;
    std::cout << "메뉴를 선택해주세요" << std::endl;
    std::cout << "[ y ] 게임 시작하기" << std::endl;
    std::cout << "[ n ] 종료하기" << std::endl;
    std::cout << "입력 : ";
    std::cin >> input_Char_Select;

    switch (input_Char_Select)
    {
    case 'y':
        system("cls");
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "게임을 시작합니다" << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        Sleep(3000);
        system("cls");
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "[ 현재 점수 ] : " << playerScore << "점" << std::endl;
        std::cout << "[ 랜덤으로 생성된 숫자 ] : " << randomNumber_1 << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << "점수 안내" << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "[ 35점 ] 정확히 맞출경우" << std::endl;
        std::cout << "[ 25점 ] 1의 오차가 있을 경우" << std::endl;
        std::cout << "[ 15점 ] 2의 오차가 있을 경우" << std::endl;
        std::cout << "[ 10점 ] 맞추는 숫자와 내가 입력한 숫자가 둘다 짝수 및 홀수인 경우" << std::endl;
        std::cout << "[  5점 ] 맞추는 숫자보다 내 숫자가 크거나 같은 경우" << std::endl;
        std::cout << "[  5점 ] 맞추는 숫자보다 내 숫자가 작거나 같은 경우" << std::endl;
        std::cout << "랜덤으로 수가 생성되었습니다" << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "랜덤으로 수가 생성되었습니다" << std::endl;
        std::cout << "랜덤으로 생성된 숫자를 맞춰주세요" << std::endl;
        std::cout << "0을 입력 했을 경우 랜덤 숫자가 0이 아니면 바로 패배합니다" << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "입력 : ";
        std::cin >> inputNumber_1;

        if (randomNumber_1 == 0)
        {
            randomNumber_view_1 = false;
        }
        else if (randomNumber_1 != 0)
        {
            randomNumber_view_1 = true;
        }

        if (randomNumber_view_1 == false)
        {
            playerScore = 0;
            std::cout << "정답입니다" << std::endl;
            std::cout << "[ 점수 ] : " << playerScore + 35 << "점" << std::endl;
        }
        else
        {
            std::cout << "정답은 0이었습니다" << std::endl;
            std::cout << "[ 점수 ] : " << playerScore + 0 << "점" << std::endl;
        }
        
        if (randomNumber_view_1 == true)
        {

            if ((inputNumber_1 == randomNumber_1) || (inputNumber_1 > randomNumber_1) || (inputNumber_1 < randomNumber_1))
            {
                system("cls");
                std::cout << "---------------------------------------------------------------" << std::endl;
                std::cout << "[ 입력한 숫자 ] : " << inputNumber_1 << std::endl;
                std::cout << "---------------------------------------------------------------" << std::endl;
                std::cout << "아래 메뉴를 선택해주세요" << std::endl;
                std::cout << "[ 메뉴 1 ] : 내가 선택한 그 숫자가 완전히 맞다" << std::endl;
                std::cout << "[ 메뉴 2 ] : 오차가 1 있을 것 같다" << std::endl;
                std::cout << "[ 메뉴 3 ] : 오차가 2 있을 것 같다" << std::endl;
                std::cout << "[ 메뉴 4 ] : 내 선택이 홀수면 어쨌든 맞추는 숫자도 같은 홀수이고, 짝수면 같은 짝수 같다" << std::endl;
                std::cout << "[ 메뉴 5 ] : 어쨌든 맞추는 숫자가 내 결정보다 크거나 같은 것 같다" << std::endl;
                std::cout << "[ 메뉴 6 ] : 어쨌든 맞추는 숫자가 내 결정보다 작거나 같은 것 같다" << std::endl;
                std::cout << "---------------------------------------------------------------" << std::endl;
                std::cout << "입력 : ";
                std::cin >> input_Number_Select;

                switch (input_Number_Select)
                {
                case 1:
                    // [ 메뉴 1 ] : 내가 선택한 그 숫자가 완전히 맞다
                    if (inputNumber_1 == randomNumber_1)
                    {
                        playerScore = 0;
                        std::cout << "정답입니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore + 35 << "점" << std::endl;
                    }
                    else
                    {
                        std::cout << "틀렸습니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore << "점" << std::endl;
                    }
                    break;

                case 2:
                    // [ 메뉴 2 ] : 오차가 1 있을 것 같다
                    if (inputNumber_1 - randomNumber_1 == 1 || inputNumber_1 - randomNumber_1 == -1)
                    {
                        playerScore = 0;
                        std::cout << "정답입니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore + 25 << "점" << std::endl;
                    }
                    else
                    {
                        std::cout << "틀렸습니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore << "점" << std::endl;
                    }
                    break;

                case 3:
                    // [ 메뉴 3 ] : 오차가 2 있을 것 같다
                    if (inputNumber_1 - randomNumber_1 == 2 || inputNumber_1 - randomNumber_1 == -2)
                    {
                        playerScore = 0;
                        std::cout << "정답입니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore + 25 << "점" << std::endl;
                    }
                    else
                    {
                        std::cout << "틀렸습니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore << "점" << std::endl;
                    }
                    break;

                case 4:
                    // [ 메뉴 4 ] : 내 선택이 홀수면 어쨌든 맞추는 숫자도 같은 홀수이고, 짝수면 같은 짝수 같다
                    if (inputNumber_1 % 2 == 0)
                    {
                        playerScore = 0;
                        std::cout << "짝수 정답니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore + 10 << "점" << std::endl;
                    }
                    else if (inputNumber_1 % 3 == 0)
                    {
                        playerScore = 0;
                        std::cout << "홀수 정답니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore + 10 << "점" << std::endl;
                    }
                    else
                    {
                        std::cout << "틀렸습니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore << "점" << std::endl;
                    }
                    break;

                case 5:
                    // [ 메뉴 5 ] : 어쨌든 맞추는 숫자가 내 결정보다 크거나 같은 것 같다
                    if (inputNumber_1 <= randomNumber_1)
                    {
                        playerScore = 0;
                        std::cout << "정답입니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore + 5 << "점" << std::endl;
                    }
                    else
                    {
                        std::cout << "틀렸습니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore << "점" << std::endl;
                    }
                    break;

                case 6:
                    // [ 메뉴 6 ] : 어쨌든 맞추는 숫자가 내 결정보다 작거나 같은 것 같다
                    if (inputNumber_1 >= randomNumber_1)
                    {
                        playerScore = 0;
                        std::cout << "정답입니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore + 5 << "점" << std::endl;
                    }
                    else
                    {
                        std::cout << "틀렸습니다" << std::endl;
                        std::cout << "[ 점수 ] : " << playerScore << "점" << std::endl;
                    }
                    break;

                default:
                    std::cout << "잘못된 입력입니다" << std::endl;
                    break;
                }
            }
        }
        case 'n':
            std::cout << "게임을 종료합니다" << std::endl;
            break;
    }
}
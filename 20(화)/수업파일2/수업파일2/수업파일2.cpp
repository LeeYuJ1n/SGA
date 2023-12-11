#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    for (int i = 0; i < 10; i++)
    {
        // 위 형태에서 짐작할 수 있는 for문의 특징

        // 시작 상황(첫 번째 조건)이 정확히 제시되어야 한다
        // 반복시 변화 상황을 적절히 제시하지 못하면 무한반복에 갇힐 수 있다
        // (→ 무한히 가능하지만, 무한이 기본 상황는 아닌 것)
        // 변화 상황을 제시할 경우, 반복의 횟수가 구제척으로 정확히 주어진다

        // → 딱 정해진 만큼만 반복하고 딱 잘라서 종료하고 싶을 때, for문은 가장 적절한 선택지가 된다
    }

    // 반복문 심화 : 다른 상황에서 사용할 수 있는 또 다른 반복문
    // 반복문으 경우, 이쪽이 더 자주 사용되는 경우도 있다

    // while (조건) { 반복한 코드 }

    int number = 0;

    while (number < 10) // ()안에 조건이 참인 동안 이 반복문은 돌아간다
    {
        std::cout << number << std::endl;
        number++; // 반복 한 번 할 때마다 number가 1 증가
    }

    // while은 조건이 주어지면 조건이 참인 동안은 무조건 돌아간다
    // 횟수가 문법 내에서 정해지지 않았다 : 무한이 기본
    // 코드 안에서 직접 변화를 줄 경우, 그 변화로 조건을 제어하는 것도 가능

    // → 미리 정해놓은 횟수가 없고, 될 때까지 하다가 조건이 맞춰지면 끝나는 다소 덜 구체적인 반복 상황에서는 while이 더 유용

    // while의 조금 더 흔한 활용법

    int number2 = 0;

    while (true) // 참은 그냥 참이므로, 이런 형태의 조건을 제시하면 while은 무한이 완전한 기본이 된다
    {
        std::cout << number2 << std::endl;
        number2++; // 반복마다 number2 1증가

        // while 안에서 if 사용(가능)
        if (number2 == 20)
        {
            // while 및 switch에서 break는 한 세트나 다름없다
            // break : 무한한 반복문에서 종료하는 시점 혹은 조건을 지정하는 코드
            break; // 반복문에서 다음 사례를 반복하지 않고, 아래 코드를 수행하지 않고 그대로 종료하는 코드
        }
    }

    // while의 무한반복 특성과 조건이 맞을 때 break되는 특성을 확인해보기 좋은 사례
    // "수동 종료"

    int number3;

    while (true)
    {
        std::cout << "숫자를 아무거나 입력해주세요.(단, 0은 종료입니다)" << std::endl;
        std::cout << "입력 : ";
        std::cin >> number3;

        std::cout << number3 << "를 입력 했습니다." << std::endl;

        if (number3 == 0)
        {
            break; // 넘버3이 0일 때 이 반복문 종료
        }
    }

    // 가위 바위 보를 while로 만들기

    srand(GetTickCount64());

    int player = 0, computer = 0, pScore = 0, cScore = 0;

    while (false)
    {
        computer = rand() % 3;

        std::cout << "가위 바위보 (0, 1, 2)사이에서 입력하세요." << std::endl;
        std::cout << "입력 : ";
        std::cin >> player;

        if (player == 0 && computer == 0)
        {
            std::cout << "비겼습니다" << std::endl;
        }
        else if (player == 0 && computer == 1)
        {
            std::cout << "컴퓨터가 이겼습니다." << std::endl;
            cScore++;
        }
        else if (player == 0 && computer == 2)
        {
            std::cout << "이겼습니다" << std::endl;
            pScore++;
        }
        else if (player == 1 && computer == 0)
        {
            std::cout << "이겼습니다" << std::endl;
            pScore++;
        }
        else if (player == 1 && computer == 1)
        {
            std::cout << "비겼습니다" << std::endl;
        }
        else if (player == 1 && computer == 2)
        {
            std::cout << "컴퓨터가 이겼습니다" << std::endl;
            cScore++;
        }
        else if (player == 2 && computer == 0)
        {
            std::cout << "컴퓨터가 이겼습니다" << std::endl;
            cScore++;
        }
        else if (player == 2 && computer == 1)
        {
            std::cout << "이겼습니다" << std::endl;
            pScore++;
        }
        else if (player == 2 && computer == 2)
        {
            std::cout << "비겼습니다" << std::endl;
        }

        if (player == 3 || computer == 3)
        {
            break;
        }
    }

    if (player > computer)
    {
        std::cout << "여러분이 마지막에 이겼습니다" << std::endl;
    }
    else // 비기는 경우가 있을 수 없으므로 이 경우 컴퓨터가 이긴 것
    {
        std::cout << "컴퓨터가 마지막에 이겼습니다" << std::endl;
    }
}

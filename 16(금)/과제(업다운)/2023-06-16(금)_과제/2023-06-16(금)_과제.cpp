// 2023년 6월 16일 금요일 과제
// 김유준

#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    srand(GetTickCount64());
    int randomNumber = rand();

    // 1 ~ 100까지 랜덤 숫자 생성 시드
    randomNumber = (rand() % 100) + 1;

    std::cout << "Start Up and Down Gaems" << std::endl;

    // 랜덤으로 생성된 숫자 출력
    std::cout << randomNumber << std::endl;
    std::cout << "" << std::endl;

    for (int i = 0; i <= 4; ++i)
        // i++와 ++i는 연산이 다 끝나면 +1이 된다는 점에서 같다
        // i++ : 연산 중에는 +1이 적용되지 않는다
        // ++i : 연산 중에 이미 +1이 적용된다
    {
        
        // for 반복문이 끝날 때 까지 계속 출력되는 부분
        int j;
        std::cout << "Input Number : ";
        std::cin >> j;
        std::cout << "[ Coins ] : " << 4 - i << std::endl;

        if (j > randomNumber)
        {
            std::cout << "result : [ DOWN ]" << std::endl;
            std::cout << "" << std::endl;
        }
        else if (j < randomNumber)
        {
            std::cout << "result : [ UP ]" << std::endl;
            std::cout << "" << std::endl;
        }

        // 사용자가 입력한 숫자가 정답일 경우 "미션클리어" 텍스트 출력 후 소스 종료
        if (j == randomNumber)
        {
            std::cout << "[ Mission clear ]" << std::endl;
            break;
        }

        // 총 5번의 기회동안 정답을 못 맞추면 "미션실패" 텍스트 출력 후 소스 종료
        else if (i == 4)
        {
            std::cout << "[ Mission failed ]" << std::endl;
            break;
        }
        if (j >= 100)
        {

            // 사용자가 100 이상의 숫자를 입력 할 경우 나오는 오류 부분
            std::cout << " [ 1 ~ 100까지 숫자만 입력해주세요 ] " << std::endl;
            std::cout << "" << std::endl;
            i--;
        }
    }
}
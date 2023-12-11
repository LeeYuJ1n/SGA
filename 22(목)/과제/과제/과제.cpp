// 2023년 6월 22일 목요일 과제
// 김유준

#include <iostream>
#include <Windows.h>
#include <stdlib.h>

int main()
{
    srand(GetTickCount64());

    int bingoScore = 0, bingo[5][5], inputNumber;

    // bingo[반복문 i][반복문 j]를 이용해 세로 5줄, 가로 5개 만들기
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            bingo[i][j] = i * 5 + j + 1;
        }
    }

    // 숫자를 랜덤으로 섞기
    for (int i = 0; i < 10000; ++i)
    {
        int x1 = rand() % 5;
        int x2 = rand() % 5;
        int x3 = rand() % 5;
        int x4 = rand() % 5;

        int tmp = bingo[x1][x2];
        bingo[x1][x2] = bingo[x3][x4];
        bingo[x3][x4] = tmp;
    }

    std::cout << "Bingo Games" << std::endl;

    while (bingoScore <= 3)
    {
        for (int i = 0; i < 5; ++i)
            // 변수 i는 0 ~ 4까지 반복할 때마다 1씩 증가(총 : 5번 반복)
        {
            for (int j = 0; j < 5; ++j)
                // 변수 j는 0 ~ 4까지 반복할 때마다 1씩 증가(총 : 5번 반복)
            {
                std::cout << "Test" << std::endl;
            }
        }

        // 변수 inputNumber에 값을 입력
        std::cout << "inputNumber : ";
        std::cin >> inputNumber;

        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (bingo[i][j] == inputNumber)
                {
                    bingo[i][j] = 0;
                }
            }
        }
    }
}
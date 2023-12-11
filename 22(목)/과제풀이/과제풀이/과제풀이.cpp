﻿#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    srand(GetTickCount64());

    // 1인용 빙고

    // 빙고에 필요한 것들 : 판, 숫자 25개, 내가 어디를 지우려고 하는가 (나중에는 내가 무슨 숫자를 지우려고 하는가)
    //                   : 내가 빙고를 몇 줄 만들었는가 + 빙고는 랜덤이다
    // -> 5x5 배열, 배열에 들어갈 숫자 모음(아마도 배열), 지우려는 위치 (가로, 세로), 빙고 줄 수

    // 변수로 만들어봅시다

    //숫자가 들어갈 데이터
    int rawData[25] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };

    //빙고 판
    int bingoBoard[5][5];

    //지우려는 위치(입력으로 받을 거라서 선언만)
    int x;
    int y;

    //빙고가 지금 몇 줄인가
    int bingoCount = 0; //시작할 때는 0

    //빙고도 게임이다 : 게임을 하고 있을 때와 끝났을 때가 구분되면 좋을 것
    //bool isPlaying = true;
    bool gameOver = false;

    //게임을 시작하기 전에 빙고 판부터 만듭시다

    for (int i = 0; i < 1000; i++) //1000번 돌아가는 for 반복문
    {
        int randomA = rand() % 25;
        int randomB = rand() % 25;

        int tmp = rawData[randomA];
        rawData[randomA] = rawData[randomB];
        rawData[randomB] = tmp;
    }
    //이 반복문이 끝나면 rawData 배열의 순서가 뒤죽박죽이 됩니다.

    //잘 섞인 rawData를 빙고 판에 넣읍시다.

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; ++j)
        {
            bingoBoard[i][j] = rawData[(i * 5) + j];
        }
    }


    while (true) //게임오버 되기 전까지는 무한하게 돌아갈 반복문 (게임)
    {
        //이 반복문이 끝나는 조건부터 지정
        //if (gameOver == true)
        if (gameOver) // 게임오버"라면"의 줄임 표현이고, if (gameOver == true)하고 같은 뜻이 됩니다.
        {
            break;
        }

        //빙고 게임이 진행되는 과정에서 필요한 안내를 합니다
        std::cout << std::endl;

        std::cout << "빙고 게임" << std::endl;
        //std::cout << "현재 빙고 줄 수 : " << bingoCount << std::endl;

        //std::cout << std::endl;

        //여기서 빙고 판을 보여주거나, 보여주기 전에 빙고 줄 수부터 제대로 계산할 수 있습니다.
        //빙고 줄 수를 계산을 먼저 하려고 할 경우...
        // 빙고 줄 수를 출력하는 것도 주석 다음으로 미뤄야 할 수 있습니다!

        //여기서는 빙고 줄 수 계산부터 해보는 쪽으로 코딩해보겠습니다.
        // = 빙고 판이 나올 때 이미 모든 계산이 끝난 상태


        //---지금부터 빙고 계산 시작---

        bingoCount = 0; //반복문이 돌아올 때마다 빙고 줄 수를 0부터 시작하게 만들 수 있습니다.
        //-매번 반복문이 돌 때마다 빙고 줄을 처음부터 하나씩 세는 겁니다
        //-연산은 느리지만, 대신 확실하게 하나씩 계산할 수 있습니다.

        // 각 줄마다 빙고가 되어 있는가? 를 판단하기
        // 빙고가 되려면? 칸이 먼저 지워져야 하는데, 칸이 지워진 건 어떻게 표현할 것인가?
        // 여기서는 칸이 지워지면 해당 배열의 값이 -1인 것으로 칩시다.

        //가로줄부터 빙고 여부를 판단해보기
        // 가로 맨 윗줄부터 아랫줄까지 쭉 돌아가면서 판단한다 -=> 반복문 사용
        for (int i = 0; i < 5; ++i)
        {
            //가로의 모든 줄이 -1인가?를 판단하는 방법
            // 가로가 같은 줄(세로로 i번째인 가로줄) 의 모든 칸이 -1이면
            if (bingoBoard[i][0] == -1 &&
                bingoBoard[i][1] == -1 &&
                bingoBoard[i][2] == -1 &&
                bingoBoard[i][3] == -1 &&
                bingoBoard[i][4] == -1)
            {
                // 코딩 팁. ;이 없으면 컴퓨터가 줄바꿈을 인식하지 못하는 점을 역이용해서
                // 엔터로만 줄바꿈을 하면 가로로 긴 코드를 줄을 나누어서 편하게 볼 수 있습니다.

                bingoCount++; //5개의 조건이 모두 참이면 빙고 하나 올리기
            }
        }

        //세로줄 (가로로 n번째인 줄) 빙고 여부 판단
        for (int i = 0; i < 5; ++i)
        {
            //세로줄의 모든 칸이 지워졌다고 판단할 수 있는 (위와는 또 조금 다른) 방법
            // 각 칸이 -1로 숫자가 되어 있다면, 이 칸을 모두 더하면 -5
            // 더불어서 하나라도 0이나 양의 숫자가 있다면 -5는 절대 나올 수 없다
            // 모든 칸이 지워져야만 나올 수 있는 수의 합계를 이용해서 조건문을 작성

            if (bingoBoard[0][i] +
                bingoBoard[1][i] +
                bingoBoard[2][i] +
                bingoBoard[3][i] +
                bingoBoard[4][i] == -5)
            {
                bingoCount++;
            }
        }

        // 대각선 확인하기
        // 1. 모든 빙고 판을 돌려서 행과 열의 숫자가 같은 칸끼리, 행과 열의 합이 4인 칸끼리 비교해서 판단하기
        // 2. 그냥 무식하게 각 경우의 수에 맞는 칸 5개만 곧바로 비교하기
        // -> 여기서는 2번 방법을 쓰겠습니다.

        // 대각선 1 (왼쪽 위에서 오른쪽 아래) 판단
        if (bingoBoard[0][0] == -1 &&
            bingoBoard[1][1] == -1 &&
            bingoBoard[2][2] == -1 &&
            bingoBoard[3][3] == -1 &&
            bingoBoard[4][4] == -1)
        {
            bingoCount++;
        }

        //대각선 2 (오른쪽 위에서 왼쪽 아래로) 판단
        if (bingoBoard[0][4] +
            bingoBoard[1][3] +
            bingoBoard[2][2] +
            bingoBoard[3][1] +
            bingoBoard[4][0] == -5)
        {
            bingoCount++;
        }

        //----여기서 빙고 줄 수 판단은 끝났습니다 ---

        // 계산이 끝난 빙고 줄 수를 밑에 보여줍니다.

        std::cout << "현재 빙고 줄 수 : " << bingoCount << std::endl;

        std::cout << std::endl;

        // 현재의 빙고 판을 보여줍니다.

        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (bingoBoard[i][j] < 10)
                {
                    std::cout << " "; //10보다 숫자가 작으면 공백 하나 더 넣기
                }

                if (bingoBoard[i][j] != -1)
                {
                    std::cout << bingoBoard[i][j] << "  ";
                    //숫자를 표시하고, 숫자 사이에 공백을 띄워서 알아보기 쉽게
                }
                else
                {
                    std::cout << "-" << "  "; //지워진 칸은 -1이라는 숫자 대신 기호가 나오도록
                }

            }
            //가로로 한 줄 표시한 다음 줄바꿈
            std::cout << std::endl;
        }

        //입력 부분 만들기
        std::cout << "지우려는 가로 칸을 입력해주세요." << std::endl;
        std::cout << "입력 : ";
        std::cin >> x; //x칸 입력

        std::cout << "지우려는 세로 칸을 입력해주세요." << std::endl;
        std::cout << "입력 : ";
        std::cin >> y; //y칸 입력

        //받은 입력으로 빙고 칸 지우기

        //...를 하기 전에, 입력이 뭔가 잘못된 경우 처리하는 부분부터
        // continue 사용

        if (x < 1 || x > 5 || y < 1 || y > 5)
        {
            std::cout << "입력이 잘못되었습니다." << std::endl;
            continue;
        }

        //if (y < 1 || y > 5)
        //{
            //std::cout << "입력이 잘못되었습니다." << std::endl;
            //continue;
        //}

        //입력이 제대로 됐으면 정말로 빙고 칸 지우기

        if (bingoBoard[y - 1][x - 1] != -1)
        {
            std::cout << "가로 " << x << "칸, 세로 " << y << "칸에 있는 숫자" << bingoBoard[y - 1][x - 1] << "를 지웠습니다." << std::endl;
            bingoBoard[y - 1][x - 1] = -1;

            //[y-1][x-1] : 배열은 가로줄이 먼저 나오고 세로줄이 나중에 나오므로 y가 왼쪽 []에 들어간다
            //y-1, x-1 : 입력값은 1~5인데 배열 순번은 0~4이므로 숫자를 1씩 줄여서 계산
            //문자 출력부터 하고 지우려는 이유 : 지워지기 이전의 원본 숫자 값을 쓰기 위해서
            // -> 지우기 수정부터 하고 출력을 하면 지운 칸의 숫자가 -1로만 나올 테니까...
        }

        //여기서 빙고 줄 수가 3줄이 되면 게임오버를 시키고, 반복문을 처음으로 돌아가도록 하겠습니다.

        if (bingoCount >= 3) //빙고가 중복이 되다 보면 한번에 2줄씩 올라가기도 하니까 (2줄에서 4줄로)
        {
            gameOver = true; //게임오버 확정
            continue; //처음으로 -> 게임오버이므로 거기서 break;
        }
    }

    //이 반복문이 끝났으면 게임이 다 끝난 겁니다.

    std::cout << "게임 끝. 고생하셨습니다!" << std::endl;
}
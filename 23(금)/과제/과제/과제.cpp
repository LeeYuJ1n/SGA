// 2023년 6월 25일 금요일 2인 빙고
// 김유준

#include <iostream>
#include <stdlib.h>
#include <windows.h>

void SinglePlayer();
void MultiPlayer();

int main()
{
    srand(GetTickCount64());

    int level_chooise = 0;
    bool gameModes = true;
    
    

    while (gameModes)
    {
        std::cout << "빙고게임" << std::endl;
        std::cout << "--------------------------------------------------------------" << std::endl;
        std::cout << "[ 1 ] 1인 빙고게임" << std::endl;
        std::cout << "[ 2 ] 2인 빙고게임" << std::endl;
        std::cout << "--------------------------------------------------------------" << std::endl;
        std::cout << "레벨 선택 : ";
        std::cin >> level_chooise;

        switch (level_chooise)
        {
        case 1:
            SinglePlayer();
            gameModes = false;
            break;

        case 2:
            MultiPlayer();
            gameModes = false;
            break;
        }
    }
}

void MultiPlayer()
{
    system("cls");

    // 숫자가 들어갈 데이터
    int rawData[25] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };

    // player1, player2이 지우려고 하는 숫자
    int player_1_number = 0;
    int player_2_number = 0;

    // 빙고판
    int player_1_bingoboard[5][5];
    int player_2_bingoboard[5][5];

    // player1과 player2의 빙고 카운트
    int player_1_bingoCount = 0, player_2_bingoCount = 0;

    bool gameOver = false; // 게임 오버 판단
    bool player_1_turn = true; // 순서 판단
    bool player_2_turn = true; // 순서 판단

   // 게임을 시작하기 전에 rawData 순서 무작위 섞기
    for (int i = 0; i < 1000; ++i)
    {
        int random_a = rand() % 25;
        int random_b = rand() % 25;

        int tmp = rawData[random_a];
        rawData[random_a] = rawData[random_b];
        rawData[random_b] = tmp;
    }
    
    // 섞인 rawData의 순서를 player1에 넣기
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; ++j)
        {
            player_1_bingoboard[i][j] = rawData[(i * 5) + j];
        }
    }

    // 게임을 시작하기 전에 rawData 순서 무작위 섞기
    for (int i = 0; i < 1000; ++i)
    {
        int random_a = rand() % 25;
        int random_b = rand() % 25;

        int tmp = rawData[random_a];
        rawData[random_a] = rawData[random_b];
        rawData[random_b] = tmp;
    }

    // 섞인 rawData의 순서를 player2에 넣기
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; ++j)
        {
            player_2_bingoboard[i][j] = rawData[(i * 5) + j];
        }
    }

    std::cout << std::endl;

    while (true)
    {
        if (gameOver)
        {
            break;
        }

        std::cout << std::endl;

        // 빙고 계산
        player_1_bingoCount = 0, player_2_bingoCount = 0;

        // 가로줄 계산
        for (int i = 0; i < 5; ++i)
        {
            // player1의 가로줄 빙고 검사
            if (player_1_bingoboard[i][0] == -1 &&
                player_1_bingoboard[i][1] == -1 &&
                player_1_bingoboard[i][2] == -1 &&
                player_1_bingoboard[i][3] == -1 &&
                player_1_bingoboard[i][4] == -1)
            {
                player_1_bingoCount++; // -5가 되면 player1의 빙고 점수를 1 증가
            }

            // player2의 가로줄 빙고 검사
            if (player_2_bingoboard[i][0] == -1 &&
                player_2_bingoboard[i][1] == -1 &&
                player_2_bingoboard[i][2] == -1 &&
                player_2_bingoboard[i][3] == -1 &&
                player_2_bingoboard[i][4] == -1)
            {
                player_2_bingoCount++; // -5가 되면 player2의 빙고 점수를 1 증가
            }
        }

        for (int i = 0; i < 5; ++i)
        {
            // player1의 세로줄 빙고 검사
            if (player_1_bingoboard[0][i] == -1 &&
                player_1_bingoboard[1][i] == -1 &&
                player_1_bingoboard[2][i] == -1 &&
                player_1_bingoboard[3][i] == -1 &&
                player_1_bingoboard[4][i] == -1)
            {
                player_1_bingoCount++;
            }
            // player2의 세로줄 빙고 검사
            if (player_2_bingoboard[0][i] == -1 &&
                player_2_bingoboard[1][i] == -1 &&
                player_2_bingoboard[2][i] == -1 &&
                player_2_bingoboard[3][i] == -1 &&
                player_2_bingoboard[4][i] == -1)
            {
                player_2_bingoCount++;
            }
        }

        for (int i = 0; i < 5; ++i)
        {
            // player1의 대각선 빙고 검사
            if (player_1_bingoboard[0][0] == -1 &&
                player_1_bingoboard[1][1] == -1 &&
                player_1_bingoboard[2][2] == -1 &&
                player_1_bingoboard[3][3] == -1 &&
                player_1_bingoboard[4][4] == -1)
            {
                player_1_bingoCount++;
            }

            // player2의 대각선 빙고 검사
            if (player_2_bingoboard[0][0] == -1 &&
                player_2_bingoboard[1][1] == -1 &&
                player_2_bingoboard[2][2] == -1 &&
                player_2_bingoboard[3][3] == -1 &&
                player_2_bingoboard[4][4] == -1)
            {
                player_2_bingoCount++;
            }
        }

        // player1의 빙고 현황
        std::cout << "player1의 빙고 줄 수 : " << player_1_bingoCount << std::endl;
        std::cout << std::endl;

        // 현재 빙고판 출력
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (player_1_bingoboard[i][j] < 10)
                {
                    // 10보다 숫자가 작으면 공백 하나 더 넣기
                    std::cout << " ";
                }

                if (player_1_bingoboard[i][j] != -1)
                {
                    // 숫자를 표시하고, 숫자 사이에 공백을 띄워서 알아보기 쉽게
                    std::cout << player_1_bingoboard[i][j] << " ";
                }
                else
                {
                    // 지워진 칸은 -1이라는 숫자 대신에 기호로 표시
                    std::cout << "-" << " ";
                }
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;

        // player2의 빙고 현황
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (player_2_bingoboard[i][j] < 10)
                {
                    std::cout << " "; // 10보다 숫자가 작으면 공백 하나 더 넣기
                }

                if (player_2_bingoboard[i][j] != -1)
                {
                    std::cout << player_2_bingoboard[i][j] << " "; // 숫자사이에 공백을 띄워서 정렬
                }
                else
                {
                    std::cout << "-" << " "; // 지워진 칸은 숫자 대신에  기호로 표시
                }
            }

            std::cout << std::endl;
        }

        if (player_1_bingoCount >= 5 || player_2_bingoCount >= 5)
        {
            gameOver = true;
            continue;
        }

        if (player_1_turn)
        {
            std::cout << "빙고판에서 지우고 싶은 숫자를 입력해주세요" << std::endl;
            std::cout << "입력 : " << std::endl;
            std::cin >> player_1_number;

            if (player_1_number < 1 || player_1_number > 25)
            {
                std::cout << "잘못된 입력입니다" << std::endl;
                continue;
            }

            player_1_turn = false;
        }

        else if (!player_1_turn)
        {
            // player2가 입력합니다
            std::cout << "빙고판에서 지우고 싶은 숫자를 입력해주세요" << std::endl;
            std::cout << "입력 : " << std::endl;
            std::cin >> player_2_number;

            if (player_2_number < 1 || player_2_number > 25)
            {
                std::cout << "잘못된 입력입니다." << std::endl;
                continue;
            }

            player_1_turn = true;
        }

        std::cout << std::endl;
        
        // 입력에 맞는 숫자 지우기
        std::cout << "player1의 빙고판" << std::endl;
        std::cout << std::endl;

        int player_1_x, player_1_y;

        for (player_1_y = 0; player_1_y < 5; player_1_y++)
        {
            for (player_1_x = 0; player_1_x < 5; player_1_x++)
            {
                if (player_1_bingoboard[player_1_y][player_1_x] == player_1_number)
                {
                    std::cout << "가로 " << player_1_x + 1 << "칸, 세로 " << player_1_y + 1 << "칸에 있는 숫자" << player_1_bingoboard[player_1_y][player_1_x] << "를 지웠습니다." << std::endl;
                    player_1_bingoboard[player_1_y][player_1_x] = -1;
                }
            }
        }

        for (player_1_y = 0; player_1_y < 5; player_1_y++)
        {
            for (player_1_x = 0; player_1_x < 5; player_1_x++)
            {
                if (player_1_bingoboard[player_1_y][player_1_x] == player_2_number)
                {
                    std::cout << "가로 " << player_1_x + 1 << "칸, 세로 " << player_1_y + 1 << "칸에 있는 숫자" << player_1_bingoboard[player_1_y][player_1_x] << "를 지웠습니다." << std::endl;
                    player_1_bingoboard[player_1_y][player_1_x] = -1;
                }
            }
        }

        std::cout << "player2의 빙고판" << std::endl;
        std::cout << std::endl;

        int player_2_x, player_2_y;

        for (player_2_y = 0; player_2_y < 5; player_2_y++)
        {
            for (player_2_x = 0; player_2_x < 5; player_2_x++)
            {
                if (player_2_bingoboard[player_2_y][player_2_x] == player_1_number)
                {
                    std::cout << "가로 " << player_2_x + 1 << "칸, 세로 " << player_2_y + 1 << "칸에 있는 숫자" << player_2_bingoboard[player_2_y][player_2_x] << "를 지웠습니다." << std::endl;
                    player_2_bingoboard[player_2_y][player_2_x] = -1;
                }
            }
        }

        for (player_2_y = 0; player_2_y < 5; player_2_y++)
        {
            for (player_2_x = 0; player_2_x < 5; player_2_x++)
            {
                if (player_2_bingoboard[player_2_y][player_2_x] == player_2_number)
                {
                    std::cout << "가로 " << player_2_x + 1 << "칸, 세로 " << player_2_y + 1 << "칸에 있는 숫자" << player_2_bingoboard[player_2_y][player_2_x] << "를 지웠습니다." << std::endl;
                    player_2_bingoboard[player_2_y][player_2_x] = -1;
                }
            }
        }
    }

    if (player_1_bingoCount >= 5 && player_2_bingoCount >= 5)
    {
        std::cout << "무승부" << std::endl;
    }
    else if (player_1_bingoCount >= 5)
    {
        std::cout << "Player1 승리" << std::endl;
    }
    else if (player_2_bingoCount >= 5)
    {
        std::cout << "Player2 승리" << std::endl;
    }
}

void SinglePlayer()
{
    system("cls");

    // 숫자가 들어갈 데이터
    int rawData[25] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };

    // 빙고판
    int bingoBoard[5][5];

    // 지우려는 위치
    int x, y;

    // 빙고가 지금 몇 줄인지 판단
    int bingoCount = 0;

    // 게임이 끝났는지 구분
    int gameOver = false;

    // 게임을 시작하기 전에 빙고 판 만들기
    for (int i = 0; i < 1000; i++)
    {
        int randomA = rand() % 25;
        int randomB = rand() % 25;

        // 숫자 랜덤으로 섞기
        int tmp = rawData[randomA];
        rawData[randomA] = rawData[randomB];
        rawData[randomB] = tmp;

        // 이 반복문이 끝나면 rawData 배열의 순서가 뒤죽박죽이 됩니다
    }

    // rawData를 빙고판에 넣기
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; ++j)
        {
            bingoBoard[i][j] = rawData[(i * 5) + j];
        }
    }

    // Player 1
    while (true)
    {
        if (gameOver)
        {
            break;
        }

        std::cout << std::endl;
        std::cout << "빙고 게임" << std::endl;

        // 빙고 계산 시작
        bingoCount = 0;

        for (int i = 0; i < 5; ++i)
        {
            // 가로의 모든 줄이 -1인가?를 판단하는 방법
            // 가로가 같은 줄(세로로 i번째인 가로줄)의 모든 칸이 -1이면
            if (bingoBoard[i][0] == -1 &&
                bingoBoard[i][1] == -1 &&
                bingoBoard[i][2] == -1 &&
                bingoBoard[i][3] == -1 &&
                bingoBoard[i][4] == -1)
            {
                bingoCount++;
            }
        }

        // 세로줄의 모든 칸이 지워졌다고 판단할 수 있는 (위와는 또 조금 다른 방법)
        // 각 칸이 -1로 숫자가 되어, 이 칸을 모두 더하면 -5
        for (int i = 0; i < 5; ++i)
        {
            if (bingoBoard[0][i] +
                bingoBoard[1][i] +
                bingoBoard[2][i] +
                bingoBoard[3][i] +
                bingoBoard[4][i] == -5)
            {
                bingoCount++;
            }
        }

        if (bingoBoard[0][4] +
            bingoBoard[1][3] +
            bingoBoard[2][2] +
            bingoBoard[3][1] +
            bingoBoard[4][0] == -5)
        {
            bingoCount++;
        }

        // 빙고 계산 끝

        // 계산된 빙고를 화면에 출력

        std::cout << "현재 빙고 줄 수 : " << bingoCount << std::endl;

        std::cout << std::endl;

        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (bingoBoard[i][j] < 10)
                {
                    std::cout << " "; // 가로 세로 줄에 있는 숫자가 10보다 작으면 공배가 하나 넣기
                }

                if (bingoBoard[i][j] != -1)
                {
                    std::cout << bingoBoard[i][j] << " ";
                }
                else
                {
                    std::cout << "-" << " "; // 지워진 칸은 -1이라는 숫자 대신 기호가 나오도록
                }
            }

            // 가로로 한 줄 표시한 다음 줄바꿈
            std::cout << std::endl;
        }

        // 입력 부분 만들기
        std::cout << "지우려는 가로 칸을 입력해주세요" << std::endl;
        std::cout << "입력 :";
        std::cin >> x;

        std::cout << "지우려는 세로 칸을 입력해주세요" << std::endl;
        std::cout << "입력 : " << std::endl;
        std::cin >> y;

        if (x < 1 || x > 5 || y < 1 || y > 5)
        {
            std::cout << "잘못입력되었습니다" << std::endl;
            continue;
        }

        if (bingoBoard[y - 1][x - 1] = -1)
        {
            std::cout << "가로 " << x << "칸, 세로 " << y << "칸에 있는 숫자" << bingoBoard[y - 1][x - 1] << "를 지웠습니다." << std::endl;
            bingoBoard[y - 1][x - 1] = -1;
        }

        Sleep(2000);
        system("cls");

        if (bingoCount >= 3)
        {
            gameOver = true;
            continue;
        }
    }
}
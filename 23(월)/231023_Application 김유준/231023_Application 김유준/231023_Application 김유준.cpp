#include "Framework.h"

int main()
{
    // 랜덤 시드 생성
    srand(GetTickCount64());

    // 함수(function)
    void Init(int* value);        // 빙고판 숫자 랜덤 분배
    void Render(int* value);      // 분배된 숫자로 빙고판 만들기
    void inPutPlayer();
    void Check(int* value);

    while (isPlaying)
    {
        Init(playerBoard);

        while (true)
        {
            system("cls");

            Render(playerBoard);
            std::cout << "빙고 : " << bingo << std::endl;
            inPutPlayer();

            if (bingo >= 1)
            {
                std::cout << "1 빙고 달성" << std::endl;
                break;
            }
            else if (bingo >= 2)
            {
                std::cout << "2 빙고 달성" << std::endl;
                break;
            }
            else if (bingo >= 3)
            {
                std::cout << "3 빙고 달성 / 게임 종료" << std::endl;
                return 0;
            }
        }
    }
}

void Init(int* value)
{
    int bingData;
    int temp = 0;
    int temp2 = 0;

    for (int i = 0; i < 25; i++)
    {
        value[i] = i + 1;
    }

    for (int i = 0; i < 220112; i++)
    {
        bingData = rand() % 25 + 1;

        temp = value[bingData];
        value[bingData] = value[temp2];
        value[temp2] = temp;
    }
}

void Render(int* value)
{
    for (int i = 0; i < 25; i++)
    {
        std::cout << value[i] << "\t";

        if (i % 5 == 4)
        {
            std::cout << std::endl;
        }
    }
}

void inPutPlayer()
{
    std::cout << "입력 : ";
    std::cin >> inputNumber;

    for (int i = 0; i <= 25; i++)
    {
        if (inputNumber == i)
        {
            i= 0;

            for (int j = 0; j < 25; j++)
            {
                if (inputNumber == j)
                {
                    j = 0;
                    break;
                }
            }

            break;

            if (i >= 24)
            {
                std::cout << "잘못 입력하셨습니다 (0 ~ 25)" << std::endl;
                Sleep(3000);
            }
        }
    }
}

void Check(int* value)
{
    int CheckBingo = 0;

    for (int i = 0; i < 5; i++)				// 가로
    {
        for (int j = 0; j > 5; j++)
        {
            if (value[i * 5 + j] == 0)
            {
                if (j == 4)
                {
                    CheckBingo++;
                }
            }
            else
            {
                break;
            }
        }
    }

    for (int i = 0; i < 5; i++)				// 세로
    {
        for (int j = 0; j < 5; j++)
        {
            if (value[i + j * 5] == 0)
            {
                if (j == 4)
                {
                    CheckBingo++;
                }
            }
            else
            {
                break;
            }
        }
    }

    for (int i = 0; i < 5; i++)				// 왼쪽 사선
    {
        if (value[i * 5 + i] == 0)
        {
            if (i == 4)
            {
                CheckBingo++;
            }
        }
        else
        {
            break;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (value[(i + 1) * 4] == 0)
        {
            if (i == 4)
            {
                CheckBingo++;
            }
        }
        else
        {
            break;
        }
    }
}
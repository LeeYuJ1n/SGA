#include <iostream>
#include <Windows.h>
#include <conio.h>

// 전역변수
int playerInput = 0;
int douDim[5][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };

// 함수
void games()
{
    // 지역변수
    int x = 0;
    int y = 0;
    int player = 0xB098; // 유니코드 "나"
    bool loop = true;
    douDim[x][y] = player;

    // 2차원 배열 출력
    while (loop)
    {
        std::cout << "간단한 게임" << std::endl;

        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (douDim[i][j] == player)
                {
                    // 커서 위치와 플레이어 위치가 같으면 "나"라는 글자로 바뀌게 하기
                    std::cout << "나" << " " << "\t";
                }
                else
                {
                    // 배열 출력
                    std::cout << douDim[i][j] << " " << "\t";
                }
            }
            std::cout << std::endl; // j가 5번 반복할 때마다 i가 +1 증가
        }

        int input = _getch();

        switch (input)
        {
        case 'w':
            douDim[x][y] = player;
            --x; // 위쪽으로 이동
            douDim[x][y] = player;
            break;

        case 'a':
            douDim[x][y] = player;
            --y;
            douDim[x][y] = player;
            break;

        case 's':
            douDim[x][y] = player;
            ++x;
            douDim[x][y] = player;
            break;

        case 'd':
            douDim[x][y] = player;
            ++y;
            douDim[x][y] = player;
            break;

        case 'o':
            std::cout << "프로그램을 종료합니다" << std::endl;
            loop = false;
            break;

        default:
            std::cout << std::endl;
            std::cout << "잘못된 키를 입력하셨습니다" << std::endl;
            break;
        }
        system("cls");
        continue;
    }
    return;
}

int main()
{
    games();
}
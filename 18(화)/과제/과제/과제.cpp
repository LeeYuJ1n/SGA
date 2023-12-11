#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include "Character.h" // 캐릭터
#include "Item.h" // 아이템

int main()
{
    srand(GetTickCount64());
    int input;
    input = rand() % 2 + 1;

    Character* artist = new Character(1, 50, 1000, 100, 0);
    Character* meteorologist = new Character(2, 50, 1000, 110, 0);

    while (true)
    {
        artist->PrintStat();
        meteorologist->PrintStat();

        Sleep(3000);

        if (input == 1)
        {
            std::cout << std::endl;
            std::cout << "도화가 순서" << std::endl;
            std::cout << std::endl;
            std::cout << "메뉴 선택" << std::endl;
            std::cout << "[ 1 ] 아이템 사용 / [ 2 ] 공격하기" << std::endl;
            std::cout << "입력 : ";
            std::cin >> input;

            switch (input)
            {
            case 1:
                void SpecUp();
                break;

            case 2:

                break;
            }
        }
        else if (input == 2)
        {
            std::cout << std::endl;
            std::cout << "기상술사 순서" << std::endl;
            std::cout << std::endl;
            std::cout << "메뉴 선택" << std::endl;
            std::cout << "[ 1 ] 아이템 사용 / [ 2 ] 공격하기" << std::endl;
            std::cout << "입력 : ";
            std::cin >> input;

            switch (input)
            {
            case 1:
                
                break;
            }
        }
    }
};
#include <iostream>
#include <windows.h>
#include "Class.h"

int main()
{
    // 캐릭터 1 : 체력, 공격력
    Class character1(100, 15);

    // 캐릭터 2 : 체력, 공격력
    Class character2(100, 10);

    character1.print();
    character2.print();

    while (true)
    {
        system("cls");

        character1.attack
    }
}
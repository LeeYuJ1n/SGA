#include <iostream>
#include <Windows.h>
#include "Class.h"

void Class::print()
{
    // 캐릭터1 정보
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "캐릭터 이름 : 도화가" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "아이디 : " << id() << std::endl;
    std::cout << "체력 : " << strength() << std::endl;
    std::cout << "공격력 : 1 ~ 10" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;

    // 알아보기 쉽게하기 위한 줄바꿈
    std::cout << std::endl;

    // 캐릭터2 정보
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "캐릭터 이름 : 기상술사" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "아이디 : " << id2() << std::endl;
    std::cout << "체력 : " << strength2() << std::endl;
    std::cout << "공격력 : 1 ~ 10" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
}

void Class::pvpsystem()
{
    bool loop = true;

    srand(GetTickCount64());

    system("cls");

    std::cout << "pvp를 시작합니다" << std::endl;
    std::cout << std::endl;
    std::cout << "전투는 자동으로 진행됩니다" << std::endl;

    while (loop)
    {
        chara.attack = rand() % 10 + 1;
        chara2.attack = rand() % 10 + 1;

        if (chara.strength > 0 && chara2.strength > 0)
        {
            Sleep(1000);
            system("cls");

            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "도화가(공격) → 기상술사(피해)" << std::endl;
        
            // 데미지 계산
            chara2.strength -= chara.attack;

            std::cout << "도화가 체력 : " << chara.strength << std::endl;
            std::cout << "기상술사 체력 : " << chara2.strength << "(-" << chara.attack << ")" << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;

            Sleep(1000);

            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "기상술사(공격) → 도화가(피해)" << std::endl;
            
            // 데미지 계산
            chara.strength -= chara2.attack;

            std::cout << "기상술사 체력 : " << chara2.strength << std::endl;
            std::cout << "도화가 체력 : " << chara.strength << "(-" << chara2.attack << ")" << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;
        }
        if(chara.strength <= 0)
        {
            std::cout << "도화가 패배" << std::endl;
            loop = false;
        }
        else if (chara2.strength <= 0)
        {
            std::cout << "기상술사 패배" << std::endl;
            loop = false;
        }
    }
}
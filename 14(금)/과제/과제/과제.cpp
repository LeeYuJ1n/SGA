#include <iostream>
#include <Windows.h>
#include "Character.h"
#include "Character_Group.h"
#include "Occupation.h"

int main()
{
    std::cout << "2023년 7월 14일 과제" << std::endl;
    Sleep(3000);
    system("cls");

    Character* avatar1 = new Character(1, 50, 1000, 100);
    Character* avatar2 = new Character(2, 50, 1000, 200);

    std::cout << "Avatar1 정보:" << std::endl;
    std::cout << "아이디: " << avatar1->GetId() << std::endl;
    std::cout << "레벨: " << avatar1->GetLevel() << std::endl;
    std::cout << "체력: " << avatar1->GetStrength() << std::endl;
    std::cout << "공격력: " << avatar1->GetPower() << std::endl;

    std::cout << std::endl;

    std::cout << "Avatar2 정보:" << std::endl;
    std::cout << "아이디: " << avatar2->GetId() << std::endl;
    std::cout << "레벨: " << avatar2->GetLevel() << std::endl;
    std::cout << "체력: " << avatar2->GetStrength() << std::endl;
    std::cout << "공격력: " << avatar2->GetPower() << std::endl;

    delete avatar1;
    delete avatar2;

    return 0;
}
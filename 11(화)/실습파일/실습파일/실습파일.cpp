#include <iostream>
#include <Windows.h>
#include "header1.h"

int main()
{
    std::cout << "과제" << std::endl;

    Sleep(3000);
    system("cls");

    // header1.h → Print() 함수 호출
    Print();

    return 0;
}
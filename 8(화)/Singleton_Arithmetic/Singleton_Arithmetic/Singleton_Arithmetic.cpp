#include <iostream>
#include <Windows.h>

// 헤더
#include "Singleton_Class.h"  // Singleton

// 매크로
#define SINGLETON Singleton_Class::Get()           // Singleton_Class
#define ARITHMETIC Arithmetic_Class::Get()         // Arithmetic_Class

using namespace std;

int main()
{
    // 프로젝트 작성 날짜 및 설명
    cout << "2023년 8월 8일 화요일" << endl;
    cout << "Singleton 복습 과제" << endl;

    Sleep(5000); // 딜레이 5초

    cout << endl;
    cout << "연산 시작" << endl;

    // Arithmetic_Class → Singleton_Class → main
    Sleep(3000);                               // 딜레이 3초

    cout << endl;
    SINGLETON->ARITHMETIC->Add(5, 5);          // 더하기
    cout << endl;

    Sleep(3000);                               // 딜레이 3초

    SINGLETON->ARITHMETIC->Sub(5, 5);          // 빼기
    cout << endl;

    Sleep(3000);                               // 딜레이 3초

    SINGLETON->ARITHMETIC->Mult(5, 5);         // 곱하기
    cout << endl;

    Sleep(3000);                               // 딜레이 3초

    SINGLETON->ARITHMETIC->Div(5, 5);          // 나누기
    cout << endl;

    Sleep(3000);                               // 딜레이 3초

    SINGLETON->ARITHMETIC->Remainder(5, 5);    // 나머지
}
#include <iostream>
#include "Data.h"
#include "Add.h"
#include "Sub.h"
#include "Mult.h"
#include "Div.h"

int main()
{
	int input = 0;
	Data* CalcAdd = new Add();
	Data* CalcSub = new Sub();
	Data* CalcMult = new Mult();
	Data* CalcDiv = new Div();

	std::cout << "계산 방식 선택" << std::endl;
	std::cout << "첫 번째 숫자 : 10 / 두 번째 숫자 5" << std::endl;
	std::cout << std::endl;

	CalcAdd = CalcAdd;
	CalcAdd->Calcs(); // 더하기 계산

	CalcAdd = CalcSub; // 빼기로 바꾸기
	CalcAdd->Calcs(); // 빼기 계산

	CalcAdd = CalcMult; // 곱하기로 바꾸기
	CalcAdd->Calcs(); // 곱하기 계산

	CalcAdd = CalcDiv; // 나누기로 바꾸기
	CalcAdd->Calcs(); // 나누기 계산
}
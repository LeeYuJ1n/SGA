#pragma once

#include <iostream>
#include <Windows.h>

void arrPrint()
{
	// 1차원 배열
	int arr1[5] = { 1, 2, 3, 4, 5 };
	int arr2[3] = { 6, 7, 8 };
	int arr3[4] = { 9, 10, 11, 12 };

	// arr1, arr2, arr3 배열을 포인터를 이용해 하나로 묶기
	int* arrResult[3] = { arr1, arr2, arr3 };
	
	// arr1
	std::cout << arrResult[0][0] << " ";
	std::cout << arrResult[0][1] << " ";
	std::cout << arrResult[0][2] << " ";
	std::cout << arrResult[0][3] << " ";
	std::cout << arrResult[0][4] << " " << std::endl;

	// arr2
	std::cout << arrResult[1][0] << " ";
	std::cout << arrResult[1][1] << " ";
	std::cout << arrResult[1][2] << std::endl;

	// arr3
	std::cout << arrResult[2][0] << " ";
	std::cout << arrResult[2][1] << " ";
	std::cout << arrResult[2][2] << " ";
	std::cout << arrResult[2][3] << std::endl;
}
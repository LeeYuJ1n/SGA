#pragma once

#pragma once
// 위에 있는 gragma once 줄은 필수도 아닌데 너무너무 유용하고 좋아서 자동완성으로 들어간 것
// 그러므로 웬만하면 이 줄을 지우지 맙시다

// gragma once : 헤더와 cpp파일, 혹은 여러 개의 헤더에서 똑같은 #include가 작성됐을 때,
// 중복된 코드를 실행하지 않는 명령어(#include <iostream> 코드가 두 번 나와도 한 번만 실행)

#include <iostream> // #gragma once 코드를 믿고 아무데서나 불러도 OK

// 어제 과제 내용 : 배열로 배열을 다시 만들어서 출력하기(1중배열 작성 후 배열들로 또 배열 만들기)

// 배열 만들기(안에 들어가는 숫ㅈ는 모두 임의로)
int arr1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 99 };
int arr2[3] = { 11, 22, 33 };
int arr3[4] = { 1111, 2222, 3333, 4444 };
int arr4[7] = { 12345, 67890, 13579, 24680, 98765, 54321, 12480 };
int arr5[2] = { 44, 55 };

// 배열을 원소로 하는 새 배열 만들기
//  배열의 이름(=포인터)이 원소인 배열이니까 int*의 배열
int* aarr[5] = { arr1, arr2, arr3, arr4, arr5 };

int arrA[5] = {10, 3, 4, 7, 2};

// 위 배열도 포인터이고, int의 포인터의 포인터니까 이중 포인터
// 동시에 배열의 배열이므로 이중 배열

void PrintArray()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < arrA[i]; ++j)
		{
			std::cout << aarr[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
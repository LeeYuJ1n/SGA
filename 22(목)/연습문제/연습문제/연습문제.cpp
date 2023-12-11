// 2023년 6월 22일 목요일 연습문제
// 오늘의 연습 : 1부터 25까지 (5x5) 숫자를 2중 배열로 할당하기
// → 할당된 2중 배열을 가로 5개, 세로 5개로 출력
// → 출력까지 가능하면 랜덤으로 숫자 순서로 바꿔봅시다

#include <iostream>
#include <windows.h>
#include <stdlib.h>

int main()
{
    // arr1[12] : 1부터 12까지의 수를 배열로 선언
    int arr1[25] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 ,25 };

    // 숫자를 출력하기 위해 변수 선언
    int printData[5][5];

    // 원시 데이터(arr1)의 내용을(순서를) 랜덤으로 바꾸기
    srand(GetTickCount64());

    for (int i = 0; i < 5; ++i)
    {
        // 랜덤 숫자를 저장하기 위한 변수 선언
        int x1 = rand() % 25;
        int y1 = rand() % 25;

        // 랜덤 숫자를 순번으로 하는 두 원소의 위치 바꾸기
        int tmp = arr1[x1];
        arr1[x1] = arr1[y1];
        arr1[y1] = tmp;
    }

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            printData[i][j] = arr1[(i * 5) + j];
            std::cout << printData[i][j] << std::endl;
        }
    }
}
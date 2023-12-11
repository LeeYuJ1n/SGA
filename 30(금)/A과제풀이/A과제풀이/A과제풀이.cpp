#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    srand(GetTickCount64());
    // 배열 다시 정렬하기 : 자동 정렬 방식

    // 배열 준비
    int arrayToSort[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 배열 섞기
    for (int i = 0; i < 1000; ++i)
    {
        int ranA = rand() % 10;
        int ranB = rand() % 10;

        int tmp = arrayToSort[ranA];
        arrayToSort[ranA] = arrayToSort[ranB];
        arrayToSort[ranA] = tmp;
    }

    // 정렬의 원리
    // 1. 칸 하나(왼쪽부터 쭉) 고르기
    // 2. 자기 옆 칸과 비교하기
    // 3. 자기가 더 크면 옆칸과 위치 바꾸기 : 여기까지 1세트
    // 4. 1세트 다 돌아간 다음, 다시 처음부터 가장 작아야 하는(왼쪽) 칸부터 검사
    // 5. 세트 횟수 : 배열 크기만큼(1세트 돌아갈 때마다 1칸이 자기 자리 찾아가니까)

    // 배열 정렬
    for (int i = 0; i < 10; ++i) // 총 검사 세트 횟수
    {
        // 반복문 하나 더 준비
        for (int j = 0; j < (10 - 1); ++j) // 한 세트당 검사하는 칸 수(마지막 칸은 옆켠이 없으므로 생략)
        {
            if (arrayToSort[j] > arrayToSort[j + 1])
            {
                int tmp = arrayToSort[j];
                arrayToSort[j] = arrayToSort[j + 1];
                arrayToSort[j + 1] = tmp;
            }
        }
    }

    // 출력
    for (int i = 0; i < 10; ++i)
    {
        std::cout << arrayToSort[i] << std::endl;
    }
}
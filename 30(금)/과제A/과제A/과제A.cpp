#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    // 랜덤 시드
    srand(GetTickCount64());

    // 필요한 변수 생성
    int inputSelect = 0;
    bool loop = true;

    // 배열 선언
    int Dimension_Array_1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 변수 선언
    int tmp = 0;

    for (int i = 0; i < 1000; ++i)
    {
        int a = rand() % 10 + 1;
        int b = rand() % 10 + 1;

        tmp = Dimension_Array_1[a];
        Dimension_Array_1[a] = Dimension_Array_1[b];
        Dimension_Array_1[b] = tmp;
        break;
    }

    // 섞인 배열 출력
    std::cout << std::endl;
    std::cout << "섞인 배열 : ";

    for (int i = 0; i < 10; i++)
    {
        std::cout << Dimension_Array_1[i] << " ";
    }

    // 오름차순 정렬
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (Dimension_Array_1[i] < Dimension_Array_1[j])
            {
                int tmp = Dimension_Array_1[i];
                Dimension_Array_1[i] = Dimension_Array_1[j];
                Dimension_Array_1[j] = tmp;
            }
        }
    }

    // 오름차순 정렬 후 출력
    std::cout << std::endl;
    std::cout << "오름차순 : ";
    
    for (int i = 0; i < 10; i++)
    {
        std::cout << Dimension_Array_1[i] << " ";
    }

    std::cout << std::endl;

    // -------------------------------------------------

    // 내림차순
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (Dimension_Array_1[i] > Dimension_Array_1[j])
            {
                int tmp = Dimension_Array_1[i];
                Dimension_Array_1[i] = Dimension_Array_1[j];
                Dimension_Array_1[j] = tmp;
            }
        }
    }

    // 내림차순 출력
    std::cout << "내림차순 : ";

    for (int i = 0; i < 10; i++)
    {
        std::cout << Dimension_Array_1[i] << " ";
    }

    std::cout << std::endl;

    // ---------------------------------------------------
}
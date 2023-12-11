#include "Header.h"

int main()
{
    // PrintDoubleArrays(); // 출력 호출만 해주고 끝!
    PrintDAwithRecord(); // 기록에 의한 이중 배열 출력
}

// 이중 배열을 출력하기 위한 함수(메타데이터를 활용한 편법 스타일로)
void PrintDAwithRecord()
{
    for (int i = 0; i < 5; ++i) // 큰 배열 반복
    {
        for (int j = 0; j < lengthofArrays[i]; ++j) // 작은 배열...인데 배열 길이를 기록한 배열의 각 값을 기준으로
        {
            std::cout << aarr[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// 이중 배열을 출력하기 위한 함수(이쪽이 진짜)
void PrintDoubleArrays()
{
    // 배열이니까 반복문으로 출력합시다

    // 이 반복문은 잘못된 코드입니다. 작은 배열의 크기를 무시했기 때문에
    /*
    for (int i = 0; i < 5; ++i) // 큰 배열의 크기에 맞춘 반복문(aarr)
    {
        for (int j = 0; j < 10; ++j) // 작은 배열 크기에 맞춘 반복문(arr1 ~ arr5)
        {
            std::cout << aarr[i][j] << "\t"; // 각 원소의 값을 보여주고 탭표시로 자리 띄우기
        }
        // 작은 반복문 한 번 돌면 줄바꿈
        std::cout << std::endl;
    }
    */

    for (int i = 0; i < 5; ++i) // 큰 배열의 크기에 맞춘 반복문(aarr)
    {
        switch (i)
        {
        case 0:
            // 10개짜리 배열
            for (int j = 0; j < 10; ++j) // 작은 배열 크기에 맞춘 반복문(arr1 ~ arr5)
            {
                std::cout << aarr[i][j] << "\t"; // 각 원소의 값을 보여주고 탭표시로 자리 띄우기
            }
            break;

        case 1:
            // 3개짜리 배열
            for (int j = 0; j < 3; ++j) // 작은 배열 크기에 맞춘 반복문(arr1 ~ arr5)
            {
                std::cout << aarr[i][j] << "\t"; // 각 원소의 값을 보여주고 탭표시로 자리 띄우기
            }
            break;

        case 2:
            // 4개짜리 배열
            for (int j = 0; j < 4; ++j) // 작은 배열 크기에 맞춘 반복문(arr1 ~ arr5)
            {
                std::cout << aarr[i][j] << "\t"; // 각 원소의 값을 보여주고 탭표시로 자리 띄우기
            }
            break;

        case 3:
            // 7개짜리 배열
            for (int j = 0; j < 7; ++j) // 작은 배열 크기에 맞춘 반복문(arr1 ~ arr5)
            {
                std::cout << aarr[i][j] << "\t"; // 각 원소의 값을 보여주고 탭표시로 자리 띄우기
            }
            break;

        case 4:
            // 2개짜리 배열
            for (int j = 0; j < 2; ++j) // 작은 배열 크기에 맞춘 반복문(arr1 ~ arr5)
            {
                std::cout << aarr[i][j] << "\t"; // 각 원소의 값을 보여주고 탭표시로 자리 띄우기
            }
            break;
        }
        // 작은 반복문 한 번 돌면 줄바꿈
        std::cout << std::endl;
    }
}
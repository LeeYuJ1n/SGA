#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    srand(GetTickCount64());

    //맞춰야 할 숫자 만들기
    int answer = (rand() % 100) + 1;

    //입력으로 맞출 숫자 만들기
    int inputNumber;
    
    //정답을 맞췄는가?
    bool correct = false; //처음 만들 때는 "거짓" 맞추면 "참"으로 바꾸기

    //실제 게임

    for (int i = 0; i < 10; i++)
        // i++와 ++i는 연산이 다 끝나면 +1이 된다는 점에서 같다
        // i++ : 연산 중에는 +1이 적용되지 않는다
        // ++i : 연산 중에 이미 +1적용된다
    {
        std::cout << "컴퓨터가 정한 랜덤 숫자가 무엇인지 맞춰주세요!" << std::endl;
        std::cout << "입력 : ";
        std::cin >> inputNumber;

        //입력으로 받은 inputNumber와 컴퓨터의 answer가 어떤지 비교

        if (inputNumber < answer)
        {
            std::cout << "입력한 숫자가 정답보다 작습니다." << std::endl;
        }
        else if (inputNumber > answer)
        {
            std::cout << "입력한 숫자가 정답보다 큽니다." << std::endl;
        }
        else //더 크지도 않고, 더 작지도 않으니까 "똑같다"는 결과뿐
        {
            std::cout << "정답입니다." << std::endl;
            correct = true;

            //여기서 정답이면 반복을 더 하지 않고, 중간에 끝내는 방법
            break; //반복문 중단 코드
        }
    }

    //여기까지 오면 5번의 입력이 모두 끝난 것

    if (correct == true)
    {
        std::cout << "축하합니다. 정답을 맞췄습니다!" << std::endl;
    }
    else //correct가 true가 된 적이 없다 -> 못 맞췄다
    {
        std::cout << "고생하셨습니다." << std::endl;
    }
}
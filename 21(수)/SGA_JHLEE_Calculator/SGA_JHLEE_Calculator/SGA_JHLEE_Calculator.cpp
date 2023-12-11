#include <iostream>

int main()
{
    // 수동 사칙연산
    // 두 숫자를 입력받고 + 어떤 계산을 하려는지도 입력받고 + 필요에 따라 수동종료 + 종료 아니면 무한
    // 계산하려고 하는 부분은 숫자로도 가능, + - * / 같은 기호로도 가능

    //변수 x3

    int firstNumber;
    int secondNumber;
    char opCode; // opCode : 오퍼레이션 코드, 오퍼레이터 = 연산자

    //계산하는 부분은 while
    while (true)
    {
        std::cout << "첫 번째 숫자를 입력하세요." << std::endl;
        std::cout << "입력 : ";
        std::cin >> firstNumber;

        std::cout << "두 번째 숫자를 입력하세요." << std::endl;
        std::cout << "입력 : ";
        std::cin >> secondNumber;

        std::cout << "어떤 연산을 하려는지 기호를 입력하세요." << std::endl;
        std::cout << "0을 입력하면 계산을 종료합니다." << std::endl;
        std::cout << "입력 : ";
        std::cin >> opCode;

        //여기까지 진행하면 변수를 입력으로 받기 완료

        //while 문 안에 변수를 하나 더 미리 만들어둡시다
        //자료형은 bool, 변수의 용도 = 이 변수가 true일 때 계산기를 종료하기 위함

        bool quit = false;

        switch (opCode)
            //어떤 연산을 할지를 정하는 조건이 "어떤 연산자를 썼는가"라는 조건 하나밖에 없고
            //어떤 연산자가 있을 수 있는지도 경우의 수가 정확하기 때문에 switch를 썼을 때 더 유리한 상황
        {
        case '+':
            std::cout << firstNumber << " + " << secondNumber << " = " << firstNumber + secondNumber << std::endl;
            break;

        case '-':
            std::cout << firstNumber << " - " << secondNumber << " = " << firstNumber - secondNumber << std::endl;
            break;

        case '*':
            std::cout << firstNumber << " * " << secondNumber << " = " << firstNumber * secondNumber << std::endl;
            break;

        case '/':
            //나누기의 경우 0으로 나누려고 하면 문제가 발생하므로,
            //0인 경우는 계산을 하지 않고 계산기를 종료하도록

            if (secondNumber != 0)
            {
                std::cout << firstNumber << " / " << secondNumber << " = " << firstNumber / secondNumber << std::endl;
            }
            else
            {
                std::cout << "0으로는 나눌 수 없습니다. 계산기를 종료합니다." << std::endl;
                quit = true; //종료 결정
            }
            
            break;

        case '%':

            if (secondNumber != 0)
            {
                std::cout << firstNumber << " % " << secondNumber << " = " << firstNumber % secondNumber << std::endl;
            }
            else
            {
                std::cout << "0으로는 나눌 수 없습니다. 계산기를 종료합니다." << std::endl;
                quit = true; //종료 결정
            }

            break;

        case '0': //0을 입력했는데 컴퓨터가 "0이라는 문자"를 인식했을 경우를 대비
            std::cout << "문자 0을 입력받았습니다." << std::endl;
            quit = true; //종료 결정
            break;

        case 0: //0을 입력했는데 컴퓨터가 "0이라는 문자 코드(0이라는 숫자)"를 인식했을 경우를 대비
            std::cout << "정수 0을 입력받았습니다." << std::endl;
            quit = true; //종료 결정
            break;

        default: //미리 정해지지 못한 입력이 생겼을 경우 (if문의 else하고 같은 상황)
            std::cout << "잘못된 입력입니다. 다시 시작하겠습니다." << std::endl;
            break;
        }

        if (quit == true) //종료가 결정된 경우
        {
            break; //반복문 전체를 break하겠다
        }

    }
}
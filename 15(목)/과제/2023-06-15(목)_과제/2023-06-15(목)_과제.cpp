// 이름 : 김유준
// 2023년 6월 15일 목요일 과제

#include <iostream>

int main()
{
    // 1. 사칙연산 출력기
    // 변수 두 개를 선언한 후, 입력으로 값을 받는다.
    // 입력으로 값을 받은 두 변수를 더하고, 뺴고, 곱하고, 나누고, 나머지까지 계산해서 모니터에 출력

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "과제 1" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    // Inputnumber1, Inputnumber2 변수 선언
    int Inputnumber1, Inputnumber2;

    // Inputnumber1 변수에 값 입력받기
    std::cout << "첫 번째 숫자 입력 : ";
    std::cin >> Inputnumber1;

    // Inputnumber1 변수에 값 입력받기
    std::cout << "두 번째 숫자 입력 : ";
    std::cin >> Inputnumber2;

    // 정리를 위한 경계선 출력
    std::cout << "---------------------------------------------" << std::endl;

    // Inputnumber1에 입력된 값을 화면에 출력
    std::cout << "입력된 첫 번째 숫자 : ";
    std::cout << Inputnumber1 << std::endl;

    // Inputnumber2에 입력된 값을 화면에 출력
    std::cout << "입력된 두 번째 숫자 : ";
    std::cout << Inputnumber2 << std::endl;

    // 정리를 위한 경계선 출력
    std::cout << "---------------------------------------------" << std::endl;

    // 더하기
    std::cout << "[ 더하기 ] ";
    std::cout << Inputnumber1;
    std::cout << " + ";
    std::cout << Inputnumber2;
    std::cout << " = ";
    std::cout << Inputnumber1 + Inputnumber2 << std::endl;

    // 빼기
    std::cout << "[ 빼기 ] ";
    std::cout << Inputnumber1;
    std::cout << " - ";
    std::cout << Inputnumber2;
    std::cout << " = ";
    std::cout << Inputnumber1 - Inputnumber2 << std::endl;
    
    // 나누기
    std::cout << "[ 나누기 ] ";
    std::cout << Inputnumber1;
    std::cout << " % ";
    std::cout << Inputnumber2;
    std::cout << " = ";
    std::cout << Inputnumber1 / Inputnumber2 << std::endl;

    // 곱하기
    std::cout << "[ 곱하기 ] ";
    std::cout << Inputnumber1;
    std::cout << " x ";
    std::cout << Inputnumber2;
    std::cout << " = ";
    std::cout << Inputnumber1 * Inputnumber2 << std::endl;

    // 나머지
    std::cout << "[ 나머지 ] ";
    std::cout << Inputnumber1;
    std::cout << "와 ";
    std::cout << Inputnumber2;
    std::cout << "를 계산 했을 때 나머지 값 :  ";
    std::cout << Inputnumber1 % Inputnumber2 << std::endl;

    // 2. 자릿수 계산하기
    // 변수 한 개를 선언한 후, 입력으로 값을 받는다. 단, 입력하는 숫자는 세 자릿수여야 한다.
    // 값을 받은 변수의 백의 자리, 십의 자리, 일의 자리를 각각 계산해서 모니터에 출력
    // 백의 자리, 십의 자리, 일의 자리는 계산해서 바로 출력해도 되고, 다른 변수에 저장해도 좋습니다.

    int number;

    // 정리를 위한 경계선 출력
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "과제 2" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    // number 변수에 값 입력받기
    std::cout << "숫자를 입력해주세요 : ";
    std::cin >> number;

    // 정리를 위한 경계선 출력
    std::cout << "---------------------------------------------" << std::endl;

    // 백의 자리
    int number100 = (number / 100) % 10;
    std::cout << "백의 자리 : ";
    std::cout << number100 << std::endl;

    // 십의 자리
    int number10 = (number / 10) % 10;
    std::cout << "백의 자리 : ";
    std::cout << number10 << std::endl;

    // 일의 자리
    int number1 = number % 10;
    std::cout << "백의 자리 : ";
    std::cout << number1 << std::endl;
}
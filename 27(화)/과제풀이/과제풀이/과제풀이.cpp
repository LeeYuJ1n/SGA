#include <iostream>

int main()
{
    // 소수 두 개 입력 받고 사칙연산(나머지 필요없음)

    // 변수가 필요하니까 두 개 선언만
    float firstNumber = 0;
    float secondNumber = 0;

    // 입력 받고 사칙연산 후에 그대로 출력

    std::cout << "첫 번째 수를 입력해주세요" << std::endl;
    std::cout << "입력 : ";
    std::cin >> firstNumber;
    std::cout << "첫 번째 수를 입력해주세요" << std::endl;
    std::cout << "입력 : ";
    std::cin >> firstNumber;

    // 사칙연산 출력할 때
    // std::cout << (계산 결과) << std::endl; → 이러면 좀 더 간단, 좀 더 확실

    // 좀 더 번거롭고, 좀 더 느리지만 안전한 방법 : 변수를 다 만드는 것
    // 변수는 만드느라 메모리를 잡아먹고, 계산 결과를 변수에 넣는 과정을 거치니까 → 요즘은 컴퓨터가 빠르니까

    // 결과를 출력할 변수 만들기
    float add = firstNumber + secondNumber;
    float sub = firstNumber - secondNumber;
    float mult = firstNumber * secondNumber;
    float div = firstNumber / secondNumber;

    std::cout << firstNumber << "와 " << secondNumber << "를 더한 값 : " << add << std::endl;
    std::cout << firstNumber << "에서 " << secondNumber << "를 뺀 값 : " << sub << std::endl;
    std::cout << firstNumber << "와 " << secondNumber << "를 곱한 값 : " << mult << std::endl;

    // 만약 여기서 조건문이 들어가야 한다면 여기서 두 번째 0일 경우 결과를 다르게(생략)
    std::cout << firstNumber << "를 " << secondNumber << "로 나눈 값 : " << div << std::endl;
}
#include <iostream>

int main()
{
    // 사칙연산 후 출력
    // 자릿수 구하기

    // 데이터 = 변수 만들기

    int firstNumber; //선언만 하기 (값은 입력으로 넣기)
    int secondNumber;

    int threeDigit;

    //변수에 입력으로 값을 넣기(할당)
    //선언된 변수에 값을 넣는 행동을 "할당"이라고 한다
    // + 선언과 할당을 동시에 하면 (만들 때 값까지 다 넣어주는 것을) "초기화"라고 한다

    std::cout << "첫 번째 숫자 입력 : "; //입력을 받아야 한다는 것과 무엇을 입력할지를 안내
    std::cin >> firstNumber;
    std::cout << "두 번째 숫자 입력 : ";
    std::cin >> secondNumber;
    std::cout << "세 자릿수 입력 : ";
    std::cin >> threeDigit;

    //사칙연산 후 출력

    // -> 연산과 동시에 출력까지
    std::cout << firstNumber + secondNumber << std::endl;
    std::cout << firstNumber - secondNumber << std::endl;
    std::cout << firstNumber * secondNumber << std::endl;
    std::cout << firstNumber / secondNumber << std::endl;
    std::cout << firstNumber % secondNumber << std::endl;

    // 자릿수 구하기

    // ::백의 자리?? = "십의 자리는 무시한다" = 그 숫자를 100으로 나눈 결과
    // ::십의 자리는? = "일의 자리는 무시한다" + "100보다 큰 숫자도 버린다"
    // = "숫자를 100으로 나눈 나머지" 중에서 "일의 자리를 뺀 것"(10으로 나눈 결과)
    // ::일의 자리는? = 그 숫자를 10으로 나눴을 때 생기는 나머지

    std::cout << threeDigit / 100 << std::endl; //백의 자리
    std::cout << (threeDigit % 100) / 10 << std::endl; //십의 자리
    // ()를 계산 코드에 사용하면 () 안에 있는 계산부터 먼저 한다 (수학하고 같다)
    std::cout << threeDigit % 10; //일의 자리

}
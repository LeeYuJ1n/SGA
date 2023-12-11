// 오늘의 실습 : 사칙연산을 함수로 다시 한 번 표현
// → 더하기 함수, 빼기 함수, 곱하기 함수, 나누기 함수, 나머지 함수를 각각 별개의 함수로 만들어보자
// → 함수 안에서 결과 출력해보기, return으로 결과를 받아서 main에서 출력해보기
// → 나누기, 나머지는 입력하는 수치 따라서 추가로 안에서 조건문을 써야 할 수도...

#include <iostream>

// 선언된 함수
int Sum(int _Number1, int _Number2); // 더하기
int Sub(int _Number1, int _Number2); // 빼기
int Multiplication(int _Number1, int _Number2); // 곱하기


int main()
{
    std::cout << "계산 결과입니다" << std::endl;
    std::cout << std::endl;
    Sum(100, 100); // 더하기
    Sub(100, 50); // 빼기
    Multiplication(2, 2); // 곱하기


}

int Sum(int _Number1, int _Number2)
{
    std::cout << "[ 더하기 ]";
    int result = _Number1 + _Number2;
    std::cout << result << std::endl;
    return result;
}

int Sub(int _Number1, int _Number2)
{
    std::cout << "[ 빼기 ]";
    int result = _Number1 - _Number2;
    return result;
}

int Multiplication(int _Number1, int _Number2)
{
    std::cout << "[ 곱하기 ]";
    int result = _Number1 * _Number2;
    return result;
}
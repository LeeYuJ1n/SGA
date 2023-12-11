// 오늘의 과제 : 변수를 써서 연산을 해봅시다
// 1. 사칙연산(한번에 쭉 해도 되고, 입력을 받아서 따로 계산해도 되고, 함수로 만들어도 되고...)
// → 단, float 두 개를 받아서 계산할 것, int 사용 금지
// → 소수와 소수를 나누면 결과도 소수도 나옵니다.따라서 나머지가 발생하지 않습니다. 그러므로 나머지 연산은 빼주세요(없어도 됩니다)

#include <iostream>

void calculation(float number_1, float number_2);

int main()
{
    float number_1, number_2;

    std::cout << "계산할 두 수를 입력해주세요" << std::endl;
    std::cin >> number_1;
    std::cin >> number_2;

    calculation(number_1, number_2);

}

void calculation(float number_1, float number_2)
{
    std::cout << number_1 << " + " << number_2 << " = " << number_1 + number_2 << std::endl;

    std::cout << number_1 << " - " << number_2 << " = " << number_1 - number_2 << std::endl;

    std::cout << number_1 << " * " << number_2 << " = " << number_1 * number_2 << std::endl;

    std::cout << number_1 << " / " << number_2 << " = " << number_1 / number_2 << std::endl;
}
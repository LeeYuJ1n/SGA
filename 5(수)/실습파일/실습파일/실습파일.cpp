#include <iostream>

void Check(int input)
{
    std::cout << &input << std::endl;
}

int main()
{
    int a = 0;
    int* ptr;

    std::cout << "변수 a의 값 : " << a << std::endl;
    std::cout << std::endl;
    std::cout << "변수 a의 메모리 주소 : " << &a << std::endl;
    std::cout << std::endl;
    
    ptr = &a;
    Check(a);
    Check(*ptr);
    std::cout << "[ ptr 사용 ] a변수가 컴퓨터에서 차지한 자리 : " << ptr << std::endl;
}
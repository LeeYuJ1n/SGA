#include <iostream>

int main()
{
    int a[5] = { 1, 3, 5, 7, 9 };
    int b[5] = { 2, 4, 6, 8, 10 };

    int ab[5][5];

    std::cout << a[0] << std::endl;
    std::cout << a[1] << std::endl;
    std::cout << b[3] << std::endl;
    std::cout << b[4] << std::endl;

    std::cout << ab[0][0] << std::endl;
    std::cout << ab[1][0] << std::endl;
}
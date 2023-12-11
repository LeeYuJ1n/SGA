#include <iostream>

int func(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return func(n - 1) + func(n - 2);
}

int main()
{
    std::cout << func(10) << std::endl;

    int arr[100];

    arr[0] = 0;
    arr[1] = 1;

    for (int i = 2; i <= 10; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }

    std::cout << arr[10] << std::endl;

    return 0;
}
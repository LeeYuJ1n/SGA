#include <iostream>

int main()
{
    int arr1[3] = {1, 2, 3};
    int arr2[5] = {1, 2, 3, 4, 5};
    int arr3[6] = {1, 2, 3, 4, 5, 6};

    int* arrPtr[3] = {arr1, arr2, arr3};

    int arrMeta[3] = {3, 5, 6};

    for (int i = 0; i <= 2; ++i)
    {
        for (int j = 0; j < arrMeta[i]; ++j)
        {
            std::cout << arrPtr[i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}
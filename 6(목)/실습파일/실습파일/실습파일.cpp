#include <iostream>

int main()
{
	char name[10] = "대한민국";
	char* namePtr = name;
	std::cout << namePtr << std::endl;
	std::cout << namePtr + 2 << std::endl;
	std::cout << name[2] << std::endl;
}
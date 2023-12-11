#include <iostream>

int main()
{
	int inputGameNumber;   
	std::cout << "숫자를 입력해주세요" << std::endl;
	std::cin >> inputGameNumber;

	switch (inputGameNumber)
	{
	case 1:
		std::cout << "로스트아크" << std::endl;
		break;

	case 2:
		std::cout << "오버워치" << std::endl;
		break;

	case 3:
		std::cout << "발로란트" << std::endl;
		break;

	case 4:
		std::cout << "클로저스" << std::endl;
		break;

	case 5:
		std::cout << "붕괴 : 스타레일" << std::endl;
		break;
		
	case 6:
		std::cout << "카스온라인" << std::endl;
		break;

	case 7:
		std::cout << "레프트 4 데드 2" << std::endl;
		break;

	case 8:
		std::cout << "버블파이터" << std::endl;
		break;

	case 9:
		std::cout << "메이플스토리" << std::endl;
		break;
	}
}
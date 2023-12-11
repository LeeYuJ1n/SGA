// 2023년 6월 20일 화요일
// 김유준

#include <iostream>

int main()
{
	bool loop = true;

	while (loop)
	{
		int inputNumber1 = 0, inputNumber2 = 0, result = 0;
		char operation;

		std::cout << "입력 가능한 숫자는 0부터 5까지입니다." << std::endl;

		std::cout << "첫 번째 숫자를 입력해주세요 : ";
		std::cin >> inputNumber1;
			
		std::cout << "두 번째 숫자를 입력해주세요 : ";
		std::cin >> inputNumber2;

		std::cout << "더하기(+) / 빼기(-) / 곱하기(*) / 나누기(/) / 나머지(%)" << std::endl;
		std::cout << "연산할 종류를 입력해주세요" << std::endl;
		std::cin >> operation;

		switch (operation)
		{
		case '0':
			std::cout << "프로그램 종료" << std::endl;
			loop = false;
			break;

		case '+':
			result = inputNumber1 + inputNumber2;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			std::cout << " [ 더하기 ] " << inputNumber1 << " + " << inputNumber2 << " = " << result << std::endl;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			break;

		case '-':
			result = inputNumber1 - inputNumber2;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			std::cout << " [ 빼기 ] " << inputNumber1 << " - " << inputNumber2 << " = " << result << std::endl;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			break;

		case '*':
			result = inputNumber1 * inputNumber2;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			std::cout << " [ 곱하기 ] " << inputNumber1 << " * " << inputNumber2 << " = " << result << std::endl;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			break;

		case '/':
			if (inputNumber1 == 0 || inputNumber2 == 0)
			{
				std::cout << "잘못된 입력입니다. 프로그램을 종료합니다." << std::endl;
				loop = false;
				break;
			}

			result = inputNumber1 / inputNumber2;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			std::cout << " [ 나누기 ] " << inputNumber1 << " / " << inputNumber2 << " = " << result << std::endl;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			break;

		case '%':
			if (inputNumber1 == 0 || inputNumber2 == 0)
			{
				std::cout << "잘못된 입력입니다. 프로그램을 종료합니다." << std::endl;
				loop = false;
				break;
			}

			result = inputNumber1 % inputNumber2;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			std::cout << " [ 나머지 ] " << inputNumber1 << " % " << inputNumber2 << " = " << result << std::endl;
			std::cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << std::endl;
			break;
		}
	}
}
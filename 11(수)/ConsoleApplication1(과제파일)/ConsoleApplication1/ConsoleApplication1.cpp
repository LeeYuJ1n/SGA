#include <iostream>
#include <conio.h>
#include <string>

int main()
{
	std::string result_str;

    while (true)
    {
		char null;

		null = _getch(); // _getch() 함수를 사용해 입력된 키를 인식한다음 null 변수 값으로 사용

		system("cls"); // 화면을 초기화

		result_str.push_back(null); // push_back를 사용해 str원소 맨 뒤에 새로운 원소를 추가

		std::cout << null << std::endl; // 현재 null 변수에 있는 값을 모니터에 출력
		std::cout << result_str << std::endl;  // 현재 str에 있는 모든 원소를 출력
    }
}
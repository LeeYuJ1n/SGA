#pragma once
#include <iostream>

class Sample // 실습용
{
private: // 개인정보
	int age; // 나이
	float Height; // 키

	void Print()
	{
		std::cout << "나이 : " << age << " 키 : " << Height << std::endl;
	}

public:
	int GetAge() { return age; }
	int GetHeight() { return Height; }
};
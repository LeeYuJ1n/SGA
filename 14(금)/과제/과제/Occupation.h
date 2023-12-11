#pragma once
#include <iostream>
#include "Character.h"

// Character 클래스를 Occupation의 파생 클래스로 설정
class Occupation : public Character
{
private:
	// 캐릭터 포지션
	int position;

public:
	// 기본 생성자
	Occupation()
	{
		position = 0;
	}

	// 캐릭터 출력용 함수
	void PrintMe()
	{
		std::cout << "캐릭터 아이디 : " << id << std::endl;
		std::cout << id << "의 레벨 : " << level << std::endl;
		std::cout << id << "의 체력 : " << strength << std::endl;
		std::cout << id << "의 공격력 : " << power << std::endl;
	}
};
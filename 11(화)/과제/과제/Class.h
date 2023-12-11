#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

class Class
{	
private:
	// 캐릭터 구조체
	struct Character
	{
		// 수정 불가능한 변수
		int rawID; // 캐릭터 고유 번호
		int strength; // 체력
		int attack; // 공격력
	};

	// Character 인스턴스 생성
	Character chara; // 캐릭터 1
	Character chara2; // 캐릭터 2

public:
	// 함수 선언
	void print();
	void pvpsystem();

	// 캐릭터 1 정보 : 도화가
	int id() { return chara.rawID = 1; } // 캐릭터1 아이디 : 1
	int strength() { return chara.strength = 100; } // 캐릭터1 체력 : 100
	int attack() { return chara.attack; } // 캐릭터1 공격력 : 10

	// 캐릭터 2 정보 : 기상술사
	int id2() { return chara2.rawID = 2; } // 캐릭터2 아이디 : 2
	int strength2() { return chara2.strength = 100; } // 캐릭터2 체력 : 100
	int attack2() { return chara2.attack; } // 캐릭터2 공격력 : 15
};
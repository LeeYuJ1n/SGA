#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

class Class
{	
private:
	// 변수
	const int rawID; // 캐릭터 고유 번호
	int strength; // 체력
	int attack; // 공격력
	bool dead;

	void ApplyDamage(float amount);

	void Dead();

public:
	// 함수 선언
	void print();

	// 생성자
	Class(int _strength, int _attack)
		: rawID(0) // 오류 방지용 코드
	{
		strength = _strength;
		attack = _attack;
	}

	void attack(Class* target, int attack);
};
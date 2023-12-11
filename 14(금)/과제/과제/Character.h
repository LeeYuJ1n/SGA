#pragma once
#include <iostream>
#include "Occupation.h"

class Character
{
	// 게임에 등장할 캐릭터 구성

// 개인정보
protected: // 제한된 공개정보
	int id; // 아이디
	int level; // 레벨
	float strength; // 체력
	float power; // 공격력

	void ImOut()
	{
		std::cout << "[ 멤버 이니셜 라이저 실행 성공 ] 시험코드 1" << std::endl;
	}

public: // 공개정보
	// 자기가 가진 정보를 필요에 따라 보여줄 수 있는 것
	int GetId() { return id; }
	int GetLevel() { return level; }
	float GetStrength() { return strength; }
	float GetPower() { return power; }

	// 기본 생성자
	Character()
	{
		id = 0;
		level = 0;
		strength = 0;
		power = 0;
	}

	// 멤버 이니셜라이저
	Character(int _id, int _level, float _strength, float _power)
		:id(_id),
		level(_level),
		strength(_strength),
		power(_power)
	{
		// 출력 확인용 함수
		ImOut();
	}
};
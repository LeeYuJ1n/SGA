#pragma once
#include <iostream>

// 헤더에서 전역변수 및 함수선언으로 두가지 만들기

// 캐릭터 두명
// 캐릭터에 영향을 끼치는 함수

// *출력

// 캐릭터(구조체)
struct  Character
{
	// 여러 가지 하위 변수들이 있어야겠지만, 시간상 변수 둘만 빠르게
	float hitPoint; // HP, 체력
	int atk; // attack : 공격력
};

// 구조체에서 변수 둘 = 캐릭터 둘
Character chara1;
Character chara2;

// 캐릭터에 영향을 주는 함수ㅇ
void LevelUp_1();
void LevelUp_2(); // 매개변수 없이 직접 전역변수에 개입

void PrintChara(Character thisOne); // 구조체 변수도 변수니까 매개변수 가능

void Attack(Character actor, Character target);
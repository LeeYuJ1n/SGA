#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

// 전역변수
int inputSelect = 0;
bool loop = true;
int Cha_1_Level = 1;
int Cha_1_experience = 0;
int Cha_1_strength = 0;
int Cha_2_Level = 0;
int Cha_2_experience = 0;
int Cha_2_strength = 0;

// 구조체(캐릭터 정보)
struct Character_1
{
	char chaName[20] = "도화가"; // 캐릭터 이름
	int level = 1; // 레벨
	float experience = 0; // 경험치
	int strength = 1000; // 체력
	int power = 500; // 공격력
	int defensive = 800; // 방어력
	int gold = 1000; // 재련 재화
};

// Character_1에 대한 인스턴스 생성
Character_1 Cha_1;

struct Character_2
{
	char chaName[20] = "기상술사"; // 캐릭터 이름
	int level = 1; // 레벨
	float experience = 0; // 경험치
	int strength = 1000; // 체력
	int power = 5000; // 공격력
	int defensive = 20; // 방어력
	int gold = 1000; // 재련 재화
};

// Character_2에 대한 인스턴스 생성
Character_2 Cha_2;

void Character_1_SpecUp();
void Character_2_SpecUp();
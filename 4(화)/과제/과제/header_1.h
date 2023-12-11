#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

// ��������
int inputSelect = 0;
bool loop = true;
int Cha_1_Level = 1;
int Cha_1_experience = 0;
int Cha_1_strength = 0;
int Cha_2_Level = 0;
int Cha_2_experience = 0;
int Cha_2_strength = 0;

// ����ü(ĳ���� ����)
struct Character_1
{
	char chaName[20] = "��ȭ��"; // ĳ���� �̸�
	int level = 1; // ����
	float experience = 0; // ����ġ
	int strength = 1000; // ü��
	int power = 500; // ���ݷ�
	int defensive = 800; // ����
	int gold = 1000; // ��� ��ȭ
};

// Character_1�� ���� �ν��Ͻ� ����
Character_1 Cha_1;

struct Character_2
{
	char chaName[20] = "������"; // ĳ���� �̸�
	int level = 1; // ����
	float experience = 0; // ����ġ
	int strength = 1000; // ü��
	int power = 5000; // ���ݷ�
	int defensive = 20; // ����
	int gold = 1000; // ��� ��ȭ
};

// Character_2�� ���� �ν��Ͻ� ����
Character_2 Cha_2;

void Character_1_SpecUp();
void Character_2_SpecUp();
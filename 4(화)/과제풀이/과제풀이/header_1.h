#pragma once
#include <iostream>

// ������� �������� �� �Լ��������� �ΰ��� �����

// ĳ���� �θ�
// ĳ���Ϳ� ������ ��ġ�� �Լ�

// *���

// ĳ����(����ü)
struct  Character
{
	// ���� ���� ���� �������� �־�߰�����, �ð��� ���� �Ѹ� ������
	float hitPoint; // HP, ü��
	int atk; // attack : ���ݷ�
};

// ����ü���� ���� �� = ĳ���� ��
Character chara1;
Character chara2;

// ĳ���Ϳ� ������ �ִ� �Լ���
void LevelUp_1();
void LevelUp_2(); // �Ű����� ���� ���� ���������� ����

void PrintChara(Character thisOne); // ����ü ������ �����ϱ� �Ű����� ����

void Attack(Character actor, Character target);
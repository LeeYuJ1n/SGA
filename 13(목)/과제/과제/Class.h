#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

class Class
{	
private:
	// ����
	const int rawID; // ĳ���� ���� ��ȣ
	int strength; // ü��
	int attack; // ���ݷ�
	bool dead;

	void ApplyDamage(float amount);

	void Dead();

public:
	// �Լ� ����
	void print();

	// ������
	Class(int _strength, int _attack)
		: rawID(0) // ���� ������ �ڵ�
	{
		strength = _strength;
		attack = _attack;
	}

	void attack(Class* target, int attack);
};
#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

class Class
{	
private:
	// ĳ���� ����ü
	struct Character
	{
		// ���� �Ұ����� ����
		int rawID; // ĳ���� ���� ��ȣ
		int strength; // ü��
		int attack; // ���ݷ�
	};

	// Character �ν��Ͻ� ����
	Character chara; // ĳ���� 1
	Character chara2; // ĳ���� 2

public:
	// �Լ� ����
	void print();
	void pvpsystem();

	// ĳ���� 1 ���� : ��ȭ��
	int id() { return chara.rawID = 1; } // ĳ����1 ���̵� : 1
	int strength() { return chara.strength = 100; } // ĳ����1 ü�� : 100
	int attack() { return chara.attack; } // ĳ����1 ���ݷ� : 10

	// ĳ���� 2 ���� : ������
	int id2() { return chara2.rawID = 2; } // ĳ����2 ���̵� : 2
	int strength2() { return chara2.strength = 100; } // ĳ����2 ü�� : 100
	int attack2() { return chara2.attack; } // ĳ����2 ���ݷ� : 15
};
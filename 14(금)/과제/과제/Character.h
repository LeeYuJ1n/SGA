#pragma once
#include <iostream>
#include "Occupation.h"

class Character
{
	// ���ӿ� ������ ĳ���� ����

// ��������
protected: // ���ѵ� ��������
	int id; // ���̵�
	int level; // ����
	float strength; // ü��
	float power; // ���ݷ�

	void ImOut()
	{
		std::cout << "[ ��� �̴ϼ� ������ ���� ���� ] �����ڵ� 1" << std::endl;
	}

public: // ��������
	// �ڱⰡ ���� ������ �ʿ信 ���� ������ �� �ִ� ��
	int GetId() { return id; }
	int GetLevel() { return level; }
	float GetStrength() { return strength; }
	float GetPower() { return power; }

	// �⺻ ������
	Character()
	{
		id = 0;
		level = 0;
		strength = 0;
		power = 0;
	}

	// ��� �̴ϼȶ�����
	Character(int _id, int _level, float _strength, float _power)
		:id(_id),
		level(_level),
		strength(_strength),
		power(_power)
	{
		// ��� Ȯ�ο� �Լ�
		ImOut();
	}
};
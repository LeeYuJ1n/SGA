#pragma once
#include <iostream>
#include "Character.h"

// Character Ŭ������ Occupation�� �Ļ� Ŭ������ ����
class Occupation : public Character
{
private:
	// ĳ���� ������
	int position;

public:
	// �⺻ ������
	Occupation()
	{
		position = 0;
	}

	// ĳ���� ��¿� �Լ�
	void PrintMe()
	{
		std::cout << "ĳ���� ���̵� : " << id << std::endl;
		std::cout << id << "�� ���� : " << level << std::endl;
		std::cout << id << "�� ü�� : " << strength << std::endl;
		std::cout << id << "�� ���ݷ� : " << power << std::endl;
	}
};
#pragma once
#include <iostream>

class Sample // �ǽ���
{
private: // ��������
	int age; // ����
	float Height; // Ű

	void Print()
	{
		std::cout << "���� : " << age << " Ű : " << Height << std::endl;
	}

public:
	int GetAge() { return age; }
	int GetHeight() { return Height; }
};
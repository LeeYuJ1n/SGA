#pragma once
#include <iostream>
#include <Windows.h>

// ���
#include "Arithmetic_Class.h" // ��Ģ���� ������

using namespace std;

class Singleton_Class : public Arithmetic_Class
{
private:
	// private�� �����ڿ� �Ҹ��� ����
	Singleton_Class();      // ������
	~Singleton_Class();     // �Ҹ���

	// ��ü ���޿� ������ �ν��Ͻ�
	static Singleton_Class* instance;

public:
	static Singleton_Class* Get()
	{
		// ���� instance�� ���ٸ� ����
		if (instance == nullptr)
		{
			// �ڱ� �ڽ��� instance�� ����
			instance = new Singleton_Class();
		}

		// instance ��ȯ
		return instance;
	}
	
	// ���� ������ Ŭ������ ȣ�� �� ���
	void ArithmeticZip();

	// instance ������ �޸� ���� ����
	void Delete();
};


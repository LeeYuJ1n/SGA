#pragma once
#include <iostream>

class Arithmetic_Class
{
public:
	// public�� �����ڿ� �Ҹ��� ����
	Arithmetic_Class();         // ������
	~Arithmetic_Class();        // �Ҹ���

	// ��ü ���޿� instance
	static Arithmetic_Class* instance;

	static Arithmetic_Class* Get()
	{
		// ���� instance�� ������ ���� ���ٸ�
		if (instance == nullptr)
		{
			// �ڱ� �ڽ��� instance�� ����
			instance = new Arithmetic_Class();
		}

		// instance ��ȯ
		return instance;
	}

	// ��Ģ���� �Լ�
	void Add(int _x, int _y);              // ���ϱ�
	void Sub(int _x, int _y);              // ����
	void Mult(int _x, int _y);             // ���ϱ�
	void Div(int _x, int _y);              // ������
	void Remainder(int _x, int _y);        // ������

	// ���꿡 �ʿ��� ����
	int x = 0, y = 0;

	// �� �� instance�� ���� �� ���
	void Delete();
};


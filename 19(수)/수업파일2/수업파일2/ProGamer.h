#pragma once
#include "Human.h"

class ProGamer : public Human
{
	int tier;

public:
	// �ڽ� Ŭ���� �߿��� ������ ������ ���� �ִ� ��쵵 �ִ�

	ProGamer() 
	{
		tier = 0;
	}
	
	virtual void Live() override
	{
		std::cout << "���ΰ��̸Ӵ� ������ �� �մϴ�" << std::endl;
		// �����Լ����� �ڱ� ������ ����
		std::cout << "Ƽ�" << tier << " Ƽ����!" << std::endl;
	}
};


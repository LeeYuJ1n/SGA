#pragma once
#include "Human.h"

class Vendor : public Human // ������
{
public:
	Vendor() {}

	// �����Լ�(�� �纻) �ۼ�
	virtual void Live() override
	{
		std::cout << "�������� �ֵ��׸� ���ְ� ����ϴ�" << std::endl;
	}
};


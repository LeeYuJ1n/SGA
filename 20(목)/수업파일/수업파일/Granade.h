#pragma once
#include "Character.h"
#include "Item.h"

class Granade : public Item
{
protected:
	int id;
	float magnitude;
	int type;

public:
	Granade()
	{
		id = 0;
		magnitude = 0;
		type = 0;
	}

	Granade(int _id, int _type, float _magnitude)
	{
		id = _id;
		magnitude = _magnitude;
		type = _type;
	}

	// �����Լ��� �����ͼ� ����
	virtual int GetID() override { return id; }
	virtual float GetMagnitude() override { return magnitude; }
	virtual int GetType() override { return type; }

	virtual void Use(Character* target) override
	{
		std::cout << "������ ���ż� " << magnitude << "��ŭ ȸ���߽��ϴ�!" << std::endl;

		if (target->hp > 0)
		{
			target->hp -= magnitude; // ���ݷ¸�ŭ ���ظ� �ְ�
			if (target->hp < 0) // ���� ��� HP�� ������ �� ��Ȳ�̸�
			{
				target->hp = 0; // 0���� ����
			}
			std::cout << "���� ü�� :  " << target->hp << std::endl;
		}
		else
		{
			std::cout << "�׸��ϼ���! �̹� ǥ���� ü���� 0�Դϴ� " << std::endl;
			std::cout << "���� ü�� :  " << target->hp << std::endl;
		}
	}
};


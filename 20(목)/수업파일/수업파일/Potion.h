#pragma once
#include "Item.h"
#include "Character.h" // ���⼭�� �ε��� ���� ���� ����(�ȿ� �ִ� ��� ������ ��� �ؼ�)

class Potion : public Item
{
protected:
	int id;
	float magnitude;
	int type;

public:
	Potion()
	{
		id = 0;
		magnitude = 0;
		type = 0;
	}

	Potion(int _id, int _type, float _magnitude)
	{
		id = _id;
		magnitude = _magnitude;
		type = _type;
	}

	// �����Լ��� �����ͼ� ����
	virtual int GetID() override { return id; }
	virtual float GetMagnitude() override { return magnitude; }
	virtual int GetType() override { return type; }

	// ������ �ڽ� Ŭ�������� �ᱹ�� ���� ������ �����ٵ�,
	// �� ���� �̷� �ͱ��� �����Լ��� �������? : ���� Ŭ������ �߻� Ŭ������ ����� ����
	// �� ������ ���� ��ü�δ� ���� �� �� ������ ���ڱ�
	
	// ��� ����
	virtual void Use(Character* target) override
	{
		std::cout << "������ ���ż� " << magnitude << "��ŭ ȸ���߽��ϴ�!" << std::endl;

		if (target->hp < target->maxHp)
		{
			target->hp += magnitude; // ȸ���� ���ְ�
			if (target->hp > target->maxHp) // ȸ�� ��� HP�� ������ �Ѿ�����
			{
				target->hp = target->maxHp; // �ִ�ġ�� ������
			}
			std::cout << "���� ü�� :  " << target->hp << std::endl;
		}
		else
		{
			std::cout << "�׷��� �ִ� ü���̶� ü���� �״��..." << std::endl;
			std::cout << "���� ü�� :  " << target->hp << std::endl;
		}

		// �߰� �Լ� �Ẹ��
		Duplicate();
	}

	// ������ ���, �߰��� �� �� �ִ� �Լ��� �ִٰ� �����غ��ô�
	// �� �Լ��� ���ǿ��� ���� ���� �Լ��� ���� �Լ��� �ƴմϴ�
	void Duplicate() // "�����ϴ�"
	{
		// �ӽ÷� ����� ���
		std::cout << "������ ���� �Լ��� �ҷ��Խ��ϴ�" << std::endl;
	}
};


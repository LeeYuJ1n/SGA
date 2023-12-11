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

	// 가상함수를 가져와서 구현
	virtual int GetID() override { return id; }
	virtual float GetMagnitude() override { return magnitude; }
	virtual int GetType() override { return type; }

	virtual void Use(Character* target) override
	{
		std::cout << "포션을 마셔서 " << magnitude << "만큼 회복했습니다!" << std::endl;

		if (target->hp > 0)
		{
			target->hp -= magnitude; // 공격력만큼 피해를 주고
			if (target->hp < 0) // 공격 결과 HP가 음수가 될 상황이면
			{
				target->hp = 0; // 0으로 조정
			}
			std::cout << "현재 체력 :  " << target->hp << std::endl;
		}
		else
		{
			std::cout << "그만하세요! 이미 표적의 체력은 0입니다 " << std::endl;
			std::cout << "현재 체력 :  " << target->hp << std::endl;
		}
	}
};


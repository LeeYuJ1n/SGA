#pragma once
#include "Item.h"
#include "Character.h" // 여기서는 로딩을 피할 수가 없다(안에 있는 멤버 변수를 써야 해서)

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

	// 가상함수를 가져와서 구현
	virtual int GetID() override { return id; }
	virtual float GetMagnitude() override { return magnitude; }
	virtual int GetType() override { return type; }

	// 어차피 자식 클래스마다 결국은 같은 변수가 쓰일텐데,
	// 왜 굳이 이런 것까지 가상함수로 만드느냐? : 원본 클래스를 추상 클래스로 만들기 위함
	// → 원본은 원본 자체로는 절대 쓸 수 없음을 못박기
	
	// 사용 구현
	virtual void Use(Character* target) override
	{
		std::cout << "포션을 마셔서 " << magnitude << "만큼 회복했습니다!" << std::endl;

		if (target->hp < target->maxHp)
		{
			target->hp += magnitude; // 회복을 해주고
			if (target->hp > target->maxHp) // 회복 결과 HP가 상한을 넘었으면
			{
				target->hp = target->maxHp; // 최대치로 재조정
			}
			std::cout << "현재 체력 :  " << target->hp << std::endl;
		}
		else
		{
			std::cout << "그러나 최대 체력이라 체력은 그대로..." << std::endl;
			std::cout << "현재 체력 :  " << target->hp << std::endl;
		}

		// 추가 함수 써보기
		Duplicate();
	}

	// 포션의 경우, 추가로 쓸 수 있는 함수도 있다고 가정해봅시다
	// 이 함수는 포션에서 새로 만든 함수라서 가상 함수가 아닙니다
	void Duplicate() // "복제하다"
	{
		// 임시로 모니터 출력
		std::cout << "아이템 복제 함수를 불러왔습니다" << std::endl;
	}
};


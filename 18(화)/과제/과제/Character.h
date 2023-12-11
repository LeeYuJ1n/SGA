#pragma once
#include "Item.h"

// Ä³¸¯ÅÍ
class Character : public Item
{
protected:
	int id;
	int level;
	float strength;
	int power;
	int item;
	bool dead;

public:
	int GetId() { return id; }
	int GetLevel() { return level; }
	float GetStrength() { return strength; }
	int GetPower() { return power; }
	int GetItem() { return item; }

	Character()
	{
		id = 0;
		level = 0;
		strength = 0;
		power = 0;
		item = 0;
	}

	Character(int _id, int _level, float _strength, int _power, int _item)
		:id(_id), level(_level), strength(_strength), power(_power), item(_item)
	{
		dead = false;
	}

	void PrintStat();

	void Attack(Character* target);

	void SpecUp();
};
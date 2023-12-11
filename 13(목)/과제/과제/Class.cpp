#include <iostream>
#include <Windows.h>
#include "Class.h"

void Class::attack(Class* target, int attack)
{
	int _attacker = this -> rawID;
	int _target = target -> rawID;

	std::cout << _attacker << "번 캐릭터가 " << _target << "번 캐릭터한테 " << this -> attack * attack << "의 데미지를 주었습니다" << std::endl;
}

void Class::ApplyDamage(float amount)
{
	this -> strength -= amount;

	if (this -> strength <= 0)
	{
		this->dead = true;

		this->Dead();
	}
}

void Class::print()
{
    std::cout << "< " << rawID << " 번 캐릭터 능력치 >" << std::endl;
    std::cout << std::endl;

    std::cout << rawID << "번 캐릭터 공격력 : " << attack << std::endl;
    std::cout << std::endl;
}

void Class::Dead()
{
	std::cout << rawID << "이 패배했습니다" << std::endl;
	std::cout << std::endl;
}
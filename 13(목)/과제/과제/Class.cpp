#include <iostream>
#include <Windows.h>
#include "Class.h"

void Class::attack(Class* target, int attack)
{
	int _attacker = this -> rawID;
	int _target = target -> rawID;

	std::cout << _attacker << "�� ĳ���Ͱ� " << _target << "�� ĳ�������� " << this -> attack * attack << "�� �������� �־����ϴ�" << std::endl;
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
    std::cout << "< " << rawID << " �� ĳ���� �ɷ�ġ >" << std::endl;
    std::cout << std::endl;

    std::cout << rawID << "�� ĳ���� ���ݷ� : " << attack << std::endl;
    std::cout << std::endl;
}

void Class::Dead()
{
	std::cout << rawID << "�� �й��߽��ϴ�" << std::endl;
	std::cout << std::endl;
}
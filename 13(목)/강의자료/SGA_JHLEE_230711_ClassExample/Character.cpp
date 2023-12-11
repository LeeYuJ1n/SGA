#include "Character.h"

//함수 정의

void Character::Init(int _id, float _hp, int _atk)
{
	id = _id;
	hitPoint = _hp;
	attack = _atk;
	dead = false; // 생성 시점에서야 죽었을 리가 없으니, 매개변수 필요 없이 그냥 값을 false로
}

void Character::Attack(Character* target, float attackMullt)
{
	//공격자, 피격자 정보 확인

	int _attacker = this->id;
	int _target = target->id;

	// 위 코드에서 쓰인 this : 각 인스턴스에서 자기 자신을 가리키는 포인터
	// 따라서 이 함수의 this : 공격하는 쪽이 id를 가리킨다

	//전투 표현 (텍스트로)

	std::cout << _attacker << "번 인물이 " << _target << "번 인물에게 " << this->attack * attackMullt << "의 위력으로 타격!" << std::endl;

	// 전투 결과
	target->ApplyDamage(this->attack * attackMullt);
	// 공격을 받는 쪽도 일단은 같은 클래스를 공유하는 다른 인스턴스.
	// 그러므로 main에서는 숨겨진 함수 변수를 쓸 수 없지만, 클래스라는 같은 설계도 안에서는
	// 숨겨졌던 private 변수 함수를 자유롭게 쓸 수 있습니다!!

	//줄 바꾸고 출력

	std::cout << std::endl;

	std::cout << "현재 목표의 상태" << std::endl;
	target->PrintMe();

	std::cout << "현재 공격한 쪽의 상태" << std::endl;
	this->PrintMe();
}

void Character::ApplyDamage(float amount)
{
	this->hitPoint -= amount;

	//this 의 기준은 함수(와 변수)를 호출하는 주체
	//따라서 이 함수에서 쓰인 this는 위 Attack에서 공격을 받았던, 표적을 뜻한다 (표적"이 자기에게" 피해를 적용)

	if (this->hitPoint <= 0)
	{
		this->dead = true; //체력이 0 밑이면 꽥

		this->WhenDead();
	}
}

void Character::PrintMe()
{
	std::cout << "< " << id << " 번 인물의 간이 능력치 >" << std::endl;
	std::cout << std::endl;

	std::cout << id << "번 인물의 내구력 : " << hitPoint << std::endl;
	std::cout << id << "번 인물의 기초 공격력 : " << attack << std::endl;
	std::cout << std::endl;

	// 멤버 이니셜라이저 사용시 상수값을 보기 위한 자료
	if (id2 != 0)
	{
		std::cout << "< " << id << " 번 인물의 간이 능력치 >" << std::endl;
		std::cout << std::endl;

		std::cout << id << "번 인물의 상수값1 : " << id2 << std::endl;
		std::cout << id << "번 인물의 상수값2 : " << f2 << std::endl;
		std::cout << std::endl;
	}
}


void Character::WhenDead()
{
	std::cout << id << "번 인물이 쓰러졌습니다." << std::endl;
	std::cout << std::endl;

	//this는 문법적으로 생략 가능. (id나, this->id나 똑같다)
	//누가 이 함수를 불렀는지 너무나 명명백백하면 this를 그냥 안 써도 아무 문제가 없다
}
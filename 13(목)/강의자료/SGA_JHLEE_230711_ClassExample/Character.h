#pragma once
#include <iostream>

class Character
{
private: // 밖에서 보면 안되는 자료
	//변수모음집
	int id;
	float hitPoint;
	int attack;
	int mana;
	bool dead; //죽었나?
	const int id2;
	const float f2;

	//함수 (클래스 밖에선 알 필요 없음)

	void ApplyDamage(float amount);
	//위는 공격을 받은 쪽에서 피해를 적용하기 위한 함수. 얻어맞는 당사자(인스턴스)에게 꼭 필요한 기능이지만,
	//"전투 개발자" 입장에선 "공격하면 다른 쪽이 내 공격력으로 피해를 입는다"는 데까지만 알면 그만.

	void WhenDead(); //죽으면 출력할 함수

public: // 밖에서 호출 가능

	// 변수 세팅 함수, 이니시에이터
	// : private 변수를 세팅할 수 있다는 장점이 있지만 위험하다
	// 현실적으로 이런 함수를 흔히 쓰지는 않는다(꼭 필요하면 쓰기는 쓴다)
	void Init(int _id, float _hp, int _atk);

	// 이니시에이터 대신에 쓸 수 있는, 객체의 값을 처음에 설정하는 방법
	// → C++에서 기본으로 제공하는 기능
	
	//  : 생성자(constructor, 건축가, 건축계획)

	// 생성자 작성 예시
	Character() // 자료형 없이, 클래스 이름을 그대로 사용한 함수 생성
		:id2(0), f2(0) // 오류 방지용 코드
		// 이 함수는 인스턴시 생성 시에 단 한 번 부를 수 있다
		// 그리고 생성 후(return 필요없이) Character라는 클래스를 반환(후 인스턴스 적용)
	{
		// 생성자에 각 변수를 설정 가능
		id = 0;
		hitPoint = 1;
		attack = 0;
		mana = 1000;
		dead = false;
	} // 이것이 기본 생성자

	// 생성자는 매개변수를 다르게 설정하면 한 클래스에 여러 개 만들 수도 있다
	Character(int _id, float _hp, int _attack, int _mana) // 호출마다 매개변수를 받아서
		:id2(0), f2(0) // 오류 방지용 코드
	{
		// 받은 매개변수를 private이었던 변수에 대입
		id = _id;
		hitPoint = _hp;
		attack = _attack;
		mana = _mana;
		dead = false;
	}

	// ---------------------------------------------------

	// 클래스에 상수가 있을 경우, 생성자만으로는 상수에 값을 넣는 것이 힘들다
	// : 먼저 변수가 선언이 된 후에, 생성자를 통해서 그 다음 값을 할당하는 절차라서
	// : 상수가 있는 클래스는 특별한 방법으로(상수가 없어도 본 방법 적용 가능)
	// 인스턴스 생성과 동시에 변수 전체 초기화를 할 수 있다

	Character(int _id, float _hp, int _attack, int _mana, int _conValue, float _conFloat) // 4번째 매개변수를
		: id2(_conValue), f2(_conFloat), id(_id), hitPoint(_hp), attack(_attack)// 매개변수 넣는 ()가 끝난 뒤에 : 을 붙이고
		// : 뒤에 클래스에서 필요한 변수와, 그 안에 들어가야 할 값을 변수(값) 모양으로 입력해준다
		// 이 방법으로 값을 할당할 변수가 둘 이상이면, (쉼표)로 구분한다
		// 이렇게 매개변수를 초기화에 직접 사용하는 문법을

		// "멤버 이니셜라이저"라고 한다(줄여서 이니셜라이저)
	{
		mana = _mana;
		dead = false;
	}

	// ---------------------------------------------------

	// 위 사례에서도 볼 수 있지만, 생성자를 만든다고 모든 변수에 매개변수를 대입할 필요는 없다
	// 무조건 정해진 변수가 있다면 그건 그냥 생성자 내에서 따로 만들어도 무방

	// 이렇게 생성자를 만들게 되면, 인스턴스 생성과 동시에(혹은 거의 동시에)
	// 변수를 클래스에 곧바로 할당 가능

	// 인스턴스 생성 시에 부르는 것이기 때문에, public으로 호출 가능하면서도
	// 불필요하게 여러 번 호출해서 데이터의 완전을 위협할 가능성이 줄어든다

	// 생성자의 사용 예시는 main에서 봅시다

	// id 게터 (짧으니 정의까지 해치웁시다)
	int GetID() { return id; }

	// 생사 여부도 게터로
	bool GetDead() { return dead; }

	// 공격!
	void Attack(Character* target, float attackMullt);

	// 출력
	void PrintMe();

};


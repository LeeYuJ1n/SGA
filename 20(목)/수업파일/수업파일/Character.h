#pragma once
// #include "Potion.h"

// 아이템과 포션이 있다
class Item;
class Potion;

class Character
{
	// private이 좋은데, 시간과 확인 편의상 public으로 작성
public:
	float hp; // 캐릭터의 체력(확인용 변수)
	float maxHp; // 캐릭터의 최대 체력

	// 캐릭터는 아이템 세 개를 가집니다
	// 이 아이템은 포션일 수도 있고, 다른 뭔가일 수도 있습니다
	Item* i1;
	Item* i2;
	Item* i3;

	Character() 
		: i1(nullptr), 
		i2(nullptr), 
		i3(nullptr),
		hp(1000),
		maxHp(1000)
	{
		// 이 생성자를 실행했을 때 내가 원하는 것:
		// 처음에는 아무 아이템도 없고 나중에 (코드든 다른 뭔가로든) 부여받는 것
		// 매개변수도 필요없고 다른 의도를 적용하는 것도 의미 없다
		// 공유나 의도 선언의 없다면 굳이 몸체 초기화(여기에 코딩)가 필요하지 않을지도...
	}
};


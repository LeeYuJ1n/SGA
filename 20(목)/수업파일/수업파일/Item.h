#pragma once // 같은 기능 두 번 로딩 방지용. 자동 생성됨
#include <iostream> // 혹시 모르니까 출력용 미리 로딩
// #include "Character.h" // 아이템을 쓸 대상을 로딩..하지 않도록 하겠다(상호참조 문제 방지)

class Character; // "캐릭터라는 클래스가 있다"고 선언만 해준다(실제 정의는 다른 파일에서)

class Item
{
public:
	// 추상 클래스로 만들 생각이므로 가상함수만

	// 가상 함수에서도 그 이름을 통해서 클래스의 필요한 변수를 어느 정도는 짐작을 시켜줄 수 있다
	virtual int GetID() = 0; // ← 이 함수의 이름을 본 사람은 대체로 "이 클래스에는 ID가 있어야겠구나"라고 짐작
	virtual float GetMagnitude() = 0; // ← magnitude : 강한 정도, 아이템의 효과에 자주 인용, 회복 아이템이라면 회복량, 무기라면 공격력
	virtual int GetType() = 0; // ← 아이템 타입

	// 위는 변수를 위한 가상 겟터

	// 아래가 함수
	virtual void Use(Character* target) = 0; // ← 아이템은 사용하려고 만드는 것

	Item(){} // ← 생성자를 만들지만 어차피 호출은 못 한다
};


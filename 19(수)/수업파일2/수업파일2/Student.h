#pragma once
#include "Human.h"

class Student : public Human
{
public: // 편의상 public만 작성
	Student() { } // 현재 상황에서는 원본을 생성자를 부를 필요가 없다

	// Human에서 만든 함수를 다시 만들기(오버라이드)
	// virtual을 쓰는 가상함수는 둘이 한 쌍(사본과 원본)
	// =virtual을 쓰고 내용이 있다 : 얘는 사본이다, 하고 알 사람들은 알겠지만
	// 조금 더 확실히 하는 문법적 의미 표시가 하나 더 있다 : 매개변수 뒤 override
	// : 잘 모르는 사람과도 가상함수의 관계성을 정확히 공유하기에 좋다
	virtual void Live() override // 오버라이드된, 즉 사본으로 존재하는 가상 함수라는 뜻
	{
		// 가상 함수의 내용 (개별 자식 클래스용 연산)
		std::cout << "학생은 공부합니다" << std::endl;
	}

	// 학생이란 자식 클래스와, 학생만의 생활이 있으니
	// 다른 클래스도 이렇게 만들 수 있지 않을까?
};


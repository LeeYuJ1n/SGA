#pragma once
#include "Human.h"

class ProGamer : public Human
{
	int tier;

public:
	// 자식 클래스 중에는 별개의 변수를 갖고 있는 경우도 있다

	ProGamer() 
	{
		tier = 0;
	}
	
	virtual void Live() override
	{
		std::cout << "프로게이머는 게임을 잘 합니다" << std::endl;
		// 가상함수에서 자기 변수를 쓰기
		std::cout << "티어가" << tier << " 티어임!" << std::endl;
	}
};


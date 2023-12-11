#pragma once
#include "Human.h"

class Vendor : public Human // 노점상
{
public:
	Vendor() {}

	// 가상함수(의 사본) 작성
	virtual void Live() override
	{
		std::cout << "노점상은 핫도그를 맛있게 만듭니다" << std::endl;
	}
};


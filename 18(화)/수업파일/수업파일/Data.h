#pragma once

// 계산기에 써먹을 데이터 클래스
class Data
{
protected: // 상속받는 클래스가 있으면 거기서도 쓸 수 있게

	// 정수 데이터
	int integer1;
	int integer2;

	// 소수 데이터
	float singleNumber1; // single : 부동소수점 자료형을 지칭하는 또 다른 이름 중 하나
	float singleNumber2; // 밑에 있는 "배정밀도"에 대응해서, "1배수 정밀도", "단정밀도"라는 뜻함

	// 배정밀도 데이터
	double doubleNumber1;
	double doubleNumber2;

	// 합계(추가 변수)
	int sum;
	int sub;

public:
	
	// 일단은 "데이터"에서 이 자료들을 어떻게 쓸지 모르겠으니까 비워둡시다
	// 나중에 쓸 일 있으면 함수 작성

	// 이 클래스의 존재의의 : 내부에 있는 데이터를 외부에서 못 보게 하기(숨기기)
	// 하지만 상속받으면 그 클래스에서는 데이터를 쓸 수 있게 하기

	// --------------------------------------------------------

	// 함수는 없어도 생성자는 만듭니다

	Data()
	{
		integer1 = 0;
		integer2 = 0;
		singleNumber1 = 0;
		singleNumber2 = 0;
		doubleNumber1 = 0;
		doubleNumber2 = 0;
		sum = 0;
		sub = 0;
	}
};
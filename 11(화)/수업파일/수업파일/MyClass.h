#pragma once
#include <iostream>

// 따라서, 포인터와 상수의 조합만으로는 구조체에서 보안을 유지하기가 힘들다
// 동시에 쓰는 입장에서도 어떤 변수는 써도 되고, 어떤 변수는 안된다는 걸 외워야 되니까
// → 불편하다. 그리고 위험하다

// → 그래서 c++에서는 구조체를 대신하기 위해서 새로운 문법, 개념을 만들었다

// 프로그램 내에서 부분 집합처럼 존재하는, 하지만 main()와는 분리된 독립 개체
// 이 안에 변수도 있고, 함수도 있고, 아무튼 개발자가 지정하는 "동작하기 위한 모든 것"
// 그 모두가 포함되는 가상의 범위를 c++에서는 

// Class(클래스) 라고 한다 : 변수 + 함수 + 클래스가 프로그램에 있기 위한 추가 문법

// --------------------------------------------------------------

// 클래스의 작성 사례

class MyClass // 클래스의 선언 : class 클래스이름
{
private: // 클래스와 함께 나온 문법, 접근 지정자
	// private : 이 밑으로 적인 코드는(다른 접근 지정자가 또 나오지 않는 한)
	//			 클래스와 무관한 곳에서(예를 들면 main함수)볼 수 없다
	//			 볼 수 없으므로 함수도 호출 못한다. 변수도 수정 못 한다
	//			 다시 말해서 클래스 자신만 쓸 수 있다

	// 클래스에 들어갈 수 있는 것
	// (당연히) 변수
	
	int a = 100;
	float f = 88.8f;
	int id = 77777;

	// 함수
	
	int Add(int x, int y); // ← 함수 선언 가능
	void ShowFloat(float z)  // ← 함수 정의도 가능
	{
		std::cout << z << std::endl;
	}

public:
	// public : 이 밑에 있는 코드는 클래스와 무관한 곳에서도 부를 수 있다

	// 퍼블릭도 프라이빗과 마찬가지로 변수, 함수 작성 가능

	int xx = 567;
	int Mult(int x, int y);

	// private에서 작성된 코드는 여기서는 쓸 수 있다
	// (여기도 클래스니까)

	// 그래서 private에 있는 데이터를 사용하는 함수만 여기에 작성을 해두면
	// private은 그대로 두고, public에서 호출용 함수만 쓸 수 있다

	// 예 : private에 있는 showFloat 함수를 쓸 수 있도록 하는 public의 호출용 함수

	void CallshowFloat(float z2) // 매개변수를 하나 받고
	{
		ShowFloat(z2); // private의 함수를 호출하면서 매개변수를 그대로 토스
	}

	// 다른 예 : id를 수정할 수 없고, 볼 수만 있도록 하는 방법
	// int로 반환되는 함수를 만든다
	int ID() { return id; }
	// 실행하면 private에 있는 id를 컴퓨터에게 전달하는 게 유일한 목적인 함수
	// id를 마치 상수처럼 열람만 할 수 있게 해주는 것이 존재 의의

	// 선언된 함수를 정의하는 방법은 MyClass.cpp 파일에서 

	// 또 다른 예 : id를 열람은 할 수 없는데, 수정만 할 수 있게 하는 방법

	void SetID(int value) {id = value;}
	// 오직 id를 수정하기 위해서만 존재하는 함수

	// 클래스를 실제로 쓰고 호출하는 방법은 main이 있는 cpp 파일에서

	// ----------------------------------------

	// 이니시에이터 작성(선언)

	void Init(int _a, float _f, int _id, int _xx);
};
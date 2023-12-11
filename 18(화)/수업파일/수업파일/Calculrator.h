#pragma once
#include "Data.h"

class Calculrator : public Data // 데이터 클래스 상속받기
{
	// 변수는 작성할 필요가 없다(원본에 있으니까)

public: // 외부 호출 함수 작성용

	// 정수들을 사용한 사칙연산 만들기

	int Add(int x, int y);
	int Sub(int x, int y);
	int Mult(int x, int y);
	int Div(int x, int y);
	int Nam(int x, int y);

	// 소수를 사용한 사칙연산 만들기

	// * C++에서 이해하는 함수의 이름은 함수명의 첫 글자부터 매개변수 지정이 끝나는 곳까지
	// 다시 말해 Add의 대문자 A부터 맨 뒤의 ) 표시까지
	// * 함수를 작성하는 시점에서는 이 부분이 선언과 정의가 달라지지 않게 주의해야
	// * 한편 똑같은 일을 해야 할, 그러나 매개변수 환경이 다른 함수가 있을 때
	//	 일일이 다른 "함수면"을 적용해서 작성하면 사용할 때 귀찮으므로, C++에서 이해하는
	//	 함수의 이름의 특성(매개변수까지 명칭으로 이해)을 이용해서
	//	 같은 함수명에, 다른 매개벼수를 사용한 볅의 함수를 또 만들 수있다

	// 이렇게 다른 매개변수를 사용해 "같은 함수명"을 만드는 것을
	// 함수의 누적, 혹은 함수의 "오버로드"라고 한다(overload, overloading)

	float Add(float x, float y); // Add라는 함수명을 사용한 "소수" 더하기

	// int Add(float x, float y); // 자료형만 다른 건 C++에서는 같은 함수로 친다(사용불가)

	float Sub(float x, float y); // 같은 함수명에 소수 빼기
	float Mult(float x, float y);
	float Div(float x, float y);

	// -------------------------------------

	// 함수 오버로드의 또 다른 응용 : 매개변수의 종류에 이어 매개변수의 개수

	int Add(int add); // 매개변수 한 개짜리 더하기

	// 테스트용
	int Add(int x, int y, int z); // 매개변수 세 개짜리

	int Add(float x, float y, float z); // int인데 float 세 개 받는 함수

	int Sub(int _sub);

	// 이렇게, 함수 오버로드를 사용하면 매개변수의 숫자에도, 매개변수의 형식에도 변화를 줄 수 있다

	// 해보기 : 매개변수 한 개짜리 누적 빼기, 누적 곱하기, 누적 나누기
	//		    정수 ver, 소수 ver도 만들어봅시다

	// -------------------------------------

	Calculrator()
	{
		// 계산기를 만들면 원본 데이터도 같이 생성
		Data();
	}
};
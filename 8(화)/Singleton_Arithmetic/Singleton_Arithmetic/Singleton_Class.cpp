#include "Singleton_Class.h"

// instance를 nullptr로 초기화
Singleton_Class* Singleton_Class::instance = nullptr;

// 생성자
Singleton_Class::Singleton_Class() {}

// 소멸자
Singleton_Class::~Singleton_Class() {}

// 연산 데이터 클래스 호출 후 출력
void Singleton_Class::ArithmeticZip()
{
	Add(x, y);
	Sub(x, y);
	Mult(x, y);
	Div(x, y);
	Remainder(x, y);

	cout << "모든 연산이 끝났습니다" << endl;
}

// 사용이 끝난 Singleton의 instance 삭제
void Singleton_Class::Delete()
{
	delete instance;
}
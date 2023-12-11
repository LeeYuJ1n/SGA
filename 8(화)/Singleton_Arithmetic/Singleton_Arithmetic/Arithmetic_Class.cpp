#include "Arithmetic_Class.h"

using namespace std;

// instance를 nullptr로 초기화
Arithmetic_Class* Arithmetic_Class::instance = nullptr;

// 생성자
Arithmetic_Class::Arithmetic_Class() {}

// 소멸자
Arithmetic_Class::~Arithmetic_Class() {}

// 더하기
void Arithmetic_Class::Add(int _x, int _y)
{
	x = _x;
	y = _y;

	cout << "입력한 첫 번째 숫자 : " << x << endl;
	cout << "입력한 두 번째 숫자 : " << y << endl;
	cout << "두 수의 더하기 결과 : " << x + y << endl;
}

// 빼기
void Arithmetic_Class::Sub(int _x, int _y)
{
	x = _x;
	y = _y;

	cout << "입력한 첫 번째 숫자 : " << x << endl;
	cout << "입력한 두 번째 숫자 : " << y << endl;
	cout << "두 수의 빼기 결과 : " << x - y << endl;
}

// 곱하기
void Arithmetic_Class::Mult(int _x, int _y)
{
	x = _x;
	y = _y;

	cout << "입력한 첫 번째 숫자 : " << x << endl;
	cout << "입력한 두 번째 숫자 : " << y << endl;
	cout << "두 수의 곱하기 결과 : " << x * y << endl;
}

// 나누기
void Arithmetic_Class::Div(int _x, int _y)
{
	x = _x;
	y = _y;

	cout << "입력한 첫 번째 숫자 : " << x << endl;
	cout << "입력한 두 번째 숫자 : " << y << endl;
	cout << "두 수의 나누기 결과 : " << x / y << endl;
}

// 나머지
void Arithmetic_Class::Remainder(int _x, int _y)
{
	x = _x;
	y = _y;

	if (x == 0 || y == 0)
	{
		cout << "0으로는 나눌 수 없습니다. 다시 입력해주세요." << endl;
	}
	else
	{
		cout << "입력한 첫 번째 숫자 : " << x << endl;
		cout << "입력한 두 번째 숫자 : " << y << endl;
		cout << "두 수의 나머지 결과 : " << x % y << endl;
	}
}

// 다 쓴 isntance 삭제
void Arithmetic_Class::Delete()
{
	delete instance;
}
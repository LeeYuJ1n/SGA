#include "Calculator.h"

// 생성자 겸 첫 번째 실행했을 때 생기는 일
Calculator::Calculator()
{
	// 계산기 실행을 안내
	cout << "무한 누적 계산기를 시작합니다" << endl;
	cout << endl;
	
	cout << "첫 번째 숫자를 입력해주세요 : ";
	cin >> record; // 저장용 변수를 처음으로 할당받기

	// 두 변수 미리 초기화 (필요는 없는데 그냥 속 편하려고)
	input = 0;
	opCode = ' ';
}

// 주 실행 함수
void Calculator::Run()
{
	// 여기서 무한으로 계산기를 돌릴 생각
	while (true)
	{
		cout << endl;

		cout << "현재까지의 숫자에 추가로 연산한 숫자를 입력해주세요" << endl;
		cout << "입력 : ";
		cin >> input;

		cout << "연산하려는 계산을 연산자로 입력해주세요" << endl;
		cout << "입력 : ";
		cin >> opCode;

		switch (opCode)
		{
		case '+':
			Add(input); // 입력받은 숫자를 넣어서 더하기
			break;

		case '-':
			Sub(input);
			break;

		case '*':
			Mult(input);
			break;

		case '/':
			Div(input);
			break;

		case '%':
			Remain(input);
			break;
		}
	}
}

// 연산들 (출력까지)
void Calculator::Add(int value)
{
	cout << endl;

	cout << record << "와" << value << "의 합은 : " << record + value << "입니다" << endl;

	// 값을 실제로 반영
	record += value;
}

void Calculator::Sub(int value)
{
	cout << endl;

	cout << record << "와" << value << "의 빼기는 : " << record - value << "입니다" << endl;

	// 값을 실제로 반영
	record -= value;
}

void Calculator::Mult(int value)
{
	cout << endl;

	cout << record << "와" << value << "의 곱하기는 : " << record * value << "입니다" << endl;

	// 값을 실제로 반영
	record *= value;
}

void Calculator::Div(int value)
{
	if (value != 0)
	{
		cout << endl;

		cout << record << "와" << value << "로 나누면 : " << record / value << "입니다" << endl;

		// 값을 실제로 반영
		record /= value;
	}
	else
	{
		cout << endl;

		cout << "0으로는 나눌 수 없습니다" << endl;
	}
}

void Calculator::Remain(int value)
{
	if (value != 0)
	{
		cout << endl;

		cout << record << "와" << value << "로 나머지는 : " << record % value << "입니다" << endl;

		// 값을 실제로 반영
		record %= value;
	}
	else
	{
		cout << endl;

		cout << "0으로는 나눌 수 없습니다" << endl;
	}
}


void Run(); // 실행이라는 함수 하나만 밖으로 공개
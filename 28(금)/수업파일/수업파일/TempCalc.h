#pragma once
#include <iostream>

using namespace std;

// 템플릿이 적용된 사칙연산 계산기

template <typename T>
class TempCalc
{
public:
	T input1;
	T input2;

	TempCalc()
	{
		input1 = 0;
		input2 = 0;
	}

	void input()
	{
		cout << endl;
		cout << "첫 번째 숫자 입력 : ";              // 첫 번째 숫자 입력 묻기
		cin >> input1;                              // input1에 첫 번째 숫자 넣기

		cout << endl;
		cout << "두 번째 숫자 입력 : ";              // 두 번째 숫자 입력 묻기
		cin >> input2;
	}

	// 모든 걸 public으로 만들어봅시다 (시간상, 편의상)

	// 변수 2개

	// 입력받기
	
	// 더하기
	void Add()
	{
		cout << "[계산 결과 : 더하기 ] " << input1 << " + " << input2 << " = " << input1 + input2 << endl;
	}
	
	// 빼기
	void Sub()
	{
		cout << "[계산 결과 : 빼기 ] " << input1 << " - " << input2 << " = " << input1 - input2 << endl;
	}
	
	// 곱하기
	void Mult()
	{
		cout << "[계산 결과 : 곱하기 ] " << input1 << " * " << input2 << " = " << input1 * input2 << endl;
	}
	
	// 나누기
	void Div()
	{
		if (input1 == 0 || input2 == 0)
		{
			cout << "계산 불가능" << endl;
		}
		else
		{
			cout << "[계산 결과 : 나누기 ] " << input1 << " / " << input2 << " = " << input1 / input2 << endl;
		}
	}
	
	// 나머지 함수도 ? ← T가 소수일 경우가 있으므로 아래 연산이 오류를 발생시킨다
	// 해결책 1. (제일 좋은 것) 그냥 만들지 않는다
	// 해결책 2. 정수용 함수를 따로 하나 만든다 (아래 함수는 공용 함수)

	// 해결책 2의 실행 1. 정수용 클래스를 따로 하나 더 만든다
	//                   장점 : 확실하다, 호출이 편하다
	//                   단점 : 해당 특수 클래스를 공용처럼 쓰려면 사실상 전체 재작성이 필요

	// 해결책 2의 실행 2. 클래스르 안에 작은 함수 하나 실행용 클래스를 또 만든다
	//                   그리고 그 클래스를 특수화하면 된다
	//                   장점 : 작성이 편하다
	//                   단점 : 호출이 아마 번거로울 것

	// 나머지
	void Remains()
	{
		// 공통 실행 사항 : 정수 아니면 나머지 무효
		cout << "정수가 아닌 숫자 형식으로는 나머지 도출이 무의미합니다" << endl;
	}
	// 정수용 함수 : 별도로 정의할 필요가 있다
	//              어디서부터? → 템플릿의 자료형 적용부터
	//              따라서 → class 코드 밖으로 나가야 한다

	// -------------------------------------------------------------------

	// 여기는 아직 클래스 안
	// 이곳에 작은 클래스를 하나 더 만들자

	class GetRM
	{
	public: // 함수 호출을 할 수 있게 public
		// 아래 함수에 매개변수를 넣어야 호출할 때 의도한 결과가 나온다
		void Remain(int _x, int _y)
		{
			// 확실하게 하기 위해서 int화
			int x = (int)_x;
			int y = (int)_y;

			if (y != 0)
			{
				cout << "계산 불가능" << endl;
			}
			else
			{
				cout << "[계산 결과 : 나누기 ] " << x << " / " << y << " = " << x / y << endl;
			}
		};
	};

	// 이렇게 위처럼 만들고 나니... 이미 int가 대응이 될 것
	// 클래스 속 클래스(형변환 등의 변수 추가)를 잘 활용하면 
	// 템플릿 클래스를 쓰더라도 다양한 자료형에 유연하게 대응 가능

	// ** 밑에 있는 코드는 이론의 영역에서 이해하거나
	// ** 클래스 내에서 또 다른 제2, 제3의 임시 자료형이 필요할 때 활용 가능

	// ***********************************************************

	// 클래스 속 클래스에도 템플릿이 적용된다
	template <typename TT>
	class GetRM_T
	{
	public:
		void Remain()
		{
			cout << "나머지 불가" << endl;         // 코드 작성
		}
	};

	template <>      // 임시 자료형을 지정하지 않고
	class GetRM_T<int>            // ← 자료형을 int로 지정
	{
	public:
		void Remain()
		{
			// 연산용 전용 변수 (확실하게)
			int x = (int)input1;
			int y = (int)input2;

			if (y != 0)
			{
				cout << "계산 불가능" << endl;
			}
			else
			{
				cout << "[계산 결과 : 나누기 ] " << input1 << " / " << input2 << " = " << input1 / input2 << endl;
			}
		}
	};

	// ***********************************************************

	// -------------------------------------------------------------------
};

/*

// 헤더 안, 클래스 밖 : 일반적으로는 쓰이지 않는 공간
// 하지만 템플릿 클래스가 쓰일 때는 함수의 별도 정의가 필요할 때
// 유용하게 쓰이는 공간

// 여기서 정수가 들어왔을 때만 적용되는 전용 템플릿 클래스 함수 작성
template <>        // 여기는 선언이 같거나 비슷하다
// 다만 완전히 똑같은 선언은 불가능 1. 재정의로 인한 문제
//                                2. 전용 클래스 코드를 쓰고 있을 때
//                                → 안 쓰는 임시 자료형은 그냥 <>에서 빼면 된다 = 선언도 달라지고, 낭비도 없어지고
class TempCalc<int>
{
public:
	// 모든 걸 public으로 만들어봅시다 (시간상, 편의상)
	
	// T가 적용되었던 변수도 int로 다시 작성해주고 (필수)
	int input1;
	int input2;

	// (권장 사항) 원본에 있던 다른 함수도 재정의가 되면 좋기는 하다
	// * 간단히 말하면, "특정 자료형에 대응한 클래스를 아주 하나 더 만들면 가장 좋다"
	// 이렇게 특수한 자료형에 대응해서 실행되는 템플릿 클래스, 혹은 템플릿 함수를 (함수에도 적용됨)

	// → 템플릿의 특수화라고 한다 (specialization, 특화)

	// 입력받기
	void input()
	{
		cout << endl;
		cout << "첫 번째 숫자 입력 : ";              // 첫 번째 숫자 입력 묻기
		cin >> input1;                              // input1에 첫 번째 숫자 넣기

		cout << endl;
		cout << "두 번째 숫자 입력 : ";              // 두 번째 숫자 입력 묻기
		cin >> input2;
	}

	// 더하기
	void Add()
	{
		cout << "[계산 결과 : 더하기 ] " << input1 << " + " << input2 << " = " << input1 + input2 << endl;
	}

	// 빼기
	void Sub()
	{
		cout << "[계산 결과 : 빼기 ] " << input1 << " - " << input2 << " = " << input1 - input2 << endl;
	}

	// 곱하기
	void Mult()
	{
		cout << "[계산 결과 : 곱하기 ] " << input1 << " * " << input2 << " = " << input1 * input2 << endl;
	}

	// 나누기
	void Div()
	{
		if (input1 == 0 || input2 == 0)
		{
			cout << "계산 불가능" << endl;
		}
		else
		{
			cout << "[계산 결과 : 나누기 ] " << input1 << " / " << input2 << " = " << input1 / input2 << endl;
		}
	}

	void Remain() // 나머지 (정수 전용)
	{
		if (input1 == 0 || input2 == 0)
		{
			cout << "계산 불가능" << endl;
		}
		else
		{
			cout << "[계산 결과 : 나누기 ] " << input1 << " / " << input2 << " = " << input1 / input2 << endl;
		}
	}
};
*/
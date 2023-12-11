#pragma once
#include "Human.h"

// 학생을 나타내는 클래스

// 키도 있을 거고 체중도 있을 거고 취미

// "학생도 인간이다"를 코드로 구현할 수는 없을까? → 가능하다! C++이라면

// 클래스의 상속

class Student : public Human // class 클래스명 : public 클래스명
	// 원래는 위에 public 대신 private이 와도 되지만, 현실적으로 public이 거의 쓰인다
	// 이유 : 여기서 private을 쓰면, 원본에서 public이었던 게 여기서 private이 된다
	// 		  → 원본에 있는 거의 모든 데이터를(자기 건데도) 자기가 못 부르게 되니까
{
	// 위처럼 적으면 Student는 Human의 모든 속성을 공유하는 파생 클래스(breached)가 된다
	// 자식 클래스(child), 상속된 클래스(inherited), 종속 클래스(slave)등으로도 불린다

private:
	// 학생을 나타내는 변수
	// 따로 적지 않는다(파생 클래스는 원본 클래스의 모든 데이터를 같이 갖는다)
	
	
	// 학생 고유의 변수(인간에겐 없고 학생이어야 가지는 변수)
	int schoolCode; // 코드로 나타낸 학교명
	int grade; // 학년
	float averageScore; // 평균학점

public:
	// 기본 생성자
	Student()
	{
		Human(); // 인간 긴본 생성자 사용
		schoolCode = 0;
		grade = 0;
		averageScore = 0;
	}

	// 생성자
	Student(int _age, int _gender, float _height, float _weight, int _hobby, int _school, int _grade, float _score)
		: Human(_age, _gender, _height, _weight, _hobby)
	{
		// 학생도 인긴아니, 먼저(혹은 같이)인간도 만들어져야 한다
		// Human(_age, _gender, _height, _weight, _hobby);

		schoolCode = _school;
		grade = _grade;
		averageScore = _score;
	}

	// 학생 출력용 함수
	void PrintMe()
	{
		// 이 코드 처음 작성 시 오류가 난 이유는 : age가 private이라서 
		std::cout << "내 나이는 : " << age << ", 그리고 내 학년은 : " << grade << "학년 입니다" << std::endl;
		// this->GetAge() 사용가능, Human이 protected가 적용되면 age 접근 가능
		// 이것이 클래스 외부 참조와, 상속의 가장 큰 차이

		// 학생도 인간이니까 Human이 protected로 적용된 후,
		// Human의 비공개된 모든 함수까지 여기서 호출 가능

		this->ImOut();
		this->PrivateLife();
	}

	// private : 자기 클래스 바깥의 어느 누구도 볼 수 없는 데이터
	//			 파생 클래스도 절대 예외가 아니다
	 
	// 그런데 파생 클래스면 데이터를 갖고 있는 만큼은 봐야지 않을까?

	// 그래서 파생 클래스가 원본 클래스의 데이터에 접근할 수 있도록 하는, 3번쨰 접근 지정자가 있다
	// -> Human.h에 적용
};
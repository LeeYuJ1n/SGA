#pragma once
#include <iostream>
#include <Windows.h>

// 헤더
#include "Arithmetic_Class.h" // 사칙연산 데이터

using namespace std;

class Singleton_Class : public Arithmetic_Class
{
private:
	// private에 생성자와 소멸자 생성
	Singleton_Class();      // 생성자
	~Singleton_Class();     // 소멸자

	// 실체 전달용 포인터 인스턴스
	static Singleton_Class* instance;

public:
	static Singleton_Class* Get()
	{
		// 현재 instance가 없다면 실행
		if (instance == nullptr)
		{
			// 자기 자신의 instance를 생성
			instance = new Singleton_Class();
		}

		// instance 반환
		return instance;
	}
	
	// 연산 데이터 클래스를 호출 후 출력
	void ArithmeticZip();

	// instance 데이터 메모리 공간 해제
	void Delete();
};


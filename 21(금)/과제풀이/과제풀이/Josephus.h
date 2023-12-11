#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Josephus
{
private:
	// 요세푸스 문제에 필요한 변수

	// 1. 배열(벡터)
	vector<int> firstData; // 처음 배열
	vector<int> answer;    // 답이 들어갈 배열

	// 2. 입력을 받아서 넣을 변수
	int sizeOfArray; // 처음 벡터의 크기
	int interval;    // 간격

	// 2-1. 계산용 변수(필요함)
	int next;

	// 3. 필요 없는데 그냥 넣고 싶어서 넣는 변수
	// * 코딩 테스트처럼 속도가 중요할 때는 이런 거 만들지 맙시다
	// * 대신 개인적인 프로젝트라면 이렇게 장난을 쳐보는 것도 좋습니다
	int count; // 현재 계산 몇 번째인가

	// 배열 보여주기는 함수를 미리 만들어서 여러분 호출
	void PrintVector(vector<int> data);

public:
	// 함수 부르기
	void Start();

	// 생성자 (입력을 따로 받을 거라 생성자에서 뭘 줄 필요가 없다
	Josephus()
	{
		count = 1; // 첫 번째 계산이니까 1
		next = 0;  // 다음에 지울 순번

		// 0 초기화
		sizeOfArray = 0;
		interval = 0;
	}
};


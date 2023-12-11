#pragma once
#include "DequeClass.h"
#include <iostream>
#include <vector> // 벡터 기능

using namespace std;

void DequeClass::Start()
{
	// < 디큐(혹은 "데크) 선언하기 >
	deque<int> dq; // 정수의 디큐

	// < 추가하기 >
	dq.resize(10); // 크기를 지정해주고 (이런 방법도 있으니까)

	for (int i = 0; i < dq.size(); ++i)
	{
		dq[i] = i + 1;         // 디큐는 [] 사용 가능
		 
		cout << dq[i] << endl; // 출력까지 한번에
	}

	// 원소 추가하기 (개별)
	dq.push_back(11); // push_back 가능
	// pop_back, insertm emplacem erase 모두 가능

	// 더불어서 아래 두 함수가 *기본적으로* 사용 가능
	// 사용상의 차이는 이 두 함수가 결정적

	dq.push_front(-1); // push_front : 디큐 배열의 맨 처음"의 앞"에 새 구성요소를 추가

	dq.pop_front();    // pop_front : 디큐 배열의 맨 앞의 구성요소를 없애는 함수
	dq.pop_front();
	dq.pop_front();

	for (int i = 0; i < dq.size(); ++i)
	{
		cout << dq[i] << endl; // 출력까지 한번에
	}

	vector<int> vc;
	vc.push_back(1); // 벡터는 push_front가 아예 없다(C++에서는)

	// ------------------------------------------

	// dq의 추가 특징 (C++에서)
	// : 벡터와 마찬가지로, push, insert, emplace, erase 실행 시
	//   반복자 무효화 현상이 일어난다 (*주의!)

	// 1. 사본 형셩의 가능성 때문에
	//    → (사본 형성이 잘 안 일어나는 거지, 절대 안 일어나는 건 아니다)
	// 2. 배열 앞에도 구성요소가 추가될 수 있기 때문에
	//    → (= begin의 의미가 자꾸 달라진다)

	// --------------------------------------------

	// 디큐는 자료 관리 능력이 뛰어난, 벡터보다 개선된 자료 구조이지만,
	// 메모리 효율이 낮아서 게임 개발에서는 비교적 덜 선호된다
	// (써야 되면 주로 벡터 혹은 더 자주 선택되기론 리스트)
}
#pragma once

// 구조체 내에서 (c의 기본 문법만으로) 상수 표현하기
// () 조건이 없으면 현재의 c, 혹은 c++에서 물려받은 기능을 써도 되니까

// 전통적인 구조체

struct Character
{
	int notID; // 사실은 id가 맞지만, 다른 이가 쓰지 말라고 고의로 이름을 이렇게 정함
	const int* id = &notID; // id 생성

	// 함수, 혹은 c++의 다른 기능과 동일한 다른 문법 안 씀
};

// 구조체 변수
Character c1;
Character c2;

// 나머지는 메인에서
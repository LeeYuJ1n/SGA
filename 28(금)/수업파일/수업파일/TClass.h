#pragma once
#include <iostream>
#include <vector>                 // 벡터 로딩
#include <string.h>               // 스트링 로딩

using namespace std;

// 클래스 템플릿 이용 방법
// : 기본적으로는 템플릿 함수와 비슷
// 차이점 : 클래스 이름 위에 미리 템플릿을 선언

template <typename T>

class TClass
{
protected:
	T data;

public:
	// 편의상 함수 접근은 모두 public으로

	TClass() { data = 0; }        // 기본 생성자

	TClass(T _data)               // 생성자
	{
		data = _data;
	}

	// 템플릿 클래스를 정의하려면?
	// 그냥은 정의 불가능 : 템플릿 자체에 범위가 적용되기 때문에
	//                     (템플릿 선언 안에서 이루어진 코드는 밖에서 접근 불가)
	
	// 정의할 때도 템플릿을 써줘야 한다
	// 단, 함수 제외! 함수는 헤더에서 정의까지 해야 한다 (템플릿이라면)
	// 이런 식으로 헤더에서 모든 정의를 끝마치는 클래스를 인라인 클래스라고 한다

	void print()
		// 템플릿 클래스에서 함수는 별 다른 조치가 더 없으면 헤더에서 정의해야 한다
		// 헤더에서 함수 정의는 권장 사항이 아니지만 어쩔 수 없다
	{
		cout << data << endl;
	};
};


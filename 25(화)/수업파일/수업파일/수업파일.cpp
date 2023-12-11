#include <iostream>
#include "ListClass.h"
#include "DequeClass.h"

int main()
{
    // 벡터에 이어서 다른 동적 배열 사용
    
    // List : 불연속적 자료에 상관관계를 부여하여 구축한 자료 구조 → (아무 데나 있는 자료에 순번을 매긴 동적 배열)
    // Deque : 양극성 큐 (double ended queue) → 양쪽에 자료를 추가할 수 있도록 누적 유형 자료 구조 (위나 밑에 데이터를 추가할 수 있도록 만든 동적 배열)

    // 현 C++에서 이 동적 배열들의 특징 : 아무튼 코드를 쓰는 입장에서는 용도에 따른 함수 사용이 거의 같다
    //                                  → 벡터를 알면, 벡터에 있는 함수를 쓸 수 있으면 이 둘도 자동으로 쓸 수 있다

    ListClass* lc = new ListClass();
    // lc -> Start();

    DequeClass* dc = new DequeClass();
    dc -> Start();
}
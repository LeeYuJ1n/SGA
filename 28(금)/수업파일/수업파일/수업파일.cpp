#include <iostream>
#include "TClass.h"
#include "TempCalc.h"        // 실습 : 템플릿이 적용된 사칙연산 계산기

int main()
{
    // 템플릿 심화 : 클래스에 템플릿을 적용했을 때 생각할 수 있는 것들
    //              → ( 구조체에도 같이 적용 가능 )

    // 이를 클래스 템플릿, 혹은 템플릿 클래스

    // 클래스 템플릿 설명 : TClass에서

    // -------------------------------------------------------------

    // 클래스 템플릿 사용해보기

    TClass<int>* tc1 = new TClass<int>(897);
    // 인스턴스 선언 시 어느 자료형의 형태로 쓸 것인지 <>로 선언 같이 해주기
    // → 벡터, 리스트와 같은 원리 (즉 벡터와 리스트도 템플릿이 적용되었던 것)

    tc1->print();        // 만들어진 인스턴스에서는 함수를 평소처럼 쓰면 된다

    TClass<float>* tc1f = new TClass<float>(5.4f);

    tc1f->print();

    // ---------------------------------------------------------------

    // 실습 : 템플릿이 적용된 사칙연산 계산기

    TempCalc<int>* intTc1 = new TempCalc<int>();
    
    intTc1->input();
    intTc1->Add();
    intTc1->Sub();
    intTc1->Mult();
    intTc1->Div();
    // intTc1->Remains(); ← 주석 처리

    // 클래스 속 작은 클래스에는 그에 맞는 인스턴스가 더 필요하다
    // 중첩 클래스에 접근하는 법 → 클래스이름::중첩클래스이름
    
    // 같은 문법을 사용하는 예시 : vector의 반복자

    // GetRM ← 클래스 속에서 만들어진 중첩 클래스는 바깥 클래스를
    //         거치지 않고는 직접 접근이 불가능하다

    TempCalc<int>::GetRM* inst1 = new TempCalc<int>::GetRM();
    // 그리고 이렇게 인스턴스를 구분하고 보니 확인 가능한 한 가지 추가 사실
    // → intCalc와 inst1은 다른 인스턴스 = 안에 있는 변수도 달라졌다
    //   그런데 inst1에서 그냥 함수를 호출하면 ? → 의도한 결과가 나오지 않는다

    // 그래서 이 문제를 해결하기 위해서는 inst1이 만들어진 후 intCalc의 변수를 받거나,
    // 처음부터 함수가 매개변수를 받으면 된다

    // 하여 계산기에 나머지 도출용 클래스를 사용 시험
    inst1->Remain(intTc1->input1, intTc1->input2);
    // 겟터가 있는 편이 더 좋았겠지만 편의상 변수 직접 호출

    TempCalc<float>* floatTc2 = new TempCalc<float>();

    // floatTc2->input();
    // floatTc2->Add();
    // floatTc2->Sub();
    // floatTc2->Mult();
    // floatTc2->Div();

    // ---------------------------------------------------------------
}
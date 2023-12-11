#include <iostream>
#include "MySingleton.h"

// 싱글턴 약어 매크로
#define SINGLETON MySingleton::Get()

using namespace std;

// 정적 선언을 C++ 응용하는 방법 중 대중적인 사례 한 가지

// → 정적 선언은 함수나 구조체, 클래스 등에도 사용할 수 있다
//   (전역 함수=main 밖 함수 등에서 써 봤자 의미 없으니 그동안 안 쓴 것뿐)

// → 클래스가 좀 더 필수적으로 쓰여야 할 환경에서...
//   해당 클래스가 마치 전역 변수인 것처럼 (그러나 진짜 전역은 아닌)
//   그리고 별도의 전역변수 선언 없이 어디서나 호출되어서 쓰여야 하는 게 있다면?

// → 그런 클래스를 정적으로 만들어서 호출해도 좋지 않을까?
//   그런 정적 클래스를 만들어서 호출할 수 있을까? 있다!

// → 정적 클래스를 만든 후 별도의 변수 지정 없이 불러내는 기법을 "싱글턴"이라고 한다 (singleton, 외동이, 외툴이, 단독자)

void Change(); // 변화라는 이름의 함수를 선언

int main()
{
    // 싱글턴을 직접 써보자

    // 싱글턴은 별도의 인스턴스 (포인터 포함) 선언이 필요없다
    // 그냥 클래스 범주 :: 안으로 들어가서 Get함수를 불러오면 바로 결과물(instance)이 나온다
    // 어디서든 똑같은 instance에 접근 가능

    // 싱글턴을 쓸 때, #define 처리를 통해서 약어를 지정해두면 타자가 좀 더 편해지기도 한다

    MySingleton::Get()->x = 10; // 싱글턴 인스턴스의 변수를 호출, 수정
    cout << MySingleton::Get()->x << endl; // 출력

    // 다른 함수에서 instance에 접근 후 숫자를 바꾸고 출력
    Change();
    cout << MySingleton::Get()->x << endl;
    Change();
    cout << MySingleton::Get()->x << endl;

    // 아래 코드는 매크로로 호추
    SINGLETON->Init(100, 200);
    cout << SINGLETON->x << endl;
    cout << SINGLETON->y << endl;

    SINGLETON->Add(5, 5);
    cout << SINGLETON->x << " + " << SINGLETON->y << " = " << SINGLETON->result << endl;

    SINGLETON->Sub(5, 5);
    cout << SINGLETON->x << " - " << SINGLETON->y << " = " << SINGLETON->result << endl;

    SINGLETON->Mult(5, 5);
    cout << SINGLETON->x << " * " << SINGLETON->y << " = " << SINGLETON->result << endl;

    SINGLETON->Div(5, 5);
    cout << SINGLETON->x << " / " << SINGLETON->y << " = " << SINGLETON->result << endl;
}

void Change()
{
    MySingleton::Get()->x++;
}
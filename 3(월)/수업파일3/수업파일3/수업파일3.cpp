﻿#include <iostream>

void ShowNumber(); // 함수의 선언 방법(자세한 설명은 맨 밑어)

// 함수, 매개변수, 지역변수, 전역변수(+헤더 파일)

// 함수, 매개변수 : 컴퓨터의 코드를 개발자가 임의로 행동단위에 따라 구분하여 분리한 것
// 개발자의 의사에 따라 컴퓨터의 기능을 독립적으로 정의한 것

// 프로그래밍을 한다는 것을 라면 끓이기에 비유한다면(라면 우화)

// 라면을 사고, 냄비에 물을 끓이고, 라면을 넣고, 스프를 넣고 3분 뒤에 먹는다...는 것을 코드로 구현한 거라고도 본다

// 이 때, "냄비에 물을 끓이고, 라면을 넣고, 스프를 넣고, 3분 기다린다"는 과정을 하나의 이름으로 묶는다
// 이름하여 "라면 끓이기"

// → 라면을 사고, 라면을 끓이고, 라면을 먹는다...로 평소에는 줄여서 이해하고,
// 라면을 어떻게 끓이는데? 에서 자세한 행동을 지정해서 이해할 수 있게 된다

// -----------------------

// 위 우화처럼 C++에서 코드를 따로 묶어서 별도의 이름으로 정의하는 것
// : 함수(=기능, 행동, 원문은 funcion)

// 함수를 실제로 만드는 법

// 기본적으로 변수와 비슷하다
// 1. 자료형 : 함수 속에 있는 코드를 수행했을 때, 결과물이 존재하는지 여부와, 그 결과물의 자료형
//             int 함수 : 이 함수를 실행하면 정수가 하나 나와야 한다는 뜻
//             float : 실행 끝에 소수가 하나 반드시 나온다는 뜻(개발자가 주겠다고 약속했다는 뜻)

//             (*중요) void 함수 : 실행을 했을 때, 결과가 나오지 않는다는 뜻(개발자가 아무 결과도 내지 않겠다고 선언)
//             * void 함수는 계산 결과보다는 과정이 중요할 때 쓴다(라면이 중요한 게 아니라 끓이는 중간의 행동이 더 중요하다)

// 2. 함수명 : 개발자가 정한, 함수의 이름, 호출에 쓴다

// 3. 매개변수 : 함수명 뒤에 ()를 붙여서 표시, 이 표시가 C++에서 함수가 변수와 표기상 다른 점
//               이 함수를 실행할 때, 호출 시마다 달라져야 하는 부분이 있는지를 확인하고,
//               호출할 때, 이 달라져야 할 부분이 이번에는 어떻게 실행되어야 하는지를 사용자에게 요구
//               매개변수가 없어도 ()표시는 (안에 아무 것도 안 적고) 꼭 붙여야 한다

// 4. 실제코드 : 실제로 수행할 코드

// 5. (자료형이 있을 경우) 코드의 마루리는 'return 결과값' 으로 표현해야 한다
//    void 함수라도 (굳이 그럴 필요 없지만) return을 쓰면 함수를 마친다(함수 강제종료 시에 유용)

// 작성 사례

// 정수 두 개를 first, second라는 이름으로 받아서, 덧셈을 실행하고, 결과를 컴퓨터에게 전달하는 함수

int Add(int first, int second)
{
    int result = first + second; // 두 수를 더한 결과를 저장
    return result; // 위에서 만든 결과를 컴퓨터로 전달
}
// 이 함수를 나중에 호출할 때, first, second의 값이 무엇이어야 하는지 지정
// 비유하면, 라면 끓일 때 몇 분 끓일지, 신라면 쓸지 삼양라면 쓸지를 미리 정하지 않고 그때그떄 다르게 지정

// 소수 두 개를 매개변수로 받아서, 뺄셈을 실행하고 리턴하는(컴퓨터에게 전달하는) 함수
float Sub(float first, float second)
{
    // 매개변수도 함수 안에서 ({} 안에서) 새로 만들어낸 변수로 친다
    // 다른 {}  안의 매개변수와 이름이 겹쳐도 된다(별도의 변수니까)
    // 한 함수에서 만든 매개변수를 다른 함수(다른 {})에서 부를 수 없다

    // 다시 말해, 여기서 부른 first는 이 함수의 float이지, 위 Add 함수의 int 변수가 아니다

    return first - second; // 별도의 변수 없이 그냥 연산을 수행해서 곧 바로 결과를 전달하는 것도 가능
}

int Mult(int first, int second)
{
    std::cout << first * second << std::endl;
    // 함수는 변수와 매개변수 처리만 하는 게 아니라, 개발자가 지정한 다른 코드라도 수행 가능
    // 결과나 연산과 완전히 별개로, 출력 등도 하려면 얼마든지 할 수 있다(물론 다른 기능도)

    std::cout << "나누기" << std::endl; // ← 함수와 관계없는 코드

    // *.....단, 함수의 목적을 생각할 때(행동에 따른 코드 분리)
    // 필요 없는 기능을 함수에 같이 넣는 것이 좋지는 않다
    // 함수는 자기 목적에 맞는 코드만 깔끔하게 갖고 있을 때 가장 좋다

    return first * second;
}

void Div(int first, int second)// void 함수 : 결과가 없는 함수
{
    // 함수와 매개변수는 자료형이 서로 달라도 괜찮다

    if (second != 0)
    {
        std::cout << first / second << std::endl;
    }
    
    // return;불필요
}

// void 함수가 있는 이유 : 활용법
// 이 함수는 결과를 보기 위한 것이 아니다, 과정이 더 중요한 경우
int x = 1000; // 전역 변수 작성
void ChangeX() // ()안에 아무 것도 없다 : 매개변수가 없다
{
    // 매개변수는 빈 ()를 씀으로써 없다고 해줄 수도 있다. 그러나 매개변숙 없어도 ()표시는 필수

    // 아래는 함수의 과정(함수가 단지 실행되어다는 이유만으로 수행하야 할 코드)

    std::cout << "x의 값을 지금부터 바꾸겠습니다!" << std::endl; // 정해진 문자 출력
    x = 99999; // x의 값을 정해진 숫자로 수정
    std::cout << x << std::endl; // x를 모니터에 출력

    return; // 겨로가가 나오지 않아도, "아무것도 없다는 결과 자체"는 컴퓨터에 전달 가능
    // 위 리턴 코드가 수행되는 시점에서 함수는 끝난다
    // return : 함수 강제 종료라고 생각해도 무방

    // 확인용 코드 : return 보다 밑에 있기 때문에 실행되지 않는다. 실행되면 안 된다
    std::cout << "이 코드는 보이면 안 됩니다!" << std::endl;

    // 위 함수에서, 전역변수 호출(접근 사용)
}

int main()
{
    // 함수를 사용하는 방법 : 일반적으로 변수처럼 그냥 호출

    // Add(); // 매개변수가 있어야 하는데 안 적으면 오류
    // Sub();
    // Mult();
    // Div();

    Add(10, 3);
    Sub(10, 3);
    Mult(10, 3);
    Div(10, 3);

    // 호출을 끝내면 컴퓨터는 값을 전달은 받지만, 변수처럼 따로 쓰지 않으면 아무것도 하지 않는다
    // a; ← 이것처럼

    // 결과가 있는 함수의 경우, 그 결과를 다시 데이터처럼 취급해서 다룰 수 있고, 그렇게 다뤄야 할 필요도 있다

    std::cout << Add(10, 3) << std::endl; // 덧셈 결과를 모니터에 출력
    std::cout << Sub(10, 3) << std::endl;
    std::cout << Mult(10, 3) << std::endl;
    // std::cout << Div(10, 3) << std::endl; // 여기서 에러가 나는 이유 : 컴퓨터가 값을 못 받아서

    ChangeX(); 
    // 함수를 호출만 했지만, 어차피 이 함수는 과정이 중요하므로, 결과는 컴퓨터가 받지도 않고 받을 필요도 없다
    // 
    // 호출 했다는 사실만으로도 과정은 수행된다 → 함수를 호출함으로써 사용하기

    // ----------------------------

    // 여기서도 전역 변수 수정 가능

    x = 10; // 가능

    // 함수끼리 지역 변수는?
    int a = 10;

    std::cout << a << std::endl; // main함수의 a를 쓸 수 있다
    // std::cout << b << std::endl; // 밑에 적은 함수 안의 b는 쓸 수 없다
    std::cout << x << std::endl; // 전역변수 x도 쓸 수 있다

    // main밑에 적은 함수 호출
    ShowNumber(); // 결과 : 숫자 출력
}

void ShowNumber()
{
    int b = 20;
    // std::cout << a << std::endl; // main함수의 a를 쓸 수 없다
    std::cout << b << std::endl; // 이 함수 안의 b는 쓸 수 있다
    std::cout << x << std::endl; // 전역변수 x도 쓸 수 있다

    // 함수 작성시 주의사항 :ㅈ완전히 새로운 변수를 main밑에서 만들지 말 것(C, C++ 한정)
    // main 최초 인식 시점에서 함수의 이름이 없으면 "없는 함수를 실행했다"고 컴퓨터가 잘못 생각하기 때문

    // 위 주의사항을 지키기 위한 팁 : main에서 밑에서 함수를 적어야 할 경우는
    // main보다 위에(가능하면 제일 위에) 함수의 이름과 자료형, 함수명, 매개변수까지만 적고, ;으로 마치자
    // → 함수의 선언
}
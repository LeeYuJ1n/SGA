#include <iostream> // <> : C++, OS, 비주얼 스튜디오에서 제공한 기본 추가 기능
#include "header_1.h" // "" : 개발자가 직접 만든 파일(확장 기능)

int main()
{
    // 헤더 : C, C++에서(꼭 필요 없는데) 지원하는 개발 편의 기능
    // 주 역할 : cpp 파일을 읽어올 때 미리 로딩이 되어야 할 주요 자료를 미리 별도의 파일에서 선언해두고 해당 선언 코드를 cpp보다 먼저 컴퓨터에게 인식시킨다
    // 사례 : 함수 선언, 전역 변수 작성 등에 쓰인다

    // 헤더의 사용 방법
    // 1. cpp 위쪽에 #include "헤더파일" 작성
    // 2. cpp 파일에서 헤더 파일에 있던 기능을 호출해서 사용
    // 2-1. 헤더파일에 선언이 된 함수가 있으면 cpp에서 정의까지 작성 후 사용
    // *header.h에 있던 함수의 정의는 이 파일의 main 아래에 작성

    // 헤더에서 작성된 각종 코드를 호출

    // 선언되고 여기서 작성된 함수를 호출
    PrintAmugona(); // 아무거나 출력하기

    std::cout << Dutsem(10, 3) << std::endl; // 10과 3을 더하는 함수를 수행 후 출력하기
    std::cout << Paelsem(99.9, 23.5) << std::endl; // 두 소스를 뺄셈하고 출력하기

    // 그 다음 헤더에서 정의까지 끝난 함수를 호출

    SetVariables(); // 만들어진 전역변수를 세팅하고 출력

    // 전역변수를 따로 호출
    std::cout << munja << std::endl; // 문자열 출력
    a = 951; // a 값 수정
    b = 7; // b 값도 수정

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    // 헤더에서 만든 구조체 호출
    hs.a = 901;
    hs.b = 902;
    hs.c = 903;

    std::cout << hs.a << std::endl;
    std::cout << hs.b << std::endl;
    std::cout << hs.c << std::endl;



    // ---------------------------------------
    
    // 구조체 : (개발자의 입장에서 이해) 자료형의 집합을 다시 자료형처럼 취급한 것
    // (C++의 정의) 개발자가 직접 정의한 신규 자료형
    // (단순하게 이해) 자료형의 묶음

    // struct 자료명 : 이 구조체를 어떤 자료형(이름)으로 쓸 것인가
    struct TempCharacter // 이 구조체는 앞으로 TempCharacter라는 자료형으로 쓰인다
    {
        // 이 안에 하위 자료형을 작성 : 이 하위 자료형들이 진짜 자료형
        // char name[17]; // 문자열
        char name[17] = "박상열"; // 구조체 안에서 미리 값을 정해줄 수도 있다
        int classID; // 정수
        int level; // 구조체에서는 선언만 하고, 나중에 값을 따로 정해줄 수도 있다
        float hitPoint; // 소수
        int strength;
        int dexteriry;
        int vitality;

        // 특정 제약은 있지만, 원칙적으로는 모든 자료형을 구조체에 작성 가능
    };

    // 구조체를 사용하는 방법 : 구조체 이름을 자료형인 것처럼, 그 자료형을 쓰는 변수를 만들면 된다

    TempCharacter tmpCha; // TempCharacter라는 "자료형"의 변수 tmpCha작성

    // 구조체로 만든 변수명 뒤에 .를 붙이면 하위 변수에 접근 가능
    // 그렇게 접근한 하위 변수를 적절히 수정, 호출하면 된다
    // tmpCha.name = "가나다라"; // 문자열을 지금 진도에서 바로 고치려고 하면 에러가 난다
    // char name[9] = "박종팔";
    // name = "김창삼"; // 이렇게 문자열을 못 바꾸는 것과 같다

    // 문자열의 경우, 넣으려면 현재 진도에서는 다음 두 방법을 써야 한다
    // 1. 덮어씌우기(=cin 사용)
    // 2. 그냥 구조체 안에서 미리 값을 정해주기
    // 3. ?????(현재 진도에서는 다루지 않음) - 나중에 해금

    // cin을 사용해서 이름을 정하고, 값도 코드에서 정한 후 구조체를 출력
    std::cin >> tmpCha.name;

    tmpCha.classID = 0; // 직업
    tmpCha.level = 51; // 레벨
    tmpCha.hitPoint = 1001; // 체력
    tmpCha.strength = 100; // 근력, "힘"
    tmpCha.dexteriry = 80; // 민첩성, "민"
    tmpCha.vitality = 120; // 생명력, 혹은 체력 "체"

    // 구조체 출력의 경우
    // std::cout << tmpCha << std::endl; // 구조체 이름을 출력에 쓸 수는 없다
    std::cout << tmpCha.name << std::endl;
    std::cout << tmpCha.classID << std::endl;
    std::cout << tmpCha.level << std::endl;
    std::cout << tmpCha.hitPoint << std::endl;
    std::cout << tmpCha.strength << std::endl;
    std::cout << tmpCha.dexteriry << std::endl;
    std::cout << tmpCha.vitality << std::endl;
}

// 헤더에서 만들었던 함수를 정의
void PrintAmugona()
{
    std::cout << "아무거나 출력하겠습니다" << std::endl;
}

int Dutsem(int first, int second)
{
    return first + second;
}

float Paelsem(double first, double second)
{
    float result = (float)first - (float)second;
    return result;
}
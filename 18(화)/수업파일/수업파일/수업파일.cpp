#include <iostream>
#include "Calculrator.h" // 계산기 로딩

int main()
{
    // 사칙 연산 계산기를 클래스로?

    Calculrator* calc = new Calculrator();

    // 계산기 사용

    std::cout << "7과 3의 더하기는 " << calc->Add(7, 3) << "입니다" << std::endl;
    std::cout << "7과 3의 빼기는 " << calc->Sub(7, 3) << "입니다" << std::endl;
    std::cout << "7과 3의 곱하기는 " << calc->Mult(7, 3) << "입니다" << std::endl;
    std::cout << "7과 3의 나누기는 " << calc->Div(7, 3) << "입니다" << std::endl;
    std::cout << "7과 3의 나머지는 " << calc->Nam(7, 3) << "입니다" << std::endl;
    std::cout << std::endl;

    // 소수를 넣어서 계산기 사용
    std::cout << "7.1과 3.2의 더하기는 " << calc->Add(7.1f, 3.2f) << "입니다" << std::endl;
    std::cout << "7.1과 3.2의 빼기는 " << calc->Sub(7.1f, 3.2f) << "입니다" << std::endl;
    std::cout << "7.1과 3.2의 곱하기는 " << calc->Mult(7.1f, 3.2f) << "입니다" << std::endl;
    std::cout << "7.1과 3.2의 나누기는 " << calc->Div(7.1f, 3.2f) << "입니다" << std::endl;
    std::cout << std::endl;

    // 매개변수 한 개짜리 함수(누적 계산)
    std::cout << "7과 3의 더하기는 " << calc->Add(7, 3) << "입니다" << std::endl;
    std::cout << "7과 3을 더한 상태에서 추가로 4를 더하면 " << calc->Add(4) << std::endl;
    std::cout << "다시 이 상태에서 추가로 6을 더하면 " << calc->Add(6) << "입니다" << std::endl;
    std::cout << std::endl;

    std::cout << "테스트용 함수 실행" << std::endl;
    std::cout << "7과 3과 11의 더하기는 " << calc->Add(7, 3, 11) << "입니다" << std::endl;
    std::cout << "7.1, 3.2, 11.3의 더하기는 " << calc->Add(7.1f, 3.2f, 11.3f) << std::endl;
    std::cout << std::endl;

    std::cout << "테스트용 함수 실행" << std::endl;
    std::cout << "7과 3의 빼기는 " << calc->Sub(7, 3) << "입니다" << std::endl;
    std::cout << "이 상태에서 추가로 5를 빼면 " << calc->Sub(5) << "입니다" << std::endl;
    std::cout << "다시 이 상태에서 추가로 10를 빼면 " << calc->Sub(10) << "입니다" << std::endl;

    // 함수 오버로드가 쓰이는 곳

    // 1. 매개변수가 달라졌을 때, 같은 "함수명"으로 호출하고 싶으면 쓴다
    //    (정수-소수 구분 없이 같은 용도의 함수를 부르고 싶거나...서로 다른 게임 속 아이템을 "사용"하고 싶거나 등)

    // 2. 같은 함수인데, 들어오는 매개변수가 정확히 무엇인지 예측할 수 없을 때 쓴다
    //    ("무슨 변수가 쓰일지 몰라서 다 만들어봤어")

    // "같은 함수, 매개변수를 예측 불가"의 상황을 가장 잘 드러내는 사례

    // → 데이터의 출력

    printf("%s", "헬로, 월드!"); // ← 문자열 출력
    printf("%d", 12345); // ← 정수 출력

    // 같은 printf인데, 똑같이 모니터에 글자를 출력하려고 쓰는 건데, 쓰이는 데이터는 아주 다르다
    // 이런 경우, 한 함수 내에서 if문으로 처리를 하는 건 한계가 있다(당장 매개변수가 다르니까)
    // →이럴 때 printf를 오버로드 : 같은 이름의 print와 printf를 많이 만들어뒀다가
    // 들어오는 매개변수를 보면서 그때그때 맞는 다른 함수들을 가져와서 쓰는 것

    // (추가) printf에 쓰인 %d, %s, f : 불특정 데이터가 들어왔을 때 해당 데이터를 모니터에 출력하기 위한 문자열로 재처리하는 코드, "서식 문자"라고 부른다
    //                                 많은 서식 문자가 있으며 개발 중에는 예시로 든 %d, %s, %f세 개가 자주 쓰인다
    //                                 %d : 정수 / %f : 소수 / %s : 문자열로 데이터를 표시

    int a; // 미리 만든 정수 변수

    scanf_s("%d", &a); // ← c++로 치면 cin에 대응하는 c언어의 입력 코드

    printf("%d", a);

    // 반환값이 있음에서 알 수 있지만 scanf도 오버로드
    // 매개변수로 쓰인 &a는 곧 포인터
}
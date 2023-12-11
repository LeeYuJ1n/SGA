﻿#include <iostream>

int main()
{
    // 어제 빠뜨린 연산자 설명 하나

    // 구분 연산자 : 기호는 ,
    // 복수의 "같은 역할을 하는 데이터들을 서로 나누어 구분하기 위한" 연산자

    // 실제 사용 예시

    int a, b, c; // int라는 자료형이 공통적인 서로 다른 변수 a와 b와 c를 각각 나누어 선언
    // 위 코드가 실행될 때, a, b, c라는 별개의 정수 세 개가 만들어졌다

    // 위 코드는 하나하나 풀면 다음 세 줄을 합친 것과 같다
    // int a;
    // int b;
    // int c;

    // 만들어진 a, b, c는 정상적으로 (각각 따로) 수정, 호출이 가능

    a = 1;
    b = 22;
    c = 333;

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << a << b << c << std::endl;
    
    // ----------------------------------------

    // 조건문 : 같은 상황에서, 조건(대표적으로 변수)이 달라졌을 때 다른 결과를 출력하는 코드

    // 조건문의 용도, 존재의의

    // 1. 상황에 따라 개발자의 의도가 달라질 경우 앱에 반영해주기 위해서
    // (예를 들면..... "거리가 1km이상 멀어지면 배달비를 1,000원 추가하는 배달앱")

    // 2. 앱에서 일어나면 안 되는 일이 일어났을 경우, 잘못된 결과나 앱의 정지를 방지하기 위해서
    // (대표적으로 "0으로 나누기" 그 외에도 앱에서 허용 안 되는 각종 사고가 일어날 경우)

    // -----------------------------------

    // 조건문의 문법 세 가지
    // 1. 삼항 연산자(게임 개발에서 흔히 쓰이지는 않는다) : 2023년 6월 27일 화요일 수업파일 참고
    // 2. if (조건) {코드}
    // 3. switch (조건) {case별 코드}

    // --------------------------------------

    // if

    // 예제용 변수

    int testIf_1 = 20;

    if (testIf_1 == 1) // ()안에 들어가는 코드가 밑에 {}코드를 수행하기 위한 조건
        // ()안에 조건이 안 맞으면, {}코드는 수해하지 않는다
    {
        std::cout << "숫자가 1입니다" << std::endl;
    }
    else if (testIf_1 == 2)
        // else : 이 이전까지 조건이 충족되지 못했던 상황에서, 다른 조건은 충족될 수 있는 경우
        // 해당 조건을 제시해서 충족되면 () 안에 코드를 수행할 수 있도록 하는 if문의 연장 문법
    {
        // 여기 코드가 수행이 되려면
        // 1. 숫자가 1은 아닐 것
        // 2. 숫자가 2일 것
        // 이 두 가지 경우가 모두 충족되어야 한다
        // (*아니..... 숫자가 2이면 어차피 1은 아닌 거 아니냐? - 조건이 딱 부러질 떄는 티가 안나지만)
        // 조건에 범주화가 있을 경우(조건이 애매해서 겹치는 구간이 있을 경우) if문의 특징이 드러난다
        // 아래의 else if와 같이 보았을 때, 숫자가 2라는 조건이 충족되면 밑의 조건이 충족되어야 하지만
        // 숫자가 2가 되어서 여기 코드가 수행되면, 밑의 코드는 자동으로 무시된다(조건을 아예 안 본다)
        // 여기서 알 수 있는 if문의 특징 : 하나의 조건에는 하나의 결과, 하나의 결과에는 무조건 하나의 조건
        std::cout << "숫자가 2입니다" << std::endl;

    }
    else if (testIf_1 < 10)
        // if문의 특징 : 제시하는 조건을 충족하는 경우의 수가 여러 개여도 괜찮다
        // 범주화된 조건, 혹은 거칠게 표현해서 "애매한 조건"을 내걸어도 조건문이 성립
    {
        // 여기 있 코드가 실행되려면
        // 1. 숫자가 1이 아닐 것
        // 2. 숫자가 2도 아닐 것
        // 3. 그런데 숫자가 10보다는 작을 것
        // 이라는 세 가지 조건을 모두 충족해야 한다
        std::cout << "숫자가 10보다 작습니다" << std::endl;
    }
    else
        // else : if문에서 조건을 제시한 후, "조건을 충족하지 못한 경우 전부 다"를 아르는 것"
        // 다른 말로 "~~~ 빼고 전부 다" : 중요한 포인트는 "전부 다"
        // 특정한 조건을 가리키지 않으므로, else if가 아닌 그냥 else 뒤에는 아무 말도 붙으면 안 된다
    {
        // 1도 아니고, 2도 아니고, 10보다 작지도 않은 "나머지 모든 경우"에 해당할 때
        // 여기 있는 코드를 수행
        std::cout << "나머지 전부 다" << std::endl;
    }

    // ------------------------------------------

    // if의 추가 응용 방법

    // 1. if에서 제시할 수 있는 조건은 둘 이상이어도 괜찮다
    // 단, 각 조건은 논리적으로 관계를 형성해서, 최종적으로는 하나의 참 / 거짓 결과가 나와야 한다
    // (예를 들면 "A이고 B여야 되는데, 그렇지 못 하면 C라도 되어야 한다")

    // 예시를 표현하기 위한 bool 변수 세 개
    bool testBool_1 = true;
    bool testBool_2 = false;
    bool testBool_3 = false;

    // 예시를 표현하기 위한 if문
    if ((testBool_1 == true && testBool_2 == true) || testBool_3 == true)
        // testBool_1도 testBool_2도 참이어야 한다(그래야 최종 참)
        // 그러나 그러지 못할 경우(testBool_1과 testBool_2 중에 거짓이 있을 경우)
        // 그로 인해 도출된 "거짓"과 나머지 3 중 하나는 참이어야 한다
    {
        std::cout << "어쨌든 하나는 참입니다" << std::endl;
    }
    else
    {
        std::cout << "참은 없었습니다" << std::endl;
    }

    // (아래는 비단 if문만이 아니라 다른 제어문에도 모두 적용되는 응용법)

    // 2. 각 if문은 자신의 범위 안에서 독립적이다
    // = if문 안에 다른 if문(혹은 다른 어떤 제어문이든) 작성 가능하다는 뜻!

    float testFloat_1 = 100;
    float testFloat_2 = 100;
    float testFloat_3 = 100;

    if (testFloat_1 >= 100)
    {
        std::cout << "1번 소수는 100보다 큽니다" << std::endl;

        // 이 안에 if문을 작성해도 아무 문제 없이 돌아간다
        if (testFloat_2 >= 100)
        {
            // if문 안에 if문(이를 중복이라고 한다) 적을 때 주의 사항
            // 맨 바깥쪽에 있는 if문 조건이 충족이 안 되면,
            // 이 안쪽으로 들어오지도 못 한다(일단 바깥쪽부터 충족되고 나야 이 조건문을 시도 가능)
            std::cout << "2번 소수도 100보다 큽니다" << std::endl;

            // if문 안에 if문 안에 if문 또 들어가도 된다
            if (testFloat_3 >= 100)
            {
                std::cout << "3번 소수도 100보다 큽니다" << std::endl;

                if (testFloat_1 >= 100 && testFloat_2 >= 100 && testFloat_3 >= 100)
                {
                    std::cout << "모든 조건이 충족하여 계산을 진행합니다" << std::endl;
                    std::cout << "testFloat_1 : " << testFloat_1 << std::endl;
                    std::cout << "testFloat_2 : " << testFloat_2 << std::endl;
                    std::cout << "testFloat_3 : " << testFloat_3 << std::endl;
                    std::cout << "모두 더한 결과 : " << testFloat_1 + testFloat_2 + testFloat_3 << std::endl;
                }
            }

            std::cout << "2번 소수에 대한 조건문이 끝났습니다" << std::endl;
        }

        std::cout << "1번 소수에 대한 조건문이 끝났습니다" << std::endl;
    }

    // 이론상 if문(정확히는 제어문 전체)의 중복은 무한히 가능은 하다

    // 다만, 현실적인 몇 가지 이유 때문에if문을 너무 중복하는 것은 개발자에서 기피하는 경향
    // 1. 맨 안쪽 if문은 (원했든 아니든) 사실상 그 때까지의 모든 조건을 모두 통과해야 수행
    // 2. 맨 안쪽 if문이 끝난다고 if문이 끝나는 게 아니다(if문이 끝나면? → 한 층 밖으로 돌아간다)
    // → 이런 부분이 별도의 참조 코드 없이도 시간 잡아먹는 괴물이 된다
    // → 순수하게 설계가 잘못됐단 이유만으로 느려지는 코드, 그리고 알아보기 힘든 코드, 그리고 수행되기도 힘든 코드
    // → 위 모든 조건을 달성하는 "개발자들이 싫어하는 코드"를 스파게티 코드라고 한다(배배 꼬였다고)
    // 보통은 if문을 따로 적거나, bool 변수를 몇 개 더 만들거나, 어떻게든 설계를 단순하게 고쳐서 if문의 중복을 피하려고 하는 편

    // 여기까지 if문

    // ------------------------------------------------

    // 조건문의 문법 3번째 

    // switch

    // switch의 구성 : switch(조건변수) {case별 코드}

    // 사용 예시

    // 시나리오는 이름의 정수 변수
    int scenario = 11;
    
    // "아웃핏"이라는 이름의 정수 변수(조간은 아니고, switch문 안에서 적당히 바꿔보기 위함)
    int outfit = 0;

    // 이 "시나리오"를 조건으로 지정한 switch문
    switch (scenario)
    {
        // 이 안에서, scenario가 정확히 몇이냐 따라서
        // 아래 코드 중 일부를 수행한다 : 정확히는 scenario가 갖는 값에 대응하는 시작점부터 코드를 밑으로 쭉 수행한다
        // 다른 말로, 특별한 조치가 없을 경우, 위쪽 case에서 시작된 코드 수행이 아래쪽 case까지도 내려갈 수 있다
        // 따라서 각 case별 결과를 분리하고 싶을 경우(대부분 그런 경우) case 코드가 끝난 다음 줄에 break; 코드를 추가해야 한다
        // 해당 코드의 기능 : 코드 수행을 중단하고, {} 한 겹 밖으로 나가는 것
        // (예외 : break;가 if문 안에서 쓰이면 두 겹 밖으로)

    case 0: // scenario가 0이라면 이 지점부터 코드를 수행
        std::cout << "0번 시나리오를 출력합니다" << std::endl;
        outfit = 100; // 아웃핏을 100으로 수정
        break; // 시나리오가 0인 경우, 여기서 코드 수행을 끝내겠다는 뜻

    case 1: // scenario가 1이라면 이 지점부터 코드를 수행
        std::cout << "1번 시나리오를 출력합니다" << std::endl;
        std::cout << outfit << std::endl; // 아웃핏을 (결과가 몇이든간) 출력하기
        break; // 시나리오가 1인 경우, 여기서 코드 수행을 끝내겠다는 뜻

    case 2: // 2라면 여기부터
        std::cout << "2번 시나리오를 출력합니다" << std::endl;
        break; // 시나리오가 2인 경우, 여기서 코드 수행을 끝내겠다는 뜻

        // switch에서 case는 중복되면 안 된다

        // 코드의 시작점과 break가 없으면 계속 밑으로 간다는 점을 응용한
        // 복수 조건 단일 결과 혹은 복수 조건, 부분 복수 결과 코드

    case 3: // 여기에 아무 코드도 (심지어 break)도 안 적고.....

    case 4: // case4에도 안 적고.....


    case 5:
        // case3에 이어서 여기에 코드를 작성할 경우
        // case가 3이어도, 4여도, 5여도 똑같이 이 밑에 있는 코드를 실행하게 된다

        // 복수 조건에서 모두 공통된, 똑같은 코드를 수행 가능(단일 결과)

        std::cout << "3 혹은 4번 혹은 5번 시나리오를 출력합니다" << std::endl;
        break; // 여기서 코드 중단

    case 6:
        outfit = 9999; // case6에 대응하는 결과를 작성한 후, break;를 생략하고

    case 7:
        std::cout << "아웃핏 : " << outfit << std::endl; // 변수를 출력하면

        // case6일 때만 실행되는 코드를 구분하면서
        // case6, 7일 경우에 공통적으로 실행 가능한 코드를 수행
        // 복수 조건에서 부분적으로 구분되는 복수 결과가 나온다

        break; // 여기서 코드 중단

    default :
        // default : 원문 뜻은 "판단 보류" 컴퓨터나 게임에서 뜻은 "기본값"
        // → switch에서 쓰면 이 단어의 뜻은 "미리 예측된 사례(case)가 되지 못한 것"=" 판단불가
        // → if문에서 말하는 else하고 뜻이 똑같다(방금 그거까지 빼고 전부 다)
        // 뜻이 그렇기 때문에 else하고 똑같이 default에도 뒤에 다른 어떤 수식도 붙지 않는다

        // 여기서는 시나리오가 0, 1, 2, 3, 4, 5, 6, 7중 어디에도 해당되지 않으면 아래 코드를 수행

        std::cout << "시나리오 범위 이탈" << std::endl;
        break; // 여기서 코드 중단(맨 마지막이면 break;가 사실 없어도 되지만 이해의 편의상)
    }

    // --------------------------------------------

    // switch의 응용 법(if문 응용법과 같다)
    
    // switch 안에 다른 switch 사용 가능
    // switch 안에 다른 if 사용 가능
    // if 안에서도 다른 switch 사용 가능
    // → 2중복 3중복 n중복 다 됩니다(이론적으로)

    // switch 중복 사례

    int subScenario = 0; // 서브 시나리오

    switch (scenario) // 시나리오별 switch
    {
    case 10: // 시나리오가 10일 경우 아래 코드 수행
        // switch문 안의 switch문

        switch (subScenario)
        {
        case 0:
            std::cout << "서브 시나리오 0" << std::endl;
            break;

        case 1:
            std::cout << "서브 시나리오 1" << std::endl;
            break;
        }

        break; // 여기서 끝

    case 11:
        if (subScenario > 0)
        {
            outfit = 101;
            std::cout << outfit << std::endl;
        }
        else
        {
            outfit = 404;
            std::cout << outfit << std::endl;
        }
        break;

    default : // 시나리오가 이탈했을 경우
        std::cout << "시나리오 이탈" << std::endl;
        break;

    }

    // --------------------------------------------

    // switch문 사용 요약

    // switch () : () 안에 "정확히 사례를 딱 지정 가능한" 변수를 조건처럼 제시
    // "정확히 사례를 딱 지정 가능한" = C++의 방식으로 말하자면, int로 컴퓨터가 인식 가능한 변수
    // {} 안에 각 case를 지정해서, case별 코드를 작성
    // = 조건으로 제시된 변수가 case와 일치할 때, 해당case가 적힌 곳부터 코드를 수행
    // {}가 끝나거나, break를 만날 때 까지
    // 따라서 case별 코드를 구분하기 위해서, case별 코드 아래에는 반드시 break;를 붙인다

    // switch의 의의와 용도

    // switch는 if문처럼 폭 넓은 조건 지정이 불가능하다(변수 하나밖에 못 본다)
    // 대신 사례를 정확히 지정해서 결과를 수행시킬 수 있다
    // (응용하기에 따라서는 ) 여러 조건에서도 같은 결과를 수행시킬 수 있다
    // .....(큰 의미는 없지만) 아무튼 if보다는 빠르다
    // 나중에 봤을 때, "이 변수가 무슨 값일 때" 어떻게 되는지를 훨씬 빠르게 보고 이해할 수 있다
    // 오직 한 가지 조건(변수)만 보는 상황에서는, 그 변수가 보여줄 경우의 수가 무엇인지
    // 개발자가 정확히 알고 있을 경우, 이런 경우는 switch가 if문보다 선호되기도 한다
}
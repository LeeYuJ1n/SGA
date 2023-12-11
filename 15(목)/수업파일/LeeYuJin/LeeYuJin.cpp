﻿// 여기에 입력하는 글자는 아무 것도 하지 않습니다.
// 이렇게 하는 일은 없지만, 기록됨으로써 정보를 남기는 문장을 주석이라고 합니다.
// 주석 입력 방법 : 줄 처음에 //

// 여기에 있는 코드는 현재 작성 중인 코드가 어떤 기능을 기초로 작동하는지를 나타냅니다.
#include <iostream>

// 여기가 프로그래밍이 실제로 작동되는 부분입니다. { } 사이에 코드를 입력하면 작동됩니다.
int main()
{
    // 여기가 프로그래밍을 하는 곳입니다.

    // 프로그래밍에서 가장 먼저, 필수적으로 들어가야 하는 것 : 프로그램의 "대상"
    // 혹은 계산에 쓰일 숫자, 혹은 물건의 이름 → 컴퓨터 용어로 "변수:라고 한다.
    // 변수라는 이름은 "프로그래밍하는 사람이 마음대로 지정해줄 수 있는 숫자"라는 데서 온다.
    // 나중에 버릴지, 말지, 어떠헥 바꿀지가 사람 마음대로 = 언제든 바뀌는 숫자

    // 그 숫자를 코드로 입력해서 컴퓨터가 이해하려면 다음 공식이 필요합니다
    // 그 숫자가 뭐냐 : 값(실제 자료, 실제 숫자, 실제 값)
    // 그 숫자의 형식이 뭐냐 : 자료의 형식, 혹은 "자료형" 혹은 "데이터 유형"
    // (그건 자연수냐, 정수냐, 소수냐 아니면 숫자도 아니냐)
    // 그리고 그 숫자의 이름이 뭐냐 : "변수의 이름" 혹은 "변수명"

    // 변수를 입력하는 방법(C++ 언어를 기준을 때, 실제로는 기호 제외)
    // (자료형) "변수명" = 값

    int number = 100;
    // int = 정수라는 뜻의 "자료형"
    // number = 변수명, 즉 컴퓨터는 이 뒤에 오는 숫자를 "넘버"라는 이름으로 기억할 것
    // 100 : 값, 컴퓨터가 "넘버"라는 이름을 들으면 떠올릴 진짜 숫자

    int sutja = 999;

    // 변수를 사용하는 방법이 여러 가지가 있는데, 그 중에는 해당 자료를 모니터에 보여주는 것도 있다.
    // 이를 출력(프린트)라고 한다.

    // 출력을 하는 방법은
    
    std::cout << number << std::endl;
    std::cout << sutja << std::endl;

    // std:: → C++에 있는 여러 기본 기능을 사용하기 위한 호출 코드
    // cout → C++에서 작성된 여러 자료를 출력하기 위한 출력(프린트) 코드
    // endl → "줄의 끝"혹은 "줄 바꿈" (End of line)에 코드를 작성하면 모니터에 나오는 문자가 줄바꿈

    // 출력을 하는 (다른) 방법 (C스타일)

    printf("%d\n", number); // (C++환경에서는 비추천)


    // -------------------------------------------------------------------------------


    // 변수를 사용하는 방법2 : 실제로 계산을 해보기(연산)
    
    // 대상은 변수 하나의 수정을 하는 방법과, 둘 이상의 변수를 사용해서 바로 계산하는 방법이 있다.

    // 변수 하나를 사용해서 계산하는 방법
    number = 200;
    // 수정 : 아까 100라고 정했던 "넘버"의 값을 200으로 고친다.

    std::cout << number << std::endl;

    number = 200 + 2;
    std::cout << number << std::endl;

    number = 200 - 2;
    std::cout << number << std::endl;

    number = 200 * 2;  // * : 컴퓨터에서 곱하기를 뜻합니다.
    std::cout << number << std::endl;

    number = 200 / 2; // / : 컴퓨터에서 나누기를 뜻합니다.
    std::cout << number << std::endl;

    // 여기서 쓰인 +, -, *, /같은 기호를 계산에 사용되는 매개, 혹은 "연산자"라고 한다.
    // 컴퓨터에서 계산에 쓰이는 기호 매개를 모두 연산자로 부른다.
    // =도 연산자이다. 그리고 더 많은 다양한 연산자가 있다.

    // 자기 자신을 사직 연산
    number = number+ 2;
    std::cout << number << std::endl;
    // 위 연산은 자신이 원래 갖고 있던 값을 이용해서 연산을 하고, 그 결과를 다시 새로운 값으로 수정해서 적용하겠다는 뜻

    number = number - 2;
    std::cout << number << std::endl;

    number = number* 2;
    std::cout << number << std::endl;

    number = number / 2;
    std::cout << number << std::endl;

    // 자기 자신을 사직 연산...을 줄여서 사용하는 방법
    number += 2;
    std::cout << number << std::endl;
    // 원래 값을 연산에 사용하고 결과를 수정해서 새로 적용


    number -= 2;
    std::cout << number << std::endl;

    number *= 2;
    std::cout << number << std::endl;

    number /= 2;
    std::cout << number << std::endl;

    // 여기에 쓰이는 +=, -=, *=, /=는을 누적 연산자라고 한다.

    number = number % 3;
    std::cout << number << std::endl;

    // % : 사직 연산에 속하지는 않지만 사직연산과 똑같은 방법으로 쓸 수 있다.
    // 의미는 "~로 나눈 나머지"

    // -------------------------------------------------------------------------------

    // 변수 둘 이상을 사용하는 연산

    number = 2; // 숫자 계산을 확인해보기 위해 수정
    
    // 사직연산이 똑같이 사용 가능

    std::cout << sutja + number << std::endl;
    // cout을 사용할 경우, 연산을 하고 그 결과를 한번에 출력하는 것도 된다.

    std::cout << sutja - number << std::endl;
    std::cout << sutja * number << std::endl;
    std::cout << sutja / number << std::endl; // 홀수를 2로 나눴는데 결과가 이상하다

    // 이런 일이 벌여지는 이유 : 컴퓨터한테 sutja와 number가 "정수"라고 주입했기 떄문.
    // 컴퓨터가 정수 외의 다른 계산을 할 능력이 없다.
    
    // 소수가 계산되어야 하는 상황이면, 그 때는 컴퓨터엑 이것이 소수라고 가르쳐줘야 한다.
    // // 그게 자료형이 있어야 하는 이융
    
    // 자료형의 종류
    
    // 정수
    int a = 1;

    // 소수
    float b = 1.1f;
    // float : "소수"라는 뜻의 컴퓨터 용어
    // 소수를 적을 때 특히 소수점 밑으로 숫자가 있으면 숫자뒤에 f를 붙여주는 것이 좋다.

    // 글자
    char c = 'a'; // 한글 불가(쓰면 에러가 나거나, 보이지 않게 된다.)

    // 여부 논리(맞느냐, 틀렸느냐의 블박에 없는 자료형. 발명한 사람의 이름을 따서 "블리만"이라고

    bool logical = false; // 틀린 경우 false

    // 훨씬 더 많은 자료형이 많지만, 실제로 자주 쓰이는 자료형은 이 네 가지가 가장 많다.

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << logical << std::endl; // boolean 자료형은 true일 경우 표시하면 1, false일 경우 0

    // -------------------------------------------------------------------------------

    // 변수 둘 이상을 사용하는 계산2

    float pn1 = 999; // 소수점이 없는데 f를 쓰면 에러(C++ 경우...쓰면서 몸으로 익히는 수밖에 없다.)
    float pn2 = 2;

    std::cout << pn1 / pn2 << std::endl;
    // 계산에 쓰일 숫자가 소수라고 컴퓨터에게 주입을 미리 해뒀기 때문에 컴퓨터가 계산을 소수로 할 수 있었다.

   
    bool comp;
    // 변수를 만들었는데 값을 주지 않으면 컴퓨터는 이름은 기억하지만 값을 계산하지 못 한다.
    // 이렇게 값 없이 변수의 이름만 컴퓨터에게 알려주는 것을 "선언"이라고 한다.
    // 선언으로 만든 변수는 계산 전에 반드시 값을 넣어줘야 한다.

    // 비교하기
    comp = pn1 < pn2; // 이 연산의 결과는 "틀림"으로 나온다.
    std::cout << comp << std::endl;

    comp = pn1 > pn2; // 이 연산은 "맞음"으로 나온다.
    std::cout << comp << std::endl;
    // <, > : 크기를 비교하는 연산자
    // < : 오른쪽이 더 크다는 뜻(혹은 크냐는 뜻)
    // > : 왼쪽이 더 크다는 뜻(혹은 크냐는 뜻)

    comp = pn1 == pn2; // 틀림으로 나올 것
    std::cout << comp << std::endl;
    // == : 왼쪽과 오른쪽이 똑같은가를 판단한다.

    comp = pn1 != pn2;
    std::cout << comp << std::endl;
    // != : 왼쪽과 오른쪽이 똑같지 않다를 판단한다.(! : "~가가 아니라"라는 뜻)

    // 여기까지가 변수만 알면 쓸 수 있는 연산자들
    // 더 많은 연산자가 개발을 하는 한 영원히 새로 등장할 것(그떄그때 연산자의 형태와 역할을 익혀두도록 합시다.)

    // -------------------------------------------------------------------------------

    // 출력과 쌍을 이루는 기능 : 입력
    // 입력 방법 : cin >> (입력이 저장될 변수)
    // 입력이 저장될 변수를 선언한다.(갑자기 줘도 되지만...어차피 입력한 값으로 바뀔 테니 의미는 없을 것)

    int input;
    
    std::cin >> input; // 여기서 입력된 숫자가 input의 값이 된다.

    std::cout << input << std::endl;

    // 입력을 받으려고 할 때, 조금 더 사용학 편하도록 프로그램 안에서 안내를 해줄 수도 있다.
    // 출력과 입력을 동시에

    std::cout << "입력 : "; // cout뒤에 ""를 넣으면 그 안에 자유롭게 다른 내용을 넣을 수도 있다.
    std::cin >> input;

    std::cout << input << std::endl;

    // 과제
    // 1. 사칙연산 출력기
    // 변수 두 개를 선언한 후, 입력으로 값을 받는다.
    // 입력으로 값을 받은 두 변수를 더하고, 뺴고, 곱하고, 나누고, 나머지까지 계산해서 모니터에 출력

    // 2. 자릿수 계산하기
    // 변수 한 개를 선언한 후, 입력으로 값을 받는다. 단, 입력하는 숫자는 세 자릿수여야 한다.
    // 값을 받은 변수의 백의 자리, 십의 자리, 일의 자리를 각각 계산해서 모니터에 출력
    // 백의 자리, 십의 자리, 일의 자리는 계산해서 바로 출력해도 되고, 다른 변수에 저장해도 좋습니다.
}

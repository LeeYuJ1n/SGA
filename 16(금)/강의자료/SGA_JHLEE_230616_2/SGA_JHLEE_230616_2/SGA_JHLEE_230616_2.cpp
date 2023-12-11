﻿#include <iostream>

int main()
{
    // 반복문 : 조건문과 함께 제어문을 구성하는 (크게 나누어서) 두 가지 유형 중 하나

    // 반복문의 역할 : 규칙에 따라 변화하거나, 완전히 똑같은 코드를 여러 번 반복한다
    // -> 귀찮은 노가다를 줄이려고 만들었다

    // 예시 : "헬로 월드" 100번 연속 출력하기

    // 만약에 이 코드를 직접 입력을 해야 했다면...?
    // std::cout << "헬로, 월드!" << std::endl; 이 코드를 100번 반복!

    // 반복문을 사용하는 방법 : 가장 대표적인 명령어
    // for (시작 상황 ; 반복문이 계속될 조건 ; 지정된 코드가 끝날 때마다 변화가 일어날 경우 그 변화)

    // for 직접 써보기 (헬로월드 100번)

    for (int i = 0; i < 100; ++i)
        // int i = 0 : 이 반복문을 시작할 때, "i"라는 이름의 정수를 만들고 0으로 할당한다 (시작 상황 설정)
        // 여기서 i는 for 문에서 보편적으로 선택되는 정수 변수의 이름(차례, 즉 index, 혹은 iterator의 첫 글자)
        // i가 왜 0인가? : 컴퓨터에서는 0이 첫 번째 숫자, 혹은 기준으로 자주 선택되므로 거기 맞춘 것

        // i < 100 : 왼쪽에서 만든 i가 100보다 작은 숫자인 한(0부터 99 사이인 한) 이 반복문은 계속된다는 뜻
        
        // ++, -- : 누적 연산자의 한 가지. 이 연산자가 숫자(특히 정수) 변수 앞뒤에 붙으면 호출 후 숫자가 1씩 바뀐다.
        // ++는 증가, --는 감소
        // ++i : 지정된 코드가 끝나고 나면 i는 1 증가한다는 뜻
    {
        //여기 입력되는 코드가 for문이 반복되는 동안에 실제로 수행할 코드
        std::cout << "헬로 월드!" << std::endl;
        //위 코드를 i가 0일 때부터 99일 때까지 (100번) 반복해서 수행
    }


    //-----------------------------

    // for문의 다른 활용법
    
    // for의 두 가지 특징 : 1. 코드가 끝나면 규칙적으로 특정 조건이 바뀐다
    // 2. 해당 조건에 for문의 시작과 끝이 달려있기 때문에, 결과적으로 for문은 "반복 횟수가 정해져 있다!"

    // for 문 활용 사례 : 구구단 (1부터 9까지 차례로 특정 숫자를 곱하기)

    for (int i = 1; i < 10; ++i)
    {
        //i가 1일 때부터 9일 때까지 차례로 아래 코드를 실행한다
        std::cout << 9 * i << std::endl; // for문 ()에서 만든 변수는 for문 안이라면 자유롭게 가져와서 쓸 수도 있다!
    }

    // for 문의 다른 활용법 2

    // 조건문과 마찬가지로, 반복문도 다른 반복문 안에서 작성할 수 있다
    // 조건문 안에 반복문, 혹은 반복문 안에 조건문도 작성할 수 있다!

    for (int i = 0; i < 10; ++i)
    {
        //i가 0부터 9일까지 10번 반복하는 코드

        //반복문 안에 반복문
        for (int j = 0; j <= i; ++j)
            //반복문 안에 반복문을 적을 때, 보통은 i 다음 j (그 다음은 다시 k...) 등으로 차례를 담당할 변수를 만든다
            //j <= i : i가 0일 때는 j도 0일 때만, i가 9라면 j도 0부터 9가 될 때까지 다른 횟수로 반복
        {
            std::cout << "*";
        }

        std::cout << std::endl; //i코드가 끝날 때만 줄바꿈을 하겠다
    }
}
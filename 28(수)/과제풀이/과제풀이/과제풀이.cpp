﻿#include <iostream>
#include <Windows.h>
#include <stdlib.h>

int main()
{
    // 랜덤 생성을 위한 기준 자료(시도) 만들기
    srand(GetTickCount64());

    // 게임에 필요한 변수 체크하기

    // 랜덤 숫자 한 개 필요
    int roulette; // 룰렛이라고 지칭
    
    // 플레이어에게 각각 맞추려는 숫자, 범위 선택지, 점수
    int bet; // 맞추려는 숫자 : 판돈대상이라고 지칭
    int call; // 제시 범위 선택지 : 제시, 제안이라고 지칭
    int div; // 내가 받을 점수를 : "배당률"이라고 지칭

    // 추가로(꼭 필요한 건 아니었지만)있으면 좋을 것 같은 변수
    // 입력을 할 건데, 입력을 애초에 내가 잘못했을 경우를 생각해보기 위한 것
    bool inputVaild; // "적절한 입력이 이루어졌는가?"를 확인하기 위한 bool 변수

    // 게임 시작 전에, 꼭 필요한 변수가 초기화 되어야 하면 해두기

    // 정수가 0부터 시작해야 하니까
    div = 0;
    
    // 이제 게임을 진행 - 혹시 빠뜨린 게 있으면 이번에는 중간에 하나씩 추가 예정

    // 랜덤 숫자가 먼저 뭔지 결정
    roulette = rand() % 37; // 37로 나누면 나머지가 0부터 36까지 나올 테니까

    // 문자로 게임 안내와 입력까지

    std::cout << "컴퓨터가 0부터 36까지 숫자 중 하나를 랜덤으로 정했습니다" << std::endl;
    std::cout << "이 숫자가 어떤 숫자인지, 혹은 어떤 범위인지 맞춰주세요" << std::endl;
    std::cout << std::endl; // 줄을 띄워서 읽기 쉽게

    std::cout << "숫자를 맞춰주세요 (0 ~ 36) : ";
    std::cin >> bet; // 맞추려는 숫자를 입력

    std::cout << std::endl; // 줄을 띄워서 읽기 쉽게

    std::cout << "맞추려는 숫자의 범위를 선택해주세요" << std::endl;
    std::cout << "1. 정확히 맞추겠다 / 2. 오차는 1이다 / 3. 오차는 2다" << std::endl;
    std::cout << "4. 홀짝이 같다 / 5. 결과가 내 예측보다 크거나 같다 / 6. 작거나 같다" << std::endl;
    std::cout << std::endl; // 줄을 띄워서 읽기 쉽게

    std::cout << "범위를 선택해주세요 (1 ~ 6) : ";
    std::cin >> call; // 맞추려는 숫자를 입력

    std::cout << std::endl; // 줄을 띄워서 읽기 쉽게

    // 안내 후 입력 받기까지 진행했으니, 이 입력이 맞는지를 먼저 확인
    inputVaild = (bet >= 0 && bet <= 36 && call >= 1 && call <= 6);
    // bet이 0:36, call은 1~6까지여야 위 변수가 true가 된다

    // 입력도 했고 입력 적절성 판별까지 헀으니 결과를 살펴봅시다

    // if (inputVaild == true)
    if (inputVaild) // 바로 위 코드와 완전히 같은 뜻, bool 변수를 if, 혹은 다른 조건에서 확인할 때, "true"
    {
        // 입력이 적절한 경우에만 결과를 판별합니다

        // 플레이어의 선택의 따라, 그 결과가 모두 범위에 맞을 때만, 정수를 적절히 주도록

        if (call == 1 && roulette == bet) // 내 선택은 칼 맞추기이고, 실제로 맞으면
        {
            // 여기서 if를 중복 작성해도 됐겠지만 큰 의미가 없다
            // 점수가 맞으면 n점(이번 경우는 35점)이고 아니면 0점이어야 하는데 0점은 이미 위에서 줬으니까

            div = 35;

            // else도 필요없다 (0점은 이미 위에서 줬다)
            // 대신 지금 필요한 건 else if
        }
        else if (call == 2 && 
            roulette >= (bet - 1) && 
            roulette <= (bet + 1))
        {
            // ↑코드 팁 : ;이 있어야 C++에서 줄바꿈이 된다는 점을 다르게 이용하면
            // ;을 쓰지 않고 텍스트를 줄바꿈했을 때, 실제로는 코드 줄바꿈을 하지 않고
            //  우리 눈에만 줄을 바꾸면서 보기 편하게 정렬할 수도 있다

            div = 25;
        }
        else if (call == 3 && 
            roulette >= (bet - 2) && 
            roulette <= (bet + 2))
        {
            div = 20;
        }
        else if (call == 4 && (roulette % 2) == (bet % 2)) // 이 조건으로 홀짝이 같은지 알 수 있다
        {
            div = 10;
        }
        else if (call == 5 && roulette >= bet)
        {
            div = 5;
        }
        else if (call == 6 && roulette <= bet)
        {
            div = 5;
        }
    }
    else
    {
        // 입력이 부절적하면?
        div = -1;
        // 입력이 잘못됐으니 정수도 뺏고 그엠 게임을 오류 처리하겠다는 뜻
        // 게임에서 꼭 필요한 변수에, 일반적으로 게임에서 배정하지 않은 값을 고의로 줄 경우
        // 이건 "에러가 났다고"그 컴퓨터에, 그리고 개발자 스스로에게 신호를 주는 행동
        // 나중에 "에러가 난 경우"를 판단할 때, 이 값을 보고 판단할 수 있다
    }

    // 이 조건문이 끝났을 때, 점수가 각각 정해지다..... 한 경우만 빼고
    // 와일드 룰 : 숫자가 0이면, 플레이어가 0을 예측하고, 또 "칼같이 맞추겠다"라고 한 경우를 뺴고 무조건 다 틀림
    // 이 조건을 구현하는 방법
    
    // 구현하는 방법 1 : 위 조건문에 각 선택지에 "숫자가 0인 경우를" 조거추가
    // 구현하는 방법 2 : "몰수패"라는 상황을 별도로 if문으로 하나 더 만든다

    // 몰수패 코드 만들기

    if (roulette == 0) // 랜덤이 0이 뜬 경우에는 몰수패를 판별합니다
    {
        // (이렇게 중복 if문으로 할 경우, 랜덤이 0이 아닐 때는 전체 if문을 안 볼 겁니다)

        if (bet == 0 && call == 1) // 내 예측도 0, 선택지도 "정확히 0이다"라고 선언했을 때
        {
            div = 35; // 그 때는 대박. 오로지 이 때만 대박
        }
        else // 하나라도 조건이 다르면
        {
            div = 0; // 몰수패, 쪽박
        }
    }
    
    // 여기까지 오면 점수가 모두 정해졌다

    // 점수가 -1만 아니면 (=게임을 정상적으로 잘 진행했다)결과를 표시
    if (div != 1)
    {
        // 랜덤 숫자를 공개하고, 내 선택지도 표시해주면서 점수를 최종 표시

        std::cout << "컴퓨터가 내었던 숫자 : " << roulette << std::endl;
        std::cout << "내가 예측한 숫자 : " << bet << std::endl;

        // 선택지를 숫자보다 좀 더 구체적으로 표시해주도록 하자
        // 어차피 여기까지 왔으면 에러가 안 났고, 따라서 내가 선택한 선택지는 1, 2, 3, 4, 5, 6 여섯 개밖에 없다
        // → switch 쓰기 딱 좋은 상황

        switch (call) // if문 안에서도 switch 사용 가능
        {
        case 1:
            std::cout << "내 선택 범위 : 정확한 예측" << std::endl;
            break;

        case 2:
            // std::cout << "내 선택 범위 : 오차 1" << std::endl;
            std::cout << "내 선택 범위 : 트리블 배팅" << std::endl;
            break;

        case 3:
            // std::cout << "내 선택 범위 : 오차 2" << std::endl;
            std::cout << "내 선택 범위 : 퀸티플 배팅" << std::endl;
            break;

        case 4:
            std::cout << "내 선택 범위 : 콜 오드" << std::endl; // 홀짝을 맞추려고 했다는 뜻
            break;

        case 5:
            std::cout << "내 선택 범위 : 빅 게임" << std::endl; // 더 큰 숫자를 노렸다는 뜻
            break;

        case 6:
            std::cout << "내 선택 범위 : 스몰 게임" << std::endl; // 더 작은 숫자를 노렸다는 뜻
            break;
        }

        // 점수가 0점이 아니면 득점을 했으니까 점수와 축하 안내하기
        if (div > 0)
        {
            std::cout << std::endl; // 한 줄 띄우고
            std::cout << "여러분의 배당 : " << div << std::endl;
            std::cout << "축하합니다" << std::endl;
        }
        else
        {
            std::cout << std::endl; // 한 줄 띄우고
            std::cout << "여러분의 배당 : " << div << std::endl;
            std::cout << "아깝습니다" << std::endl;
        }
    }
}
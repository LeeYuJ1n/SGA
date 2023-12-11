#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    srand(GetTickCount64()); //랜덤 시드 생성

    // 바카라를 하기 위한 변수

    // 카드 한 줄을 배열로 표현
    int playingCard[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }; // A부터 10까지, 잭, 퀸, 킹

    // 카드를 받아야 할 변수 (플레이어, 뱅커 각각 두 장씩) : 선언만 (값은 나중에 할당)
    int playerCard1;
    int playerCard2;

    int bankerCard1;
    int bankerCard2;

    // 카드를 합쳐서 계산한 일의 자리를 저장하기 위한 변수
    int playerCall;
    int bankerCall;

    // 두 사람의 점수
    int playerScore = 0;
    int bankerScore = 0;

    //"게임이 지금 돌아가고 있는가?"를 확인하기 위한 변수
    bool isPlaying = true;

    // 입력을 받기 위한 변수
    int input;

    //게임을 진행하기 위한 반복문
    //while(isPlaying) // 게임을 하고 있음을 조건으로 제시
    while (true) //그냥 무조건 무한으로 돌리기 (좀 더 흔한 형태)
    {
        // 게임이 종료되는 조건과 코드를 작성
        if (!isPlaying) // !를 bool 변수 앞에 붙이면 "isPlaying != true"라는 것과 똑같은 뜻이 됩니다.
        {
            break;
        }

        //안내를 하기 전에 카드를 뽑아놓고 시작합시다.
        playerCard1 = playingCard[(rand() % 13)]; // "rand() % 13"로 나온 숫자를 포커 카드의 순번으로 활용
        playerCard2 = playingCard[(rand() % 13)];

        bankerCard1 = playingCard[(rand() % 13)];
        bankerCard2 = playingCard[(rand() % 13)];

        //카드가 정해졌으니 합계도 미리 정해둡시다.
        playerCall = (playerCard1 + playerCard2) % 10; //두 수를 더하고, 10으로 나눈 나머지를 구하면 일의 자리가 나옵니다.
        bankerCall = (bankerCard1 + bankerCard2) % 10;

        std::cout << "바카라 게임 : 당신과 뱅커가 각각 두 장의 포커 카드를 랜덤으로 뽑았습니다." << std::endl;
        std::cout << "그리고 당신과 뱅커는 각각 카드의 숫자를 더해서 일의 자리만 남겼습니다." << std::endl;
        
        std::cout << std::endl; //내용을 적지 않고 std::endl;을 사용하면 줄을 한 줄 띄울 수 있습니다.

        std::cout << "지금 당신의 카드는 " << playerCard1 << ", " << playerCard2 << "입니다." << std::endl;

        std::cout << std::endl;

        std::cout << "현재 당신과 뱅커 중에서 어느 쪽 카드를 합친 일의 자리가 더 클까요?" << std::endl;
        std::cout << "맞추시면 점수를 1점 받고, 틀리면 뱅커가 점수를 1점 받습니다." << std::endl;

        std::cout << std::endl;

        std::cout << "1. 플레이어(당신) / 2. 뱅커 / 3. 비김" << std::endl;
        std::cout << "입력 : ";

        std::cin >> input;

        switch (input)
        {
        case 1: //플레이어 합이 더 크다고 내가 선택한 경우

            std::cout << "지금 당신의 카드는 " << playerCard1 << ", " << playerCard2 << "입니다." << std::endl;
            std::cout << "지금 뱅커의 카드는 " << bankerCard1 << ", " << bankerCard2 << "입니다." << std::endl;

            std::cout << "당신의 카드 계산 결과 : " << playerCall << std::endl;
            std::cout << "뱅커의 카드 계산 결과 : " << bankerCall << std::endl;

            if (playerCall > bankerCall)
            {
                std::cout << "맞췄습니다!" << std::endl;
                playerScore += 1;
            }
            else
            {
                std::cout << "틀렸습니다." << std::endl;
                bankerScore += 1;
            }

            //점수 보여주기
            std::cout << "당신의 점수 : " << playerScore << ", 뱅커의 점수 : " << bankerScore << std::endl;

            break;

        case 2: //뱅커 합이 더 크다고 내가 선택한 경우

            std::cout << "지금 당신의 카드는 " << playerCard1 << ", " << playerCard2 << "입니다." << std::endl;
            std::cout << "지금 뱅커의 카드는 " << bankerCard1 << ", " << bankerCard2 << "입니다." << std::endl;

            std::cout << "당신의 카드 계산 결과 : " << playerCall << std::endl;
            std::cout << "뱅커의 카드 계산 결과 : " << bankerCall << std::endl;

            if (playerCall < bankerCall)
            {
                std::cout << "맞췄습니다!" << std::endl;
                playerScore += 1;
            }
            else
            {
                std::cout << "틀렸습니다." << std::endl;
                bankerScore += 1;
            }

            //점수 보여주기
            std::cout << "당신의 점수 : " << playerScore << ", 뱅커의 점수 : " << bankerScore << std::endl;

            break;

        case 3: //비겼다고 내가 선택한 경우

            std::cout << "지금 당신의 카드는 " << playerCard1 << ", " << playerCard2 << "입니다." << std::endl;
            std::cout << "지금 뱅커의 카드는 " << bankerCard1 << ", " << bankerCard2 << "입니다." << std::endl;

            std::cout << "당신의 카드 계산 결과 : " << playerCall << std::endl;
            std::cout << "뱅커의 카드 계산 결과 : " << bankerCall << std::endl;

            if (playerCall == bankerCall)
            {
                std::cout << "맞췄습니다!" << std::endl;
                playerScore += 1;
            }
            else
            {
                std::cout << "틀렸습니다." << std::endl;
                bankerScore += 1;
            }

            //점수 보여주기
            std::cout << "당신의 점수 : " << playerScore << ", 뱅커의 점수 : " << bankerScore << std::endl;

            break;

        default: //입력을 잘못한 것
            std::cout << "잘못된 입력입니다. 게임은 무효로 처리하고 다시 시작하겠습니다." << std::endl;

            
            continue; //반복문에서, 필요한 경우, 이 밑에 있는 코드는 수행하지 않지만, 반복문 자체는 계속 진행하는 코드


            break;
        }

        std::cout << std::endl;//알아보기 쉽게 한 줄 띄우기

        std::cout << "계속 진행합니다." << std::endl;

        if (playerScore >= 3) //플레이어의 점수가 3점을 채우면
            //>= : 혹시라도 어떤 오류가 생겨서 플레이어 점수가 4점, 5점 등의 결과가 나오더라도 게임오버만은 제대로 될 수 있도록
        {
            std::cout << "당신이 3점을 채워서 마지막에 이겼습니다!" << std::endl;
            std::cout << "축하합니다!" << std::endl;
            isPlaying = false; //플레이 중단, 혹은 게임오버
        }
        else if (bankerScore >= 3)
        {
            std::cout << "뱅커가 3점을 채워서 마지막에 이겼습니다!" << std::endl;
            std::cout << "고생하셨습니다!" << std::endl;
            isPlaying = false;
        }

        std::cout << std::endl;
    }
}
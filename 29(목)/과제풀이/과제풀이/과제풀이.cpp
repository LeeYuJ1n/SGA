#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    // 블랙잭

    // 1. 21 범위 내에서 최대한 큰 숫자 만들기
    // 2. 21 넘어가면 패배
    // 3. 뽑는 숫자는 랜덤

    // 랜덤 시드
    srand(GetTickCount64());

    // 필요한 변수 예측
    // 두 플레이어의 카드 합
    int playerSum = 0; // 플레이어 쪽의 합, 작성과 동시에 초기화
    int computerSum = 0; // 컴퓨터 합

    // (꼭 필요한 건 아닌데, 그냥 내가 보고 싶어서)
    // 플레이어(와 상대편도) 이번에  뽑은 카드
    int playerDraw = 0;
    int computerDraw = 0;

    // 입력을 해야 되니까 입력용 변수
    int input = 0;

    // 여러 번 하는 게임이었으면 점수가 필요할지도... 모르지만, 이번엔 단판이라서 그냥 안 만듭니다
    // 대신, 이 게임이 어느 시점에서 끝나는가가 경우에 따라 달라질 수 있기 때문에(21을 한쪽이 넘기면 게임 오버)
    // 그 게임 오버 여부를 변수로 따로
    bool gameOver = false;

    // ------------------------------------- 나중에 혹시 추가 변수가 필요하면 돌아와서 더 만듭니다

    // 최초에 게임을 안내하기 위한 코드를 작성(1회용)
    std::cout << "블랙잭 게임을 시작합니다" << std::endl;
    std::cout << std::endl;

    // 게임 부분
    while (true)
    {
        // 반복문을 시작하기 전에(맨 처음에) 게임오버 여부를 한 번 판단해서
        // 게임 오버가 되어야 하면 즉시 반복문 자체를 중단
        // 게임 위에 적는 이유 : 이 게임이 어느 시점에서 처음으로 되돌아가는지....도 경우에 따라 달라질 수 있어서
        // (처음으로 반복문이 돌아가야 할 경우, continue를 사용할 위험이 있기 때문에)
        // → continue가 위험인 경우 : 쓰는 시점이 잘못될 경우, 무한 continue가 되는 동안 break가 무시될 수 있다
        if (gameOver == true)
        {
            break;
        }

        // 진짜로 게임을 진행...
        
        // 카드 뽑기
        playerDraw = (rand() % 13) + 1; // 1 ~ 13
        computerDraw = (rand() % 13) + 1;

        // 뽑았으니까 이 시점에서 바로 합계 더하기
        playerSum += playerDraw;
        computerSum += computerDraw;

        // 나온 카드 표시, 그리고 플레이어가 현재 자기 카드(숫자 합)를 볼 수 있도록
        std::cout << "카드를 뽑아서 합했습니다" << std::endl;
        std::cout << std::endl;

        std::cout << "컴퓨터가 뽑은 카드 : ???" << std::endl;
        std::cout << "컴퓨터의 카드 합 : ???" << std::endl;
        std::cout << std::endl;

        std::cout << "여러분이 뽑은 카드 : " << playerDraw << std::endl;
        std::cout << "여러분의 카드 합 : " << playerSum << std::endl;
        std::cout << std::endl;

        // 이걸로 카드 뽑기, 합, 표시가 모두 되었는데
        // 어제 과제로 제시한 블랙잭 선택지는 3가지 : 스탠드(승부) / 드로우(하나 더) / 버스트(파산+패배)

        // 버스트는 선택지지만 내가 입력하는 선택지가 아니다 → 코딩으로 지면 자동으로 실행
        // 입력을 받기 전에 버스트 여부를 판단부터 해야 한다

        // 한쪽이 21을 넘기면 → 입력 없이(플레이어 선택권 없이) 한 쪽의 패배, 혹은 무승부
        if (playerSum > 21 || computerSum > 21)
        {
            // 경우의 수는 세 가지 : 내가 망했거나, 제가 망했거나, 둘 다 망했거나
            // 
            // 버스트가 나오면 공통적으로 결과부터 공개하도록
            std::cout << std::endl;
            std::cout << "[ 버스트 ]" << std::endl;
            std::cout << std::endl;

            std::cout << "컴퓨터가 뽑은 카드 : " << computerDraw << std::endl;
            std::cout << "컴퓨터의 카드 합 : " << computerSum << std::endl;
            std::cout << std::endl;

            std::cout << "여러분이 뽑은 카드 : " << playerDraw << std::endl;
            std::cout << "여러분의 카드 합 : " << playerSum << std::endl;
            std::cout << std::endl;

            if (playerSum > 21 && computerSum > 21) // 둘 다 망한 경우
            {
                // 무승부
                std::cout << "둘 다 21을 초과하여 무승부로 처리하고, 다시 시작합니다" << std::endl;
                std::cout << std::endl;

                playerSum = 0;
                computerSum = 0;

                continue; // 반복문의 처음으로

                // 이 다음부터는 둘 다 망한 경우가 아니므로 → 한 쪽만 망한 경우가
            }
            else if (playerSum > 21) // 이 경우는 자동으로 컴퓨터는 안 망했다는 뜻
            {
                std::cout << "여러분의 카드 합이 21을 초과하여 패배했습니다" << std::endl;
                std::cout << std::endl;

                // 게임이 끝났으니 끝났다고 처리
                gameOver = true;

                // 그리고 반복문의 처음으로(처음으로 간 다음 곧바로 중단)
                continue;
            }
            else if (computerSum > 21) // else만 적어도 되긴 하지만 이렇게 구체적으로 적으면 미래의 내가 좋아하기 때문에
            {
                // 결국 코드를 길게 적는 이유도, 주석을 꼬박꼬박 다는 이유도 타인을 위해서, 미래의 나든, 같은 팀원이든...
                // 나 혼자 적고 미래의 두 번 다시 유지보수 안 할 거라면 굳이 주석이나 구체적인 코드를 짜야 할 필요는 없다
                std::cout << "컴퓨터의 카드 합이 21을 초과하여 패배했습니다" << std::endl;
                std::cout << std::endl;

                gameOver = true;
                continue;
            }
            // continue를 이렇게 적어도 좀 더 효율적인 코딩 가능
        }

        // 여기서 버스트 판단이 끝났다

        // 다음 선택이(입력을 받아서 진행)
        while (true)
        {
            std::cout << "여러분의 선택을 입력해주세요" << std::endl;
            std::cout << "1. 스탠드" << std::endl;
            std::cout << "2. 드로우" << std::endl;
            std::cout << "입력 : ";
            std::cin >> input;

            // input의 값이 1이냐 2이냐 아니냐에 따른 조건
            switch (input)
            {
            case 1:
                std::cout << "스탠드" << std::endl;
                std::cout << std::endl;

                // 두 참여자의 카드 비교

                std::cout << "컴퓨터가 뽑은 카드 : " << computerDraw << std::endl;
                std::cout << "컴퓨터의 카드 합 : " << computerSum << std::endl;
                std::cout << std::endl;

                std::cout << "여러분이 뽑은 카드 : " << playerDraw << std::endl;
                std::cout << "여러분의 카드 합 : " << playerSum << std::endl;
                std::cout << std::endl;

                // 다시 여기서 경우의 수 따지기
                // 내가 더 크거나, 상대가 더 크거나, 똑같거나
                if (playerSum > computerSum)
                {
                    std::cout << "여러분의 카드 합이 더 커서 승리했습니다" << std::endl; 
                    std::cout << "축하합니다" << std::endl;

                    // 끝났으니까 게임 오버
                    gameOver = true;
                }
                else if (playerSum < computerSum)
                {
                    std::cout << "컴퓨터가 카드 합이 더 커서 여러분이 졌습니다" << std::endl;

                    gameOver = true;
                }
                else
                {
                    // 둘이 똑같으면...무승부니까 한 판 더
                    std::cout << "두 참여자의 카드 합이 똑같습니다" << std::endl;
                    std::cout << "무승부 처리하고 다시 게임을 시작합니다" << std::endl;

                    playerSum = 0;
                    computerSum = 0;
                    
                    // 게임오버가 아니므로, 그대로 진행
                }
                break;

            case 2:
                std::cout << "드로우" << std::endl;
                std::cout << "카드를 한 장 더 뽑습니다" << std::endl;
                std::cout << std::endl;

                // 한 장 더 뽑으면 반복문 처음부터 다시 해야 하므로 별도 조치 없음
                break;

            default :
                std::cout << "입력이 잘못했습니다. 다시 입력해주세요." << std::endl;
                break;
            }

            // 여기까지 왔을 때, 입력을 잘 했거나, 잘못했거나 둘 중 하나

            // 잘 했으면 반복 입력 없이 반복문 중단
            // if (input == 1 || input == 2)
            // {
            //      break;
            // }

            if (input == 1 || input == 2)break; // 위에 있는 주석처리된 break와 똑같다

            // if문 타이핑 운용법 : 각 조건에서 (if, else if, else)실행할 코드가 하나밖에 없는 경우 {}를 생략할 수 있다
        }
    }

    // 큰 while문을 나왔으면 게임은 완전히 끝난 것이므로, 게임오버 안내를 해주고 마치도록 한다
    std::cout << "이것으로 블랙잭 게임을 종료합니다. 고생하셨습니다" << std::endl;
}
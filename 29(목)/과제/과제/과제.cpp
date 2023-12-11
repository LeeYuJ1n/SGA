#include <iostream>
#include <Windows.h>
#include <stdlib.h>

int main()
{
    int computerCard = 0, computerAddCard = 0;
    int playerCard = 0, playerAddCard = 0;
    int inputSelect_1 = 0;
    bool loop = true;

    srand(GetTickCount64());

    computerCard = rand() % 13 + 1;
    playerCard = rand() % 13 + 1;

    std::cout << "블랙잭 게임에 오신 것을 환영합니다" << std::endl;
    std::cout << std::endl;

    Sleep(3000);
    system("cls");

    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "카드 정보" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "플레이어 카드(합) : " << playerCard << std::endl;
    std::cout << "상대방 카드(합) : 비공개" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "메뉴를 선택해주세요" << std::endl;
    std::cout << "[ 메뉴 1 ] 계속(드로우)" << std::endl;
    std::cout << "[ 메뉴 2 ] 지금 비교(스탠드)" << std::endl;

    while (loop)
    {
        std::cout << "입력 : ";
        std::cin >> inputSelect_1;

        switch (inputSelect_1)
        {
        case 1:
            if (playerCard <= 21)
            {
                while (loop)
                {
                    system("cls");

                    inputSelect_1 = 0;
                    playerAddCard = rand() % 13 + 1;
                    computerAddCard = rand() % 13 + 1;
                    playerCard = playerCard + playerAddCard;
                    computerCard = computerCard + computerAddCard;

                    if (playerCard + playerAddCard > 21)
                    {
                        std::cout << "패배" << std::endl;
                        std::cout << "플레이어 카드 : " << playerCard << " / 뽑은 카드 : " << playerAddCard << std::endl;
                        std::cout << "상대방 카드 : " << computerCard << " / 뽑은 카드 : " << computerAddCard << std::endl;
                        std::cout << "플레이어 카드 합이 21이 넘어 패배처리되었습니다" << std::endl;
                        loop = false;
                        break;
                    }
                    else if (computerCard > 21)
                    {
                        std::cout << "승리" << std::endl;
                        std::cout << "플레이어 카드 : " << playerCard << " / 뽑은 카드 : " << playerAddCard << std::endl;
                        std::cout << "상대방 카드 : " << computerCard << " / 뽑은 카드 : " << computerAddCard << std::endl;
                        std::cout << "상대방 카드 합이 21이 넘어 패배처리되었습니다" << std::endl;
                        loop = false;
                        break;
                    }

                    std::cout << "-------------------------------------------------------------" << std::endl;
                    std::cout << "카드 정보" << std::endl;
                    std::cout << "-------------------------------------------------------------" << std::endl;
                    std::cout << "플레이어 카드(합) : " << playerCard << std::endl;
                    std::cout << "뽑은 카드 : " << playerAddCard << std::endl;
                    std::cout << "-------------------------------------------------------------" << std::endl;
                    std::cout << "상대방도 카드 한 장을 더 뽑았습니다" << std::endl;
                    std::cout << "-------------------------------------------------------------" << std::endl;
                    std::cout << std::endl;
                    std::cout << "메뉴를 선택해주세요" << std::endl;
                    std::cout << "[ 메뉴 1 ] 계속(드로우)" << std::endl;
                    std::cout << "[ 메뉴 2 ] 지금 비교(스탠드)" << std::endl;
                    std::cout << "입력 : " << std::endl;
                    std::cin >> inputSelect_1;

                    switch (inputSelect_1)
                    {
                    case 1:
                        if (playerCard <= 21 && computerCard <= 21)
                        {
                            playerAddCard = 0;
                            computerAddCard = 0;
                            break;
                        }

                    case 2:
                        if ((playerCard == 21) && (computerCard != 21))
                        {
                            std::cout << "승리" << std::endl;
                            std::cout << "플레이어 카드 : " << playerCard << std::endl;
                            std::cout << "상대방 카드 : " << computerCard << std::endl;
                            loop = false;
                            break;
                        }
                        else if (playerCard > computerCard)
                        {
                            std::cout << "승리" << std::endl;
                            std::cout << "플레이어 카드 : " << playerCard << std::endl;
                            std::cout << "상대방 카드 : " << computerCard << std::endl;
                            loop = false;
                            break;
                        }
                        else if (playerCard < computerCard)
                        {
                            std::cout << "패배" << std::endl;
                            std::cout << "플레이어 카드 : " << playerCard << std::endl;
                            std::cout << "상대방 카드 : " << computerCard << std::endl;
                            loop = false;
                            break;
                        }
                        else if ((playerCard != 21) && (computerCard == 21))
                        {
                            std::cout << "패배" << std::endl;
                            std::cout << "플레이어 카드 : " << playerCard << std::endl;
                            std::cout << "상대방 카드 : " << computerCard << std::endl;
                            loop = false;
                            break;
                        }
                        else if ((playerCard > 21) && (computerCard <= 21))
                        {
                            std::cout << "패배" << std::endl;
                            std::cout << "플레이어 카드 : " << playerCard << std::endl;
                            std::cout << "상대방 카드 : " << computerCard << std::endl;
                            loop = false;
                            break;
                        }
                        else
                        {
                            std::cout << "무승부" << std::endl;
                            break;
                        }
                        break;

                    default :
                        std::cout << "잘못입력하였습니다" << std::endl;
                        playerAddCard = 0;
                        break;
                    }
                    break;
                }
                break;
            }
        case 2:
            if ((playerCard == 21) && (computerCard != 21))
            {
                std::cout << "승리" << std::endl;
                std::cout << "플레이어 카드 : " << playerCard << std::endl;
                std::cout << "상대방 카드 : " << computerCard << std::endl;
                loop = false;
                break;
            }
            else if (playerCard > computerCard)
            {
                std::cout << "승리" << std::endl;
                std::cout << "플레이어 카드 : " << playerCard << std::endl;
                std::cout << "상대방 카드 : " << computerCard << std::endl;
                loop = false;
                break;
            }
            else if (playerCard < computerCard)
            {
                std::cout << "패배" << std::endl;
                std::cout << "플레이어 카드 : " << playerCard << std::endl;
                std::cout << "상대방 카드 : " << computerCard << std::endl;
                loop = false;
                break;
            }
            else if ((playerCard != 21) && (computerCard == 21))
            {
                std::cout << "패배" << std::endl;
                std::cout << "플레이어 카드 : " << playerCard << std::endl;
                std::cout << "상대방 카드 : " << computerCard << std::endl;
                loop = false;
                break;
            }
            else if (playerCard > 21)
            {
                std::cout << "패배" << std::endl;
                std::cout << "플레이어 카드 : " << playerCard << std::endl;
                std::cout << "상대방 카드 : " << computerCard << std::endl;
                std::cout << "플레이어 카드 합이 21이 넘어 패배처리되었습니다" << std::endl;
                loop = false;
                break;
            }
            else if (computerCard > 21)
            {
                std::cout << "승리" << std::endl;
                std::cout << "플레이어 카드 : " << playerCard << std::endl;
                std::cout << "상대방 카드 : " << computerCard << std::endl;
                std::cout << "상대방 카드 합이 21이 넘어 패배처리되었습니다" << std::endl;
                loop = false;
                break;
            }
            else
            {
                std::cout << "무승부" << std::endl;
                break;
            }
            break;

        default:
            std::cout << "제대로된 값을 입력해주세요" << std::endl;
            break;
        }
    }
}
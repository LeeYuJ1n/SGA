#include "OneCard_Class.h"

// 계산에 필요한 변수
int myCardArr[5];
int targetCardArr[5];
int randomOutput = 0;
int input = 0;

// 카드 지급, 중복 검사
void OneCard_Class::OneCardGame()
{
    // 랜덤 시드 생성
    srand(GetTickCount64());

    cout << "원카드 게임" << endl;

    cout << endl;

    cout << "계속 하실려면 Enter키를 눌러주세요" << endl;

    // Enter키 눌림을 기다림
    while (_getch() != 13) {}

    while (true)
    {
        // 플레이어 및 상대방 카드 랜덤 5장 지급
        for (int i = 0; i < 5; i++)
        {
            myCardArr[i] = rand() % 5 + 1;;
        }

        for (int i = 0; i < 5; i++)
        {
            targetCardArr[i] = rand() % 5 + 1;
        }
        break;
    }
    OneCardPlay();
}

// 카드 출력, 순서 정하기
void OneCard_Class::OneCardPlay()
{
    // 화면 초기화
    system("cls");

    // 플레이어 카드 출력
    cout << "플레이어 카드" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << myCardArr[i] << " ";
    }

    // 줄 바꿈
    cout << endl;
    cout << endl;

    // 상대방 카드 출력
    cout << "상대방 카드" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << targetCardArr[i] << " ";
    }

    // 줄 바꿈
    cout << endl;
    cout << endl;

    cout << "계속 하실려면 Enter키를 눌러주세요" << endl;

    // Enter키 눌림을 기다림
    while (_getch() != 13) {}

    bool acted = false;

    while (true)
    {
        switch (input)
        {
        case 0:
            for (int i = 0; i < 5 && !acted; i++)
            {
                for (int j = 0; j < 5 && !acted; j++)
                {
                    if (i != j && myCardArr[i] != 0 && myCardArr[j] != 0 && myCardArr[i] == myCardArr[j])
                    {
                        input = 1;
                        acted = true;
                        Player();
                    }
                }
            }

            if (!acted)
            {
                PlayerNoCard();
            }

        case 1:
            acted = false; //행동 리셋

            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (i != j && targetCardArr[i] != 0 && targetCardArr[j] != 0 && targetCardArr[i] == targetCardArr[j])
                    {
                        input = 0;
                        acted = true;
                        Target();
                        break;
                    }
                }
                if (acted) break;
            }

            if (!acted)
            {
                TargetNoCard();
            }
        }
    }
}

void OneCard_Class::Player()
{
    // 화면 초기화
    system("cls");

    cout << "플레이어 순서입니다" << endl;

    cout << endl;

    cout << "중복되는 카드를 버린 후 카드 현황" << endl;

    // 중복되는 카드 2장을 0으로 처리
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 6; j++)
        {
            if (myCardArr[i] == myCardArr[j])
            {
                myCardArr[i] = 0;
                myCardArr[j] = 0;
            }
        }
    }

    // 중복되는 카드 2장을 0으로 처리한 후 결과 출력
    int myZeroCount = 0;

    for (int i = 0; i < 5; i++)
    {
        cout << myCardArr[i] << " ";

        if (myCardArr[i] == 0)
        {
            myZeroCount++;
        }
    }

    if (myZeroCount == 5)
    {
        Player_OneCardSystem();
    }

    // 줄 바꿈
    cout << endl;
    cout << endl;

    cout << "순서를 마칩니다" << endl;

    cout << endl;

    cout << "계속 하실려면 Enter키를 눌러주세요" << endl;

    // Enter키 눌림을 기다림
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::PlayerNoCard()
{
    system("cls");

    cout << "플레이어 카드 중에 버릴 수 있는 카드가 없어 카드 한 장을 지급합니다" << endl;

    for (int i = 0; i < 5; i++)
    {
        if (myCardArr[i] == 0)
        {
            input = 1;
            myCardArr[i] = rand() % 5 + 1;
            cout << "지급된 카드 : " << myCardArr[i] << endl;
            break;
        }
    }

    cout << endl;

    cout << endl;

    cout << "계속 하실려면 Enter키를 눌러주세요" << endl;

    // Enter키 눌림을 기다림
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::Target()
{
    // 화면 초기화
    system("cls");

    cout << "상대방 순서입니다" << endl;

    cout << endl;
    
    cout << "중복되는 카드를 버린 후 카드 현황" << endl;

    // 중복되는 카드 2장을 0으로 처리
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 6; j++)
        {
            if (targetCardArr[i] == targetCardArr[j])
            {
                targetCardArr[i] = 0;
                targetCardArr[j] = 0;
            }
        }
    }

    // 중복되는 카드 2장을 0으로 처리한 후 결과 출력
    int targetZeroCount = 0;

    for (int i = 0; i < 5; i++)
    {
        cout << targetCardArr[i] << " ";

        if (targetCardArr[i] == 0)
        {
            targetZeroCount++;
        }
    }

    if (targetZeroCount == 5)
    {
        Target_OneCardSystem();
    }

    // 줄 바꿈
    cout << endl;
    cout << endl;

    cout << "순서를 마칩니다" << endl;

    cout << endl;

    cout << "계속 하실려면 Enter키를 눌러주세요" << endl;

    // Enter키 눌림을 기다림
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::TargetNoCard()
{
    system("cls");

    cout << "상대방 카드 중에 버릴 수 있는 카드가 없어 카드 한 장을 지급합니다" << endl;

    input = 0;

    for (int i = 0; i < 5; i++)
    {
        if (targetCardArr[i] == 0)
        {
            targetCardArr[i] = rand() % 5 + 1;
            cout << "지급된 카드 : " << targetCardArr[i] << endl;
            break;
        }
    }

    cout << endl;

    cout << endl;

    cout << "계속 하실려면 Enter키를 눌러주세요" << endl;

    // Enter키 눌림을 기다림
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::Player_OneCardSystem()
{
    // 화면 초기화
    system("cls");

    int input;
    bool loop = true;

    cout << "플레이어의 카드가 1장 남았습니다. 원카드를 외치겠습니까?" << endl;
    cout << "1. 원카드 외치기 / 2. 이어서 진행하기" << endl;
    cout << "입력 : ";
    cin >> input;


    // 플레이어의 현재 보유 카드 출력
    for (int i = 0; i < 5; i++)
    {
        cout << myCardArr[i] << " ";
    }

    while (loop)
    {
        switch (input)
        {
        case 1:
            system("cls");

            PlayerWin();
            break;

        case 2:
            system("cls");

            cout << "게임을 이어서 진행합니다" << endl;

            cout << endl;

            for (int i = 0; i < 5; i++)
            {
                if (myCardArr[i] == 0)
                {
                    myCardArr[i] = rand() % 5 + 1;
                    break;
                }
                cout << "지급된 카드 : " << myCardArr[i] << endl;
                break;
            }

            cout << "계속 하실려면 Enter키를 눌러주세요" << endl;

            // Enter키 눌림을 기다림
            while (_getch() != 13) {}

            OneCardPlay();
        }
    }
}

void OneCard_Class::Target_OneCardSystem()
{
    // 화면 초기화
    system("cls");

    cout << "패배" << endl;
    
    // 상대방이 원카드를 외칠 시 플레이어에게 벌칙으로 랜덤 카드 1장 지급
    bool foundZero = false;

    for (int i = 0; i < 5; i++)
    {
        if (myCardArr[i] == 0)
        {
            myCardArr[i] = rand() % 5 + 1;
            foundZero = true;
            break;
        }
    }

    if (!foundZero) 
    {
        cout << "카드 배열에 0인 값이 없습니다." << endl;
    }
    cout << endl;

    cout << "계속 하실려면 Enter키를 눌러주세요" << endl;

    // Enter키 눌림을 기다림
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::PlayerWin()
{
    cout << "승리" << endl;

    // Enter키 눌림을 기다림
    while (_getch() != 13) {}

    return;
}

void OneCard_Class::PlayerLoser()
{
    cout << "패배" << endl;
}
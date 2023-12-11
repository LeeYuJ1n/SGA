#include "OneCard_Class.h"

// ��꿡 �ʿ��� ����
int myCardArr[5];
int targetCardArr[5];
int randomOutput = 0;
int input = 0;

// ī�� ����, �ߺ� �˻�
void OneCard_Class::OneCardGame()
{
    // ���� �õ� ����
    srand(GetTickCount64());

    cout << "��ī�� ����" << endl;

    cout << endl;

    cout << "��� �ϽǷ��� EnterŰ�� �����ּ���" << endl;

    // EnterŰ ������ ��ٸ�
    while (_getch() != 13) {}

    while (true)
    {
        // �÷��̾� �� ���� ī�� ���� 5�� ����
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

// ī�� ���, ���� ���ϱ�
void OneCard_Class::OneCardPlay()
{
    // ȭ�� �ʱ�ȭ
    system("cls");

    // �÷��̾� ī�� ���
    cout << "�÷��̾� ī��" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << myCardArr[i] << " ";
    }

    // �� �ٲ�
    cout << endl;
    cout << endl;

    // ���� ī�� ���
    cout << "���� ī��" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << targetCardArr[i] << " ";
    }

    // �� �ٲ�
    cout << endl;
    cout << endl;

    cout << "��� �ϽǷ��� EnterŰ�� �����ּ���" << endl;

    // EnterŰ ������ ��ٸ�
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
            acted = false; //�ൿ ����

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
    // ȭ�� �ʱ�ȭ
    system("cls");

    cout << "�÷��̾� �����Դϴ�" << endl;

    cout << endl;

    cout << "�ߺ��Ǵ� ī�带 ���� �� ī�� ��Ȳ" << endl;

    // �ߺ��Ǵ� ī�� 2���� 0���� ó��
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

    // �ߺ��Ǵ� ī�� 2���� 0���� ó���� �� ��� ���
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

    // �� �ٲ�
    cout << endl;
    cout << endl;

    cout << "������ ��Ĩ�ϴ�" << endl;

    cout << endl;

    cout << "��� �ϽǷ��� EnterŰ�� �����ּ���" << endl;

    // EnterŰ ������ ��ٸ�
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::PlayerNoCard()
{
    system("cls");

    cout << "�÷��̾� ī�� �߿� ���� �� �ִ� ī�尡 ���� ī�� �� ���� �����մϴ�" << endl;

    for (int i = 0; i < 5; i++)
    {
        if (myCardArr[i] == 0)
        {
            input = 1;
            myCardArr[i] = rand() % 5 + 1;
            cout << "���޵� ī�� : " << myCardArr[i] << endl;
            break;
        }
    }

    cout << endl;

    cout << endl;

    cout << "��� �ϽǷ��� EnterŰ�� �����ּ���" << endl;

    // EnterŰ ������ ��ٸ�
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::Target()
{
    // ȭ�� �ʱ�ȭ
    system("cls");

    cout << "���� �����Դϴ�" << endl;

    cout << endl;
    
    cout << "�ߺ��Ǵ� ī�带 ���� �� ī�� ��Ȳ" << endl;

    // �ߺ��Ǵ� ī�� 2���� 0���� ó��
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

    // �ߺ��Ǵ� ī�� 2���� 0���� ó���� �� ��� ���
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

    // �� �ٲ�
    cout << endl;
    cout << endl;

    cout << "������ ��Ĩ�ϴ�" << endl;

    cout << endl;

    cout << "��� �ϽǷ��� EnterŰ�� �����ּ���" << endl;

    // EnterŰ ������ ��ٸ�
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::TargetNoCard()
{
    system("cls");

    cout << "���� ī�� �߿� ���� �� �ִ� ī�尡 ���� ī�� �� ���� �����մϴ�" << endl;

    input = 0;

    for (int i = 0; i < 5; i++)
    {
        if (targetCardArr[i] == 0)
        {
            targetCardArr[i] = rand() % 5 + 1;
            cout << "���޵� ī�� : " << targetCardArr[i] << endl;
            break;
        }
    }

    cout << endl;

    cout << endl;

    cout << "��� �ϽǷ��� EnterŰ�� �����ּ���" << endl;

    // EnterŰ ������ ��ٸ�
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::Player_OneCardSystem()
{
    // ȭ�� �ʱ�ȭ
    system("cls");

    int input;
    bool loop = true;

    cout << "�÷��̾��� ī�尡 1�� ���ҽ��ϴ�. ��ī�带 ��ġ�ڽ��ϱ�?" << endl;
    cout << "1. ��ī�� ��ġ�� / 2. �̾ �����ϱ�" << endl;
    cout << "�Է� : ";
    cin >> input;


    // �÷��̾��� ���� ���� ī�� ���
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

            cout << "������ �̾ �����մϴ�" << endl;

            cout << endl;

            for (int i = 0; i < 5; i++)
            {
                if (myCardArr[i] == 0)
                {
                    myCardArr[i] = rand() % 5 + 1;
                    break;
                }
                cout << "���޵� ī�� : " << myCardArr[i] << endl;
                break;
            }

            cout << "��� �ϽǷ��� EnterŰ�� �����ּ���" << endl;

            // EnterŰ ������ ��ٸ�
            while (_getch() != 13) {}

            OneCardPlay();
        }
    }
}

void OneCard_Class::Target_OneCardSystem()
{
    // ȭ�� �ʱ�ȭ
    system("cls");

    cout << "�й�" << endl;
    
    // ������ ��ī�带 ��ĥ �� �÷��̾�� ��Ģ���� ���� ī�� 1�� ����
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
        cout << "ī�� �迭�� 0�� ���� �����ϴ�." << endl;
    }
    cout << endl;

    cout << "��� �ϽǷ��� EnterŰ�� �����ּ���" << endl;

    // EnterŰ ������ ��ٸ�
    while (_getch() != 13) {}

    OneCardPlay();
}

void OneCard_Class::PlayerWin()
{
    cout << "�¸�" << endl;

    // EnterŰ ������ ��ٸ�
    while (_getch() != 13) {}

    return;
}

void OneCard_Class::PlayerLoser()
{
    cout << "�й�" << endl;
}
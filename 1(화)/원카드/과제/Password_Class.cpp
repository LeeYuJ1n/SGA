#include "Password_Class.h"

using namespace std;

void Password_Class::Login_Print()
{
    int inputPassword = 0; // ��й�ȣ �Է��� ���� ���� ����

    cout << "�̴ϰ��� ���忡 ���� ���� ȯ���մϴ�" << endl;
    cout << endl;

    while (true)
    {
        cout << "----------------------------------------------------" << endl;
        cout << "��й�ȣ�� �Է����ּ���" << endl;
        cout << "----------------------------------------------------" << endl;
        cin >> inputPassword; // ��й�ȣ �Է�

        if (inputPassword == 20220112) // ��й�ȣ�� �Źٸ� ��� ���� �޴��� �̵�
        {
            system("cls");
            cout << "��й�ȣ Ȯ���� �Ϸ�Ǿ����ϴ�" << endl;
            Sleep(3000);
            false;
        }
        else // ��й�ȣ�� �Źٸ��� ���� ��� �ٽ� �����
        {
            system("cls");
            cout << "�Է��Ͻ� ��й�ȣ�� �Źٸ��� �ʽ��ϴ�" << endl;
        }
    }
}
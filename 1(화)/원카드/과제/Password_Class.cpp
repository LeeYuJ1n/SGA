#include "Password_Class.h"

using namespace std;

void Password_Class::Login_Print()
{
    int inputPassword = 0; // 비밀번호 입력을 위한 변수 선언

    cout << "미니게임 월드에 오신 것을 환영합니다" << endl;
    cout << endl;

    while (true)
    {
        cout << "----------------------------------------------------" << endl;
        cout << "비밀번호를 입력해주세요" << endl;
        cout << "----------------------------------------------------" << endl;
        cin >> inputPassword; // 비밀번호 입력

        if (inputPassword == 20220112) // 비밀번호가 옮바른 경우 다음 메뉴로 이동
        {
            system("cls");
            cout << "비밀번호 확인이 완료되었습니다" << endl;
            Sleep(3000);
            false;
        }
        else // 비밀번호가 옮바르지 못할 경우 다시 물어보기
        {
            system("cls");
            cout << "입력하신 비밀번호가 옮바르지 않습니다" << endl;
        }
    }
}
#include <iostream>

using namespace std;

template <typename T>
T Add_Print(T a, T b)
{
    int x = 0, y = 0;
    result = x + y;

    return result;
}

int main()
{
    bool loop = true;
    while (loop)
    {
        int input = 0;

        cout << "1. 두 수의 덧셈 / 2. 아이디와 비밀번호 일력 후 출력" << endl;
        cout << "입력 : ";
        cin >> input;

        switch (input)
        {
        case 1:
            cout << "두 수의 덧셈" << endl;
            cout << "첫 번째 숫자 입력 : ";
            cin >> x;

            cout << endl;

            cout << "두 번째 숫자 입력 : ";
            cin >> y;

            cout << "덧셈 결과" << endl;
            cout << x << " + " << y << " = " << Add_Print<int>(result) << endl;
            break;

        case 2:

            break;

        case 3:
            cout << "프로그램 종료";
            loop = false;
            break;

        default :
            cout << "잘못된 입력입니다. 다시 입력해주세요";
            break;
        }
        continue;
    }
}

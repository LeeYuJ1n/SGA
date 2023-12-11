#include <iostream>
#include "Josephus.h"
#include "UserCert.h"

using namespace std;

int main()
{
    int input = 0;
    Josephus* josephus = new Josephus();
    UserCert* uc = new UserCert();
    
    cout << "1. 요세푸스 / 2. 인물 판별" << endl;
    cout << "입력 : ";
    cin >> input;
    
    while (true)
    {
        switch (input)
        {
        case 1:
            cout << "요세푸스" << endl;
            cout << endl;
            josephus->Start();
            break;

        case 2:
            cout << "인물 판별" << endl;
            cout << endl;
            uc->Start();
            break;
        }
        continue;
    }
}
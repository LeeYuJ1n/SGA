#include <iostream>
#include "ListClass.h"

using namespace std;

int main()
{
    ListClass* lc = new ListClass();

    list<int> myList = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    cout << "호출하기" << endl;
    lc->Call(3, myList);
    
    cout << endl;

    cout << "출력하기" << endl;
    lc->Print(myList);

    cout << endl;

    cout << "삽입하기" << endl;
    lc->Insert(1, myList, 112);
    lc->Print(myList);

    cout << endl;

    cout << "삭제하기" << endl;
    lc->Erase(9, myList);
    lc->Print(myList);

    cout << "추가하기" << endl;
    lc->Emplace(1, myList, 50);
    lc->Print(myList);

    return 0;
}
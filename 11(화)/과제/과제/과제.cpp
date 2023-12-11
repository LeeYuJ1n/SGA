#include <iostream>
#include <windows.h>
#include "Class.h"

int main()
{
    // Class.h 인스턴스 생성
    Class c;

    std::cout << "2023년 7월 11일 과제" << std::endl;
    std::cout << std::endl;
    std::cout << "1. 지금까지 만든 것 처럼 캐릭터를.. 이번에는 클래스로 만들어주세요" << std::endl;
    std::cout << "2. 캐릭터에는 변수가 셋 이상 있어야 됩니다. 최소 지정 변수는 : id, hp, 공격력" << std::endl;
    std::cout << "3. 2에서 지정된 최소 지정 변수 셋은 모두 열람만 가능하고, 수정 불가능한 int 혹은 float이어야 합니다" << std::endl;
    std::cout << "4. 특히 id는 단독 수정 가능한 함수가 없어야 합니다(매개변수 하나 넣고 id 바꾸기)" << std::endl;
    std::cout << "5. 클래스로 된 인스턴스를 둘 이상 만들어주세요" << std::endl;
    std::cout << "6. 두 인스턴스가 함수를 통해서 서로를 공격할 수 있도록 해주세요" << std::endl;
    std::cout << "7. 6에서 만든 함수 역시 클래스 안에 있어야 합니다. class{} 밖에 있으면 안 됩니다" << std::endl;

    // 딜레이 3초
    Sleep(5000);

    // 콘솔 화면 초기화
    system("cls");
    
    // 함수 호출
    c.print();

    // 딜레이 10초
    Sleep(10000);

    // 함수 호출
    c.pvpsystem();

    // 컴퓨터에게 전달
    return 0;
}
#include <iostream>

// 헤더
#include "MySingleton.h"

int main()
{
    MySingleton::Instance()->Init();             // 싱글턴 인스턴스의 초기화
    MySingleton::Instance()->RunCalculator();    // 싱글턴 인스턴스의 내부 함수를 실행
    
    // 만약 계산기가 public변수였다면...
    // MySingleton::Instance()->calc->Run(); ← 이렇게도 실행이 가능했을 것

    // 기본은 똑같다 : 계산기 클래스가 있고, 다른 곳에서 실행한 것 뿐
    // 그리고 중간에 싱글턴이 중간유통처럼 한 번 더 끼어든 것 뿐

    // 그 중간유통이 중요한 것 = WinAPI처럼 main 자체가 복잡할 때는
    // 거기서 벌어질 더 복잡한 코드들을 따로 다른 곳에서 정리해줄 곳이 필요하니까

    // 그 정리와 관리를 별도의 처리 없이도 어디서든지 똑같은 위치에서 다뤄줘야 하니까

    // → 그게 싱글턴을 사용하는 이유 (=main에서 두 줄만 가지고 계산기 실행하기)
}
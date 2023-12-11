// #include <iostream>
#include "header_1.h" // 내가 만든 헤더는 <> 대신  ""로 포함

int main()
{
    // 캐릭터 두 명의 초기 능력치를 정하자
    chara1.hitPoint = 1000;
    chara1.atk = 100;

    chara2.hitPoint = 2000;
    chara2.atk = 200;

    // 한 번 출력
    PrintChara(chara1); // 매개변수로 차라1 설정 = 차라1을 출력
    PrintChara(chara2); // 차라2를 출력

    // 레벨업
    LevelUp_1(); // 1 레벨업
    LevelUp_2(); // 2도 레벨업

    // 또 출력
    PrintChara(chara1);
    PrintChara(chara2);

    // 서로 공격
    Attack(chara1, chara2); // 1이 2를 공격
    Attack(chara2, chara1); // 2가 1를 공격

    // 또 출력
    PrintChara(chara1);
    PrintChara(chara2);

    // 결과 : 모든 함수가 정상적으로 작성, 정상적으로 수행
    // 그런데..... 어떤 함수는 결과가 제대로 반영되지 않았다
    // → 코딩이 잘못된 것이 아니다. 잘못은 C++이 했다
}

void LevelUp_1() // 레벨업 1, 캐릭터1을 레벨업
{
    chara1.hitPoint += 100;
    chara1.atk += 1;
}
// 게임마다, 최적화 정도에 따라 다르지만, 캐릭터가 다르면 레벨업 함수까지 달라지는 경우도 있긴 하다
// 대표적인 사례가 클래식(테이블탑) RPG가 원작이 되는 컴퓨터용 RPG
// * (토막팁) 최적화 : 일반적으로는 앱의 실행 속도를 높이는 것
// 게임에서는 앞의 뜻과 더불어서 같은 속도에서의 사양 수준을 낮추거나
// 같은 속도 같은 절차에서 개발자가 이해하는 과정의 단계를 줄이는 것도 포함

void LevelUp_2() // 캐릭터 2를 레벨업
{
    chara2.hitPoint += 200;
    chara2.atk += 2;
}

void PrintChara(Character thisOne) // 매개변수를 받아서
{
    // 매개변수를 받은 캐릭터의.....
    std::cout << "체력 : " << thisOne.hitPoint << std::endl;
    std::cout << "공격력 : " << thisOne.atk << std::endl;
    // .....스테이터스를 그때그때 출력
}
// 헤더에서 함수가 선언될 때 필요한 기능이 포함되지 않았더라도
// 정의하는 부분에서(지금의 경우는 이 cpp파일) 필요 기능이 포함돼있으면
// 함수 정의는 문제없이 진행 가능

// .....혹은 그 헤더 파일이 정말로 프로젝트에서 절대 빠지지 않고 main()이 있는 cpp 파일에서도 반드시 로딩된다는 보장이 있으면...
// 그냥 cpp에 있는 #include 부분을 헤더로 옮기는 것도 가능한 선택

void Attack(Character actor, Character target)
{
    // 행동하는 쪽의 공격력으로 표적이 된 쪽의 체력을 낮추자
    target.hitPoint -= actor.atk;

    // 밑에 결과도 출력
    std::cout << "공격이 발생했습니다" << std::endl;
    std::cout << "공격받은 쪽 현재 남은 체력 : " << target.hitPoint << std::endl;
}
#include <iostream>
#include "Human.h" // 인간 로딩
#include "Group.h" // 인간의 집합 로딩
#include "Sample.h" // 실습용 클래스 헤더
#include "Student.h" // 학생 로딩

int main()
{
    // 포인터 인스턴스를 이용한 동적 할당
    Human* human1 = new Human(20, 1, 170, 70, 100); // 나이 20, 성별은 "1번", 키 170, 체중 70, 취미는 코드 기준 100
    Human* human2 = new Human(40, 2, 430, 140, 200); // 인간 1의 모든 것의 2배(비현실적이지만 코드니까)

    Human* humanBlack = new Human(); // "빈 인간" 즉 인간이라는 개념의 정보를 알기 위한 모든 값이 0인 인간

    // 위 인스턴스 중 인간 1과 인간 2는 생성자에 의해 자기 정보의 일부를 출력할 것(예상)

    // 이 인스턴스를 활용해서 필요한 연산을 수행
    std::cout << human1 -> GetHeight() << std::endl;
    std::cout << human2 -> GetWeight() << std::endl;
    std::cout << human2 -> GetHobby() << std::endl;

    // ---------------------------------------------

    // 인간들의 집합을 다른 클래스에서 동적 할당

    Group* group = new Group(human1, human2, humanBlack); // 위에 만든 인간1, 인간2, 빈 인간을 구성원으로

    // 그룹이 만들어졌으니 그룹에 있는 함수도 실행 가능할 것
    group->Print_HW_Ratio(); // 인간들의 키, 체중 비율을 출력

    // 위 그룹 클래스 작성 / 생성 / 호출 / 사용을 통해서 내릴 수 있는 결론

    // : 한 클래스에서 다른 클래스를 가져와서 변수나 대상으로 써먹을 수도 있다
    // 이렇게 상관이 없지만 그냥 끌어와서 다른 클래스를 쓰는 것을 클래스 간의 참조라고 한다

    // ----------------------------------------------

    // 상속된 학생을 만들고 호출해보기

    Student* student = new Student(33, 3, 233, 133, 333, 3333, 3, 3);

    student->PrintMe(); // 학생에게 지정된 public용 코드와 더불어서, 인간의 protected 함수까지 간접 호출
}
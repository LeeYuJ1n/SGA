#include <iostream>
#include "Header.h"
#include "Character.h"

int main()
{
	srand(GetTickCount64());

	//캐릭터 두 명 인스턴스로 만들기

	// Character character1;
	// Character character2;

	//이니시에이트

	// character1.Init(1, (float)GetRandom(500, 1000), GetRandom(50, 100));
	// character2.Init(2, (float)GetRandom(500, 1000), GetRandom(50, 100));

	// 생성자를 이용해서 캐릭터 만들기
	Character character1(1, (float)GetRandom(500, 1000), GetRandom(50, 100), 1, 2, 3);
	Character character2(2, (float)GetRandom(500, 1000), GetRandom(50, 100), 1, 2, 2); // 멤버 이니셜라이저 사용
	// 위 처럼() 안에 매개변수를 넣어서 변수를 할당하고 인스턴스 생성 가능

	// 그러면 생성자에 매개변수를 안 쓰면 인스턴스 생성은 못하나?
	
	// Character character3; // 이렇게는 생성 가능
	// Character character4(); // 이렇게는 생성 불가능

	// 생성자를 선언에 사용할 때 매개변수 없이 ()를 쓰면 컴퓨터가 "매개변수를 안 줬다"라고 생각해서 오류를 일으킴
	// → 생성자는 작성도 조금 특이하지만, 호출도 약간 다른 함수와는 다르다
	// → 생성자에 매개변수가 없거나 쓰기 싫을 때는 그냥 ()까지 다 떼고 ;을 붙이면 된다
	// → 이럴 때 생성되는, 매개변수가 지정되지 않은 생성자를 기본 생성자라고 한다

	// 생성자를 작성할 때, 멤버 이니셜라이저를 사용하면 더 정확하고 빠른 코딩 가능
	// (캐릭터 헤이더에 이니셜라이저 설명 참조)
	// 반면 생성자 초기화는 개발자의 의도를 모두와 쉡게 공유 가능
	
	// 마찬가지로 인스턴스를 만들 때도, 편하게 만드는 방법 외에
	// (컴퓨터를 낭비하면서) 값을 완전하게 복사해서 만드는 방법
	// (약간 숙달이 늦지만) 안전하면서 동시에 빠르게 편하게 만드는 방법 존재

	// 예시 전용 인스턴스들
	Character character3(0, 0, 0, 0, 0, 0); // ← 기본적인 인스턴스 생성(쉽고 편하다)
	// ← 메모리에 고대로 값을 쑤셔넣는 방법이라 다소 불안하고 느리다(쓰기 편하다)

	Character character4 = *new Character(0, 0, 0, 0, 0, 0); // 값 복사 생성
	// 다른 메모리 영역에 임시 인스턴스를 또 만들고, 그 값을 복사해오기
	// 데이터의 안전이란 측면에서는 안전하단 것이 장점
	// **주의** 본 코드는 사실 비추 : 이유는 이 방법이 기본적으로 사본을 만드는 방식

	// ** 같이 참조 필요** new 코드 : 포인터인 동시에, "메모리 할당"이라는 개념
	// "별도의 메모리 영역에 클래스가 들어갈 자리를 또 하나 지정해놓고 시작한다"는 뜻
	// → 이 개념을 동적 할당이라고 한다(인간이 필요에 의해 직접 메모리를 점거)

	// 그런데 위의 character4의 경우 : new로 만든 인스턴스 자체를 쓰는 게 아니다
	// → 쓰지도 않을 사본을 만들어놓고 값을 복사해온 후, 만들어진 객체는 방치
	// → 이 경우, 사본은 언어나 환경에 따라 자동으로 지워질 수도, 혹은
	//    앱이 끝나는 날까지 영원히 메모리 한구석을 방황할 수도(=메모리 낭비)
	//    특히 C++은 그냥 안 지워진다고 생각을 해야 한다(옛날 언어라서 이런 거 관리 잘 안해준다)

	// 위 코드가 비추라면, 저 방법의 장점을 발휘할 다른 문법은 뭐가 있는가?

	// ------------------------------------------------------------

	// * 앞으로 자주 사용해야 할, 안전하고 빠르고 호출이 쉬운 문법
	//   → 클래스 ㅍ인터로 인스턴스를 생성

	Character* character5 = new Character(0, 1, 500, 1000, 0, 0); // 아이디, 체력, 공격력, 마나
	// 포인터 변수를 생성한 후, 다시 new로 메모리 어딘가에 동적 할당을 하고,
	//그 new의 메모리 위치를 포인터 변수의 값으로 할당
	
	// 객체 그 자체를 지칭하기 위한 변수명은 없다(new Character)
	// 그 '이름 없는 새 변수'를 가리키기 위한 포인터 변수명은 있다(character5)

	// 그럼 이 인스턴스의 호출은 포인터 변수명(character5)으로 하면 된다

	// 실제 사용 예(포인터 매개변수 등에 썻던 -> 연산자를 main에서 사용)
	character5 -> PrintMe(); // character5라는 이름으로 지정된 위치의, new Character의 정보 출력

	// ------------------------------------------------------------

	//출력
	character1.PrintMe();
	character2.PrintMe();

	system("pause");

	while (true)
	{
		system("cls");

		character1.Attack(&character2, GetRandomOffset());

		if (character2.GetDead()) break;

		Sleep(3000);

		system("cls");

		character2.Attack(&character1, GetRandomOffset());

		if (character1.GetDead()) break;

		Sleep(3000);
	}

	std::cout << "싸움이 끝났습니다..." << std::endl;
	std::cout << "앱을 종료합니다." << std::endl;
}

int GetRandom(int _start, int _end)
{
	return (rand() % (_end - _start)) + _start;
}

float GetRandomOffset()
{
	return (float)GetRandom(10, 20) / (float)GetRandom(10, 20);
}
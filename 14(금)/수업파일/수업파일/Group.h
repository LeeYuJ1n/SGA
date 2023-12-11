#pragma once
#include "Human.h"

class Group // 인간들의 집합을 그룹이라고 해봅시다
{
private:
	// 집합이니까 인간이 있겠지요
	Human* human1;
	Human* human2;
	Human* human3; // 3명까지 적어봅시다

	// 매개변수를 받았을 때, 그 매개변수의 하위정보로 동적 할당하는 함수
	// void MakeHuman(Human* target, Human* original) // 타겟 : 만들 대상, 오리지널 : 원본
	// {
	// 	int age = original->GetAge();
	// 	int gender = original->GetGender();
	// 	float height = original->GetHeight();
	// 	float weight = original->GetWeight();
	// 	int hobby = original->GetHobby();
	// 
	// 	target = new Human(age, gender, height, weight, hobby);
	// }

public:
	// 여기서는 간단히 생성자와 출력용 함수를 생각해봅시다

	// 기본 생성자
	Group()
	{
		human1 = new Human(); // 기본 생성자는 만들어지는 변수도 기본 생성자
		human2 = new Human();
		human3 = new Human();

		// 위는 동적 할당을 써서 사본을 만드는 경우
		// 반대로 외부에 있는 변수를 받아와서 기준을 정해야 한다면
		// 할당을 고의로 하지 않고, 포인터를 "무효값"으로 설정해둔다

		// 포인터 무효값(혹은 "널 포인터")설정하는 방법
		human1 = nullptr;
		human2 = nullptr;
		human3 = nullptr;
		// 이렇게 널 포인터와 외부 변수 받는 클래스를 만들면,
		// 아래 생성자에서도 멤버 이니셜라이저로 변수 할당 가능
	}

	// 진짜 생성자(매개변수 있는)
	Group(Human* entity1, Human* entity2, Human* entity3) // entity : 외부와 구분해서 인식 가능한 존재라는 뜻
		// : human1(entity1), // 이렇게 멤버 이니셜라이저를 쓸 경우, 외부의 개체의 포인터를 끌어오게 된다
		// human2(entity2), // 이 경우, 클래스의 인스턴스에 외부에 끌려다닐 위험이 생긴다
		// human3(entity3) // 장점 : 외부와 연계성이 높다, 단전 : 외부 인스턴스가 바뀌면 여기까지 위험
	{
		// 동적 할당을 변수에 사용하고 싶을 떄는 멤버 이니셜라이저보다 여기서 직접 코딩하는 게 낫다
		// : "이 변수는 동적 할당으로직접 만들 겁니다"라고 의도를 공유하기도 좋다

		// 이렇게 만들면 외부의 실체와는 별개로 사본을 하나 더 만들어서 그룹 클래스를 씁니다
		// MakeHuman(human1, entity1);
		// MakeHuman(human2, entity2);
		// MakeHuman(human3, entity3);

		// 임시 코드 : 직접 동적 할당을 해보겠습니다
		human1 = new Human(1, 2, 3, 4, 5);
		human2 = new Human(6, 7, 8, 9, 10);
		human3 = new Human(11, 12, 13, 14, 15);

		// 휴먼의 안에 ImOut 함수가 있으니 휴먼이 만들어지는 시점에서 한 번 출력은 됐을 겁니다

		// 별개로 여기서 출력을 한 번씩 더 해 보도록 합시다
		std::cout << "첫 번째 구성원의 취미 : " << human1 -> GetHobby() << std::endl;
		std::cout << "두 번째 구성원의 취미 : " << human2 -> GetHobby() << std::endl;
		std::cout << "세 번째 구성원의 취미 : " << human3 -> GetHobby() << std::endl;

		// human1->age : Human이 protected 접근 지정자를 써도 
	}

	// 위 방식처럼 클래스에서 다른 변수를 동적 할당하면, 데이터가 안전하다는 장점이 있지만
	// (외부 데이터와 연계가 끊어진다는 단점 외에) 추가로, 이 클래스로 만든 인스턴스가 지워질 때
	// 내부의 변수 데이터(동적 할당된)가 그대로 남아서 메모리를 낭비한다는 단점도 있다

	// 그래서 C++의 경우, 클래스가 지워질 때 특별한 함수를 하나 더 호출하는데
	// 그 함수의 내용을 보강함으로써 변수를 지우거나 다른 일을 하는 등 조치를 취해줄 수 있다

	// 클래스가 지워질 때 불러지는 함수를 "소멸자"(destructor, 철거꾼)라고 한다

	// 작성 사례
	~Group() // ~ 후 클래스 이름, ()는 붙이지만 보통 매개변수는 쓰지 않는다(어차피 지우고 있는데 뭐 받고 말고가 없으니)
	{
		// 여기서 변수를 지우거나 해야 한다면 코드를 작성

		// 일반적으로 생성되는 int a; 같은 일반 함수는 컴퓨터가 100% 책임지고 지워준다
		// 포이터나 구조체도 기본적으로는 컴퓨터가 지워준다

		// 개발자가 지워줘야 하는 건 무엇인가? - 개발자가 직접 동적 할당시킨(new 로 만든)것

		// 지우는 방법
		delete human1; // ← 동적 할당된 변수를 지우기
		delete human2;
		delete human3;

		// 지울 때 주의 점
		// 1. 지운다고 메모리에 있는 값이 바로 0이 되진 않는다(단지 덮어씌워져도 괜찮게 바뀔 뿐)
		// 2. 이렇게 지우다가 외부에 있는 데이터를 지우게 않게 조심할 것

		// 그래서 외부 변수를 포인터로 받아야 할 경우...(기본 생성자에서 설명)
	}

	// 편의상 .h에서 함수를 저의까지 다 하고 있습니다
	// → 가능해요. 이렇게 코딩해도 돌아갑니다
	// → 하지만 역시 cpp에서 함수를 정의하고, 여기선 가급적 선언만 하는 편을 추천드립니다

	float Get_HW_Ratio(Human* thisOne)
	{
		if (thisOne->GetWeight() == 0)
		{
			return 0;
		}

		return human1->GetHeight() / human1->GetWeight();
	}

	// 함수 하나만 더 만들어봅시다
	void Print_HW_Ratio()
	{
		std::cout << "첫 번째 구성원의 키 / 체중 비율 : " << Get_HW_Ratio(human1) << std::endl;
		std::cout << "두 번째 구성원의 키 / 체중 비율 : " << Get_HW_Ratio(human2) << std::endl;
		std::cout << "세 번째 구성원의 키 / 체중 비율 : " << Get_HW_Ratio(human3) << std::endl;
	}
};
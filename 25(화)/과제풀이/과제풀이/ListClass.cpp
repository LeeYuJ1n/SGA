#include "ListClass.h"

using namespace std;

void ListClass::Start()
{
	// 함수들이 잘 만들어졌는지 시험

	// 값 추가 (최초)
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);

	// 최초 값 출력해보기 (index로)
	for (int i = 0; i < test.size(); ++i)
	{
		cout << GetElement(test, i) << endl;
	}
	// 이게 잘 되면 : 1, 2, 3, 4, 5가 줄 바뀌면서 출력

	// 값 추가 (index로)
	insertBtIndex(&test, 1, 777); // 2번째 위치에 777 추가

	// 값 삭제 (index로)
	EraseByIndex(&test, 4); // 5번째(4순번) 위치 삭제

	// 값 추가, 삭제 결과를 한번 더 출력(연산 좀이라도 빨리지게 반복자로)
	cout << endl;

	for (list<int>::iterator it = test.begin();
		it != test.end();
		++it)
	{
		cout << *it << endl;
	}
}

// 값 호출하기
int ListClass::GetElement(list<int> source, int idx)
{
	// 값 호출을 비롯해서 리스트의 순번으로 작업을 하는 것을 모두 원리가 같다
	// 반복자를 만들어서, idx가 될 때까지 ++을 반복시키면 그 순번까지 참조가 간다
	// 그렇게 참조된 반복자의 값을 호출하거나, 위치에 새 값을 추가하거나, 삭제

	list<int>::iterator iter = source.begin();

	for (int i = 0; i < idx; ++i)
	{
		++iter;
	}
	
	// 값 호출
	return *iter;
}

// 값 추가하기
void ListClass::insertBtIndex(list<int>* target, int idx, int value)
{
	list<int>::iterator iter = target->begin();

	for (int i = 0; i < idx; ++i)
	{
		++iter;
	}
	target->insert(iter, value);
}

// 값 삭제하기
void ListClass::EraseByIndex(list<int>* target, int idx)
{
	list<int>::iterator iter = target->begin();

	for (int i = 0; i < idx; ++i)
	{
		++iter;
	}
	target->erase(iter);
}
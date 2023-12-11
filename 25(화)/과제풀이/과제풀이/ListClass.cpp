#include "ListClass.h"

using namespace std;

void ListClass::Start()
{
	// �Լ����� �� ����������� ����

	// �� �߰� (����)
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);

	// ���� �� ����غ��� (index��)
	for (int i = 0; i < test.size(); ++i)
	{
		cout << GetElement(test, i) << endl;
	}
	// �̰� �� �Ǹ� : 1, 2, 3, 4, 5�� �� �ٲ�鼭 ���

	// �� �߰� (index��)
	insertBtIndex(&test, 1, 777); // 2��° ��ġ�� 777 �߰�

	// �� ���� (index��)
	EraseByIndex(&test, 4); // 5��°(4����) ��ġ ����

	// �� �߰�, ���� ����� �ѹ� �� ���(���� ���̶� �������� �ݺ��ڷ�)
	cout << endl;

	for (list<int>::iterator it = test.begin();
		it != test.end();
		++it)
	{
		cout << *it << endl;
	}
}

// �� ȣ���ϱ�
int ListClass::GetElement(list<int> source, int idx)
{
	// �� ȣ���� ����ؼ� ����Ʈ�� �������� �۾��� �ϴ� ���� ��� ������ ����
	// �ݺ��ڸ� ����, idx�� �� ������ ++�� �ݺ���Ű�� �� �������� ������ ����
	// �׷��� ������ �ݺ����� ���� ȣ���ϰų�, ��ġ�� �� ���� �߰��ϰų�, ����

	list<int>::iterator iter = source.begin();

	for (int i = 0; i < idx; ++i)
	{
		++iter;
	}
	
	// �� ȣ��
	return *iter;
}

// �� �߰��ϱ�
void ListClass::insertBtIndex(list<int>* target, int idx, int value)
{
	list<int>::iterator iter = target->begin();

	for (int i = 0; i < idx; ++i)
	{
		++iter;
	}
	target->insert(iter, value);
}

// �� �����ϱ�
void ListClass::EraseByIndex(list<int>* target, int idx)
{
	list<int>::iterator iter = target->begin();

	for (int i = 0; i < idx; ++i)
	{
		++iter;
	}
	target->erase(iter);
}
#include "MySingleton.h"


MySingleton* MySingleton::instance = nullptr;

MySingleton::MySingleton() {}
MySingleton::~MySingleton() {}

void MySingleton::Init() // �̱����� �ʱ�ȭ
{
	calc = new Calculator(); // ������ �ʱ�ȭ�̸鼭, ������ ù �Է��� �޴� ��

	// ���� �ʱ�ȭ�� �߰ڴ� �ȳ��� �غ��ô� (������� ���⿡�� ���Ե�����)
	cout << "**���Ⱑ �ʱ�ȭ�ǰ� ���� ����Ǿ����ϴ�**" << endl;
}

void MySingleton::RunCalculator() // ����ڴ� �� �Լ��� �����ϴ� �Ű�
{
	calc->Run(); // ��ǻ�ʹ� ����� �޾Ƽ� ���⸦ ���� �������ִ� ��
}
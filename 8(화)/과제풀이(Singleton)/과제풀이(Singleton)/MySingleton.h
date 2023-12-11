#pragma once
#include "Calculator.h"

class MySingleton
{
private:
// ������ �ȿ� ���� �� �� �ǵ� �׳����Ǳ���
	MySingleton();
	~MySingleton();

	static MySingleton* instance;

public:
	static MySingleton* Instance()
	{
		if (Instance == nullptr)
		{
			instance = new MySingleton();
			return instance; // �ν��Ͻ��� ������ ���� ��ȯ
		}

		return instance; // ������ �ִ� �� ��ȯ
	}

	// * �߰� �ڵ� �� : Ŭ�������� ���ٱ� ������ ���� �� ����� �� �� �ֽ��ϴ�
	// private �ؿ� public, �ٽ� �� �ؿ� private�� ������ �� �ֽ��ϴ�
	// ���� private�ε� �ǹ̰� �ణ �ٸ��ų�, �켱 ������ ���̰� �ִٰ� �����Ǹ�
	// �ٸ� ���� ��� �������ϴ�

	// �̷��� ���� �� �ߺ��� ���ٱ� ������ ���� ���,
	// �� �ڵ��� ���� ���ٱ��� �������� ���� ����� ������ �����ϴ�

private:
	// �� ������ �ۼ��Ǵ� �ڵ�� �ٽ� private�� �˴ϴ�
	// �ٽ� �� �ؿ� public�� ����Ǹ�, �� �ؿ� �ۼ��� �ڵ�� �ٽ� public�� �˴ϴ�

	// ���� (private)
	Calculator* calc;

public:
	void Init();          // �ʱ�ȭ
	void RunCalculator(); // ���� ���� ����
};


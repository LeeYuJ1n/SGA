#pragma once
#include <Windows.h>

// ���
#include "TestScene.h" // �׽�Ʈ ���� �ҷ��ͼ� ��� (���߿��� �ڵ� ��ġ�� �޶��� �� ����)
#include "AngleScene.h"
#include "TimeAndCoord.h"

class GameManager
{
	// ���� �Ŵ��� : ���ӿ� ����ϱ� ���� �� ��� �߿���
	//              (�̱��� �̿��̳� ���� ��ġ�� �Ұ����ϰ�) ū Ʋ���� (��������, main��) ��ġ�ؾ� ��
	//              �׷� �߿� ��ɵ��� ��� �� ���� �����ϱ� ���� Ŭ����
	//              (������ ���۰� ��, "���", ����, ĳ���� ���� ���)

	// = main�� ����ϴ� ��ǻ��� ���� �� ��ü��� �����ص� �����ϴ�

	// �׷��� �̱������� ���� �̴ϴ�

private:
	GameManager() {} // ������ (���Ǳ���)
	~GameManager() {} // �Ҹ���

	static GameManager* instance;

public:
	static GameManager* Get()
	{
		if (instance == nullptr)
		{
			instance = new GameManager();
			return instance;
		}
		return instance;
	}

	void Delete()
	{
		delete instance; // �ν��Ͻ� ����
	}

	// ���ӸŴ����� ���� : ��� ������ �ƴ϶�, ����� ������ �� ��
	// �׷��Ƿ� ���⼭ �Լ��� ���� ������ �ƴ϶�
	// ��ϵ� ��鿡 �Լ��� �����ؼ� ���� �����ϴ� ����

	void Init(HWND _hWnd); // �ʱ�ȭ
	
	// "����"�� �߰��� �ʿ��� �� (���α׷��� ���忡�� 3����)
	// �Է�, ���, ����
	void GetInput(WPARAM _wParam);
	void Render();
	void Update();

	// ���ο� �Լ� : "����Ʈ" �ޱ�
	void GetPoint(LPARAM _lParam);

private:
	// ���ӸŴ����� ������

	// � ����� ����?
	TestScene* tsc;
	AngleScene* asc;
	TimeAndCoord* tac;
	
	// �Է��� ��� ����?
	WPARAM wParam;

	// �ʱ�ȭ�� �� ��...ȭ���� ��� ��������? ������� ����?
	HWND hWnd; // � �����쿡 ����ұ�? (�ü�� ���� ����)
	HDC hdc;    // � ȭ��(�ϵ����)���� ����ұ�? (������ ��� ����)
};


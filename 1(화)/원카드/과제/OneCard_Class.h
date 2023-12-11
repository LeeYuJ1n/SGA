#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

class OneCard_Class
{
public:
	OneCard_Class() {}

	// ����
	void OneCardGame();              // ���� �غ�
	void OneCardPlay();              // ���� ����
	void Player_OneCardSystem();     // �÷��̾� ��ī�� ��ġ��
	void Target_OneCardSystem();     // ���� ��ī�� ��ġ��

	// �÷��� �ൿ
	void Player();            // �÷��̾� �ൿ
	void PlayerNoCard();

	void Target();            // ���� �ൿ
	void TargetNoCard();

	// �¸� ����
	void PlayerWin();         // �÷��̾� �¸�
	void PlayerLoser();       // ���� �¸�
};


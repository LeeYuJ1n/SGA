#include "Game_Select_Class.h"

void Game_Select_Class::Game_Select_Print()
{
	int inputSelect = 0;
	bool loop = true;

	while (loop)
	{
		cout << "--------------------------------------------------------" << endl;
		cout << "���ϴ� ������ �������ּ���" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "[ 1�� ] ��ī�� / [ 2�� ] �̱���" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "�Է� : ";
		cin >> inputSelect;

		switch (inputSelect)
		{
		case 1:
			system("cls");
			cout << "��ī�带 �����ϼ̽��ϴ�" << endl;
			Sleep(3000);
			system("cls");
			loop = false;
			break;

		case 2:
			system("cls");
			cout << "���� �̱����� �����Դϴ�" << endl;
			Sleep(3000);
			system("cls");
			break;

		default:
			cout << "�Է��� �߸��Ǿ����ϴ�. �ٽ� �Է����ּ���" << endl;
			break;
		}
	}
}
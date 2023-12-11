#include "Game_Select_Class.h"

void Game_Select_Class::Game_Select_Print()
{
	int inputSelect = 0;
	bool loop = true;

	while (loop)
	{
		cout << "--------------------------------------------------------" << endl;
		cout << "원하는 게임을 선택해주세요" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "[ 1번 ] 원카드 / [ 2번 ] 미구현" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "입력 : ";
		cin >> inputSelect;

		switch (inputSelect)
		{
		case 1:
			system("cls");
			cout << "원카드를 선택하셨습니다" << endl;
			Sleep(3000);
			system("cls");
			loop = false;
			break;

		case 2:
			system("cls");
			cout << "현재 미구현된 상태입니다" << endl;
			Sleep(3000);
			system("cls");
			break;

		default:
			cout << "입력이 잘못되었습니다. 다시 입력해주세요" << endl;
			break;
		}
	}
}
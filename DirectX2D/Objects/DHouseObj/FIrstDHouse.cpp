#include "Framework.h"

FIrstDHouse::FIrstDHouse()
{
	stage1 = new Stage1();
	stage2 = new Stage2();
	hidden1 = new Hidden1();

	background = new Quad(L"Textures/DHouseTexure/FirstBackground.png");
	background->Pos() = { CENTER_X, CENTER_Y };
	background->UpdateWorld();

	start_Btn = new Button(L"Textures/DHouseTexure/start_Btn.png");
	start_Btn->Pos() = { CENTER_X, 100 };

	esterEgg_Btn = new Button(L"Textures/DHouseTexure/Easter_Egg.png");
	esterEgg_Btn->Pos() = { 100, 50 };

	// option_Btn = new Button(L"Textures/DHouseTexure/Option_btn.png");
	// option_Btn->Pos() = { CENTER_X, 100 };
}

FIrstDHouse::~FIrstDHouse()
{
	delete background;
	delete start_Btn;
	delete esterEgg_Btn;
	// delete option_Btn;
}

void FIrstDHouse::Update()
{
	start_Btn->Update();
	esterEgg_Btn->Update();
	// option_Btn->Update();

	if (KEY_DOWN(VK_LBUTTON))
	{
		if (start_Btn->isDownCheck)
		{
			SceneManager::Get()->ChangeScene("Stage1"); // �������� 1 �� ���

			PLAYERDATA->objectA = false;
			PLAYERDATA->objectB = false;
			PLAYERDATA->objectC = false;
			PLAYERDATA->objectD = false;
			PLAYERDATA->objectE = false;
			hidden1->count = 0;

			Audio::Get()->Stop("FirstBGM");
		}
		else if (esterEgg_Btn->isDownCheck)
		{
			Audio::Get()->Stop("FirstBGM");
			Audio::Get()->Add("LostArk", "Sounds/DHouseSound/LOSTARK_Soundtrack.wav", true);
			Audio::Get()->Play("LostArk", 10.0f);

			SceneManager::Get()->ChangeScene("EsterEgg"); // �̽��Ϳ��� �� ���
		}
		// else if (option_Btn->isDownCheck)
		// {
		// 	SceneManager::Get()->ChangeScene(""); // �ɼ� �� �v��
		// }
	}
}

void FIrstDHouse::Render()
{
	background->Render();
	start_Btn->Render();
	esterEgg_Btn->Render();
	// option_Btn->Render();
}


#include "Framework.h"
#include "FirstDHouseScene.h"

FirstDHouseScene::FirstDHouseScene()
{
	// ������� ���
	Audio::Get()->Add("FirstBGM", "Sounds/DHouseSound/First_Menu_BGM.wav", true);
	Audio::Get()->Play("FirstBGM", 10.0f);

	// ������ �ν��Ͻ� ���
	firstdhouse = new FIrstDHouse();
}

FirstDHouseScene::~FirstDHouseScene()
{
	delete firstdhouse;
}

void FirstDHouseScene::Update()
{
	firstdhouse->Update();
}

void FirstDHouseScene::Render()
{
	firstdhouse->Render();
}


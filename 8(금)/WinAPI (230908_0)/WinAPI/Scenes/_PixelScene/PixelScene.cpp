#include "Framework.h"
#include "PixelScene.h"

PixelScene::PixelScene()
{
	BulletManager::Get();

	land = new Landscape(L"Textures/_PixelSample/land.bmp", false);

	player = new PixelCharacter();
	player->pos = { CENTER_X, CENTER_Y };
	player->SetProcessLimit(totalProcess);
	player->SetLand(land);
}

PixelScene::~PixelScene()
{
	delete player;

	BulletManager::Delete();
}

void PixelScene::Update()
{
	land->Update();
	player->Update();

	currentProcess = player->GetProcess();
	if (ProcessChanged())
	{
		land->SetSpeed(player->GetSpeedX() * 100);
	}
	else
	{
		land->SetSpeed(0);
	}
}

void PixelScene::Render(HDC hdc)
{
	land->Render(hdc);
	player->Render(hdc);

	// �α� (���� �Ʒ� : ��� ���� �����ϰ� ��µǵ���)
	wstring progressLog = L"���� ���൵ : " + to_wstring(currentProcess);
	TextOut(hdc, CENTER_X - 100, 0, progressLog.c_str(), progressLog.size());
}
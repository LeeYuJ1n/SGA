#include "Framework.h"
#include "SampleScene.h"

SampleScene::SampleScene()
{
    //��������
    StageManager::Get()->LoadTileData("TextData/_SampleScene/TileTable.csv");
    StageManager::Get()->SetAuto(isLoop); // "�ڵ�" ���θ� ����

    //���� �ε�
    landscape = new Landscape(L"Textures/_SampleScene/sampleBackground.bmp", isLoop);

    //�÷��̾ ����, ��ġ�� ����
    player = new SampleCharacter();
    player->pos = { WIN_WIDTH * 0.1f, CENTER_Y };
}

SampleScene::~SampleScene()
{
    StageManager::Delete();

    delete landscape;
    delete player;
}

void SampleScene::Update()
{
    landscape->SetSpeed(StageManager::Get()->GetSpeed() * 0.5f);

    // �������� ������Ʈ
    StageManager::Get()->Update();
    StageManager::Get()->CollisionPickup(player);

    landscape->Update();
    player->Update();
}

void SampleScene::Render(HDC hdc)
{
    landscape->Render(hdc);

    StageManager::Get()->Render(hdc);

    player->Render(hdc);
}

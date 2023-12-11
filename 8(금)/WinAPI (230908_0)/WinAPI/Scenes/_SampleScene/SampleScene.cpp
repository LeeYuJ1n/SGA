#include "Framework.h"
#include "SampleScene.h"

SampleScene::SampleScene()
{
    //스테이지
    StageManager::Get()->LoadTileData("TextData/_SampleScene/TileTable.csv");
    StageManager::Get()->SetAuto(isLoop); // "자동" 여부를 설정

    //지형 로드
    landscape = new Landscape(L"Textures/_SampleScene/sampleBackground.bmp", isLoop);

    //플레이어를 생성, 위치를 지정
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

    // 스테이지 업데이트
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

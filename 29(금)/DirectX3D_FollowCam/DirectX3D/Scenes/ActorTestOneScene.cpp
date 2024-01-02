#include "Framework.h"
#include "ActorTestOneScene.h"

ActorTestOneScene::ActorTestOneScene()
{
	level = new TerrainEditor();
	player = new TestActor();

	level->GetMaterial()->SetShader(L"Light/Light.hlsl"); // 광원 처리는 계속 기본 빛
	                               // 이유 : 정점 계산 내에서 법선계산을 이미 하고 있어서
	level->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Dirt.png"); //디퓨즈맵 세팅

	player->SetLevel(level);
	
	// 추적 카메라의 표적 설정
	CAM->SetTarget(player);
	CAM->TargetOptionLoad("Follow");
}

ActorTestOneScene::~ActorTestOneScene()
{
	delete player;
	delete level;
}

void ActorTestOneScene::Update()
{
	level->Update();
	player->Update();
}

void ActorTestOneScene::PreRender()
{
	
}

void ActorTestOneScene::Render()
{
	level->Render();
	player->Render();
}

void ActorTestOneScene::PostRender()
{
	player->PostRender();
}

void ActorTestOneScene::GUIRender()
{
	level->RenderUI();
	player->GUIRender();
}
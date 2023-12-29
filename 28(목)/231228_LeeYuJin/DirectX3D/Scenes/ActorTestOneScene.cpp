#include "Framework.h"
#include "ActorTestOneScene.h"

ActorTestOneScene::ActorTestOneScene()
{
	level = new TerrainEditor();
	player = new TestActor();

	level->GetMaterial()->SetShader(L"Light/Light.hlsl"); // ���� ó���� ��� �⺻ ��
	                               // ���� : ���� ��� ������ ��������� �̹� �ϰ� �־
	level->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Dirt.png"); //��ǻ��� ����

	player->SetLevel(level);
	
	// ���� ī�޶��� ǥ�� ����
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

	if (KEY_PRESS('G'))
	{
		CAM->SetTarget(NULL);
	}
	if (KEY_PRESS('F'))
	{
		CAM->SetTarget(player);
	}
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
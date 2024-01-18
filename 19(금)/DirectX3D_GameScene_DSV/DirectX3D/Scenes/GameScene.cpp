#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	naruto = new Naruto();

	CAM->SetTarget(naruto);
	// CAM->TargetOptionLoad("Follow");
	CAM->TargetOptionLoad("Naruto");
	CAM->LookAtTarget(); // ī�޶��� 2�� ������ ǥ������ (���� �ѱ�, * ������ ����� ���ΰ��̸�? ���)

	// ���� �� �̱��� ��� �� ȣ����� Ȥ�� �ʱ�ȭ �Լ� ���
	KunaiManager::Get();
	RobotManager::Get()->SetTarget(naruto);
}

GameScene::~GameScene()
{
	delete naruto;

	// ���� �� �̱����� ���� ��� ����
	KunaiManager::Delete();
	RobotManager::Delete();
}

void GameScene::Update()
{
	naruto->Update();

	KunaiManager::Get()->Update();
	RobotManager::Get()->Update();
}

void GameScene::PreRender()
{
}

void GameScene::Render()
{
	naruto->Render();

	KunaiManager::Get()->Render();
	RobotManager::Get()->Render();
}

void GameScene::PostRender()
{
	// naruto->Render();
	
	RobotManager::Get()->PostRender();
}

void GameScene::GUIRender()
{
	naruto->GUIRender();
}

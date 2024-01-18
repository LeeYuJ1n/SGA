#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	naruto = new Naruto();

	CAM->SetTarget(naruto);
	// CAM->TargetOptionLoad("Follow");
	CAM->TargetOptionLoad("Naruto");
	CAM->LookAtTarget(); // 카메라의 2차 초점을 표적에게 (락온 켜기, * 락온의 대상이 주인공이면? 백뷰)

	// 게임 내 싱글턴 사용 시 호출생성 혹은 초기화 함수 사용
	KunaiManager::Get();
	RobotManager::Get()->SetTarget(naruto);
}

GameScene::~GameScene()
{
	delete naruto;

	// 게임 내 싱글턴이 사용된 경우 삭제
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

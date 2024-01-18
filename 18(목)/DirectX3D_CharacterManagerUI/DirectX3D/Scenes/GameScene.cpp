#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	// ○ Background
	background = new Model("Forest");               // 모델 설정
	background->SetShader(L"Basic/Texture.hlsl");   // 셰이더(텍스처) 설정
	background->Scale() *= 10.0f;                   // 크기 설정
	background->UpdateWorld();                      // 맵에 업데이트

	// ○ Character
	naruto = new Naruto();

	// ○ Color Edit (BlendState)
	FOR(2)
	{
		blendState[i] = new BlendState();
	}

	// 주어진 알파를 다른 이미지와 혼합새서 최종 적용하기 위한(덮어씌우기 위한) 표제 색으로
	blendState[1]->AlphaToCoverage(true);

	// ○ Camera
	CAM->SetTarget(naruto);
	// CAM->TargetOptionLoad("Follow");
	CAM->TargetOptionLoad("Naruto");
	CAM->LookAtTarget(); // 카메라의 2차 초점을 표적에게 (락온 켜기, * 락온의 대상이 주인공이면? 백뷰)

	// ○ SkyBox
	skyBox = new SkyBox(L"Textures/Landscape/BlueSky.dds");

	// ○ Singleton
	// 게임 내 싱글턴 사용 시 호출생성 혹은 초기화 함수 사용
	KunaiManager::Get();
	RobotManager::Get()->SetTarget(naruto);
}

GameScene::~GameScene()
{
	// ○ Background
	delete background;

	// ○ Character
	delete naruto;

	// ○ SkyBox
	delete skyBox;

	// ○ BlendState
	FOR(2)
	{
		delete blendState[i];
	}

	// ○ Singleton
	// 게임 내 싱글턴이 처음 사용된 경우 삭제
	KunaiManager::Delete();
	RobotManager::Delete();
}

void GameScene::Update()
{
	// ○ Character
	naruto->Update();

	// ○ SkyBox
	skyBox->UpdateWorld();

	// ○ Singleton
	KunaiManager::Get()->Update();
	RobotManager::Get()->Update();
}

void GameScene::PreRender()
{
	// TODO : 코드가 필요하면 추가
}

void GameScene::Render()
{
	// ○ SkyBox
	skyBox->Render();

	// ○ Character
	naruto->Render(); // 나루토 모델 출력

	// ○ Background
	blendState[1]->SetState(); // 지금 나올 이미지는 다른 이미지와 통합하면서 + 지정된 배경색이 있으면 지우기
	background->Render();      // 배경(Forest) 출력
	blendState[0]->SetState(); // 다시 이전처럼

	// ○ Singleton
	KunaiManager::Get()->Render();
	RobotManager::Get()->Render();
}

void GameScene::PostRender()
{
	// ○ Character
	// naruto->Render();
	
	// ○ Singleton
	RobotManager::Get()->PostRender();
}

void GameScene::GUIRender()
{
	// ○ Character
	naruto->GUIRender();
}

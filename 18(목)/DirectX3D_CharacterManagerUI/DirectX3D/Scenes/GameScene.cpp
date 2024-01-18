#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	// �� Background
	background = new Model("Forest");               // �� ����
	background->SetShader(L"Basic/Texture.hlsl");   // ���̴�(�ؽ�ó) ����
	background->Scale() *= 10.0f;                   // ũ�� ����
	background->UpdateWorld();                      // �ʿ� ������Ʈ

	// �� Character
	naruto = new Naruto();

	// �� Color Edit (BlendState)
	FOR(2)
	{
		blendState[i] = new BlendState();
	}

	// �־��� ���ĸ� �ٸ� �̹����� ȥ�ջ��� ���� �����ϱ� ����(������ ����) ǥ�� ������
	blendState[1]->AlphaToCoverage(true);

	// �� Camera
	CAM->SetTarget(naruto);
	// CAM->TargetOptionLoad("Follow");
	CAM->TargetOptionLoad("Naruto");
	CAM->LookAtTarget(); // ī�޶��� 2�� ������ ǥ������ (���� �ѱ�, * ������ ����� ���ΰ��̸�? ���)

	// �� SkyBox
	skyBox = new SkyBox(L"Textures/Landscape/BlueSky.dds");

	// �� Singleton
	// ���� �� �̱��� ��� �� ȣ����� Ȥ�� �ʱ�ȭ �Լ� ���
	KunaiManager::Get();
	RobotManager::Get()->SetTarget(naruto);
}

GameScene::~GameScene()
{
	// �� Background
	delete background;

	// �� Character
	delete naruto;

	// �� SkyBox
	delete skyBox;

	// �� BlendState
	FOR(2)
	{
		delete blendState[i];
	}

	// �� Singleton
	// ���� �� �̱����� ó�� ���� ��� ����
	KunaiManager::Delete();
	RobotManager::Delete();
}

void GameScene::Update()
{
	// �� Character
	naruto->Update();

	// �� SkyBox
	skyBox->UpdateWorld();

	// �� Singleton
	KunaiManager::Get()->Update();
	RobotManager::Get()->Update();
}

void GameScene::PreRender()
{
	// TODO : �ڵ尡 �ʿ��ϸ� �߰�
}

void GameScene::Render()
{
	// �� SkyBox
	skyBox->Render();

	// �� Character
	naruto->Render(); // ������ �� ���

	// �� Background
	blendState[1]->SetState(); // ���� ���� �̹����� �ٸ� �̹����� �����ϸ鼭 + ������ ������ ������ �����
	background->Render();      // ���(Forest) ���
	blendState[0]->SetState(); // �ٽ� ����ó��

	// �� Singleton
	KunaiManager::Get()->Render();
	RobotManager::Get()->Render();
}

void GameScene::PostRender()
{
	// �� Character
	// naruto->Render();
	
	// �� Singleton
	RobotManager::Get()->PostRender();
}

void GameScene::GUIRender()
{
	// �� Character
	naruto->GUIRender();
}

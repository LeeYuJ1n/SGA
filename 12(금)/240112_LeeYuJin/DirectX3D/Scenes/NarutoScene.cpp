#include "Framework.h"
#include "NarutoScene.h"

NarutoScene::NarutoScene()
{
	naruto = new Naruto();

	// 추적 카메라의 표적 설정
	CAM->SetTarget(naruto);
	CAM->TargetOptionLoad("Follow");
	CAM->Pos() = { 100, 100, 0 };
}

NarutoScene::~NarutoScene()
{
	delete naruto;
}

void NarutoScene::Update()
{
	naruto->Update();
}

void NarutoScene::PreRender()
{
}

void NarutoScene::Render()
{
	naruto->Render();
}

void NarutoScene::PostRender()
{
}

void NarutoScene::GUIRender()
{
	naruto->GUIRender();
}

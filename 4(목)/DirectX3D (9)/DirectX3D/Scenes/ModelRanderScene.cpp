#include "Framework.h"
#include "ModelRanderScene.h"

ModelRanderScene::ModelRanderScene()
{
	model = new Model("Fox");
}

ModelRanderScene::~ModelRanderScene()
{
	delete model;
}

void ModelRanderScene::Update()
{
	model->UpdateWorld();
}

void ModelRanderScene::PreRender()
{

}

void ModelRanderScene::Render()
{
	model->Render();
}

void ModelRanderScene::PostRender()
{

}

void ModelRanderScene::GUIRender()
{
	model->GUIRender();
}

#include "Framework.h"
#include "PickerScene.h"

PickerScene::PickerScene()
{
    picker = new TerrainPicker();
    picker->GetMaterial()->SetShader(L"Light/Light.hlsl");
    picker->GetMaterial()->SetDiffuseMap(L"Textures/Color/Cyan.png");
}

PickerScene::~PickerScene()
{
    delete picker;
}

void PickerScene::Update()
{
    picker->Update();
}

void PickerScene::PreRender()
{
    
}

void PickerScene::Render()
{
    picker->Render();
}

void PickerScene::PostRender()
{

}

void PickerScene::GUIRender()
{
    picker->RenderUI();
}
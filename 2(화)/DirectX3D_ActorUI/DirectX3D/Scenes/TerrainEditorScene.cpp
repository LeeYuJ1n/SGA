#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
    editor = new TerrainEditor();
    editor->GetMaterial()->SetShader(L"Light/Light.hlsl");
    editor->GetMaterial()->SetDiffuseMap(L"Textures/Color/Yellow.png");
}

TerrainEditorScene::~TerrainEditorScene()
{
    delete editor;
}

void TerrainEditorScene::Update()
{
    editor->Update();
}

void TerrainEditorScene::PreRender()
{

}

void TerrainEditorScene::Render()
{
    editor->Render();
}

void TerrainEditorScene::PostRender()
{

}

void TerrainEditorScene::GUIRender()
{
    editor->RenderUI();
}
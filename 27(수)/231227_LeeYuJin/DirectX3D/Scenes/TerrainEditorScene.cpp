#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
    editor = new TerrainEditor();
    editor->GetMaterial()->SetShader(L"Light/Light.hlsl");
    editor->GetMaterial()->SetDiffuseMap(L"Textures/Color/Yellow.png");

    character = new TestActor();
}

TerrainEditorScene::~TerrainEditorScene()
{
    delete editor;
    delete character;
}

void TerrainEditorScene::Update()
{
    editor->Update();
    character->Update();
}

void TerrainEditorScene::PreRender()
{

}

void TerrainEditorScene::Render()
{
    editor->Render();
    character->Render();
}

void TerrainEditorScene::PostRender()
{

}

void TerrainEditorScene::GUIRender()
{
    editor->RenderUI();
}
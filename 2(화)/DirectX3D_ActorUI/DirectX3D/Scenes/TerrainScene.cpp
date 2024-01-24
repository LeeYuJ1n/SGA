#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
    terrain = new Terrain();
    terrain->Pos() = { -128, 0, -128 };
    terrain->SetPivot({ 128, 0, 128 });
}

TerrainScene::~TerrainScene()
{
    delete terrain;
}

void TerrainScene::Update()
{    
    //terrain->Rot().y += DELTA;
    terrain->UpdateWorld();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
    terrain->Render();
}

void TerrainScene::PostRender()
{
}

void TerrainScene::GUIRender()
{
    terrain->GetMaterial()->RenderUI();
}

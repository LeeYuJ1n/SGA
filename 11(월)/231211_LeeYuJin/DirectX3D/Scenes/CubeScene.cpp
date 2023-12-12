#include "Framework.h"
#include "CubeScene.h"

CubeScene::CubeScene()
{    
    cube = new Cube();
}

CubeScene::~CubeScene()
{
    delete cube;
}

void CubeScene::Update()
{
    //cube->Rot().y += DELTA;
    //cube->Rot().x += DELTA;

    cube->FreeMode();
    cube->UpdateWorld();
}

void CubeScene::PreRender()
{
}

void CubeScene::Render()
{
    cube->Render();
}

void CubeScene::PostRender()
{
}

void CubeScene::GUIRender()
{
    cube->RenderUI();
}

#include "Framework.h"
#include "SphereScene.h"

SphereScene::SphereScene()
{
    sphere = new Sphere();    
    sphere->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    sphere->GetMaterial()->SetDiffuseMap(L"Textures/Etc/Sun.jpg");

    earth = new Sphere();
    earth->GetMaterial()->SetDiffuseMap(L"Textures/Etc/Earth_DM.jpg");

    earth->SetParent(sphere);
    earth->Pos().x = 10.0f;

    testSphere = new Sphere();
    testSphere->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    testSphere->GetMaterial()->SetDiffuseMap(L"Textures/Etc/cat.jpg");
    testSphere->Pos().y = 5.0f;

}

SphereScene::~SphereScene()
{
    delete sphere;
    delete earth;
    delete testSphere;
}

void SphereScene::Update()
{
    sphere->Rot().y += DELTA;
    sphere->UpdateWorld();

    earth->UpdateWorld();

    testSphere->UpdateWorld();
}

void SphereScene::PreRender()
{
}

void SphereScene::Render()
{
    sphere->Render();
    earth->Render();
    testSphere->Render();
}

void SphereScene::PostRender()
{
}

void SphereScene::GUIRender()
{
    sphere->RenderUI();
}

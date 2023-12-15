#include "Framework.h"
#include "SphereScene.h"

SphereScene::SphereScene()
{
    // 태양
    sphere = new Sphere();    
    sphere->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    sphere->GetMaterial()->SetDiffuseMap(L"Textures/Etc/Sun.jpg");

    // 지구
    earth = new Sphere();
    earth->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    earth->GetMaterial()->SetDiffuseMap(L"Textures/Etc/Earth_DM.jpg");

    earth->SetParent(sphere);
    earth->Pos().x = 10.0f;

    // 야구공
    baseball = new Sphere();
    baseball->GetMaterial()->SetDiffuseMap(L"Textures/Etc/baseball.jpg");
    baseball->SetParent(sphere);
    baseball->Pos().y = 5.0f;

    // 화성 중심점
    Pivot = new GameObject();
    Pivot->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    Pivot->GlobalPos() = sphere->Pos();

    // 달 중심점
    Pivot2 = new GameObject();
    Pivot2->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    Pivot2->GlobalPos() = earth->Pos();
    Pivot2->SetParent(earth);

    // 해왕성 중심점
    Pivot3 = new GameObject();
    Pivot3->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    Pivot3->GlobalPos() = sphere->Pos();

    // 목성 중심점
    Pivot4 = new GameObject();
    Pivot4->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    Pivot4->GlobalPos() = sphere->Pos();

    // 화성
    mars = new Sphere();
    mars->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    mars->SetParent(Pivot);
    mars->Pos().x = -5.0f;

    // 달
    mercury = new Sphere();
    mercury->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mercury.jpg");
    mercury->SetParent(Pivot2);
    mercury->Pos().x = 5.0f;

    // 해왕성
    neptune = new Sphere();
    neptune->GetMaterial()->SetDiffuseMap(L"Textures/Etc/neptune.jpg");
    neptune->SetParent(Pivot3);
    neptune->Pos().z = -20.0f;

    // 목성
    jupiter = new Sphere();
    jupiter->GetMaterial()->SetDiffuseMap(L"Textures/Etc/jupiter.jpg");
    jupiter->SetParent(Pivot4);
    jupiter->Pos().z = 15.0f;
}

SphereScene::~SphereScene()
{
    delete sphere;
    delete earth;      // 지구
    delete baseball;   // 야구공
    delete mars;       // 화성
    delete mercury;    // 달
    delete neptune;    // 해왕성
    delete jupiter;    // 목성
}

void SphereScene::Update()
{
    sphere->Rot().y += DELTA;
    sphere->UpdateWorld();

    earth->UpdateWorld();     // 지구
    earth->Rot().y += 1 * DELTA;

    baseball->UpdateWorld();  // 야구공

    Pivot->Rot().y += DELTA * 2;
    Pivot->UpdateWorld();

    Pivot2->Rot().y += DELTA * 0.5;
    Pivot2->UpdateWorld();

    Pivot3->Rot().y += DELTA * 0.2;
    Pivot3->UpdateWorld();

    Pivot4->Rot().y += DELTA * 0.4;
    Pivot4->UpdateWorld();

    mars->UpdateWorld();      // 화성
    mars->Rot().y += 2 * DELTA;

    mercury->UpdateWorld();   // 달
    mercury->Rot().y += 3 * DELTA;

    neptune->UpdateWorld();   // 해왕성
    neptune->Rot().y += 4 * DELTA;

    jupiter->UpdateWorld();   // 목성
    jupiter->Rot().y += 5 * DELTA;
}

void SphereScene::PreRender()
{
}

void SphereScene::Render()
{
    sphere->Render();
    earth->Render();     // 지구
    baseball->Render();  // 야구공
    mars->Render();      // 화성
    mercury->Render();   // 달
    neptune->Render();   // 해왕성
    jupiter->Render();
}

void SphereScene::PostRender()
{
}

void SphereScene::GUIRender()
{
    sphere->RenderUI();
}

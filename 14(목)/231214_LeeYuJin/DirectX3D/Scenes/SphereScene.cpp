#include "Framework.h"
#include "SphereScene.h"

SphereScene::SphereScene()
{
    // �¾�
    sphere = new Sphere();    
    sphere->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    sphere->GetMaterial()->SetDiffuseMap(L"Textures/Etc/Sun.jpg");

    // ����
    earth = new Sphere();
    earth->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    earth->GetMaterial()->SetDiffuseMap(L"Textures/Etc/Earth_DM.jpg");

    earth->SetParent(sphere);
    earth->Pos().x = 10.0f;

    // �߱���
    baseball = new Sphere();
    baseball->GetMaterial()->SetDiffuseMap(L"Textures/Etc/baseball.jpg");
    baseball->SetParent(sphere);
    baseball->Pos().y = 5.0f;

    // ȭ�� �߽���
    Pivot = new GameObject();
    Pivot->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    Pivot->GlobalPos() = sphere->Pos();

    // �� �߽���
    Pivot2 = new GameObject();
    Pivot2->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    Pivot2->GlobalPos() = earth->Pos();
    Pivot2->SetParent(earth);

    // �ؿռ� �߽���
    Pivot3 = new GameObject();
    Pivot3->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    Pivot3->GlobalPos() = sphere->Pos();

    // �� �߽���
    Pivot4 = new GameObject();
    Pivot4->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    Pivot4->GlobalPos() = sphere->Pos();

    // ȭ��
    mars = new Sphere();
    mars->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mars.jpg");
    mars->SetParent(Pivot);
    mars->Pos().x = -5.0f;

    // ��
    mercury = new Sphere();
    mercury->GetMaterial()->SetDiffuseMap(L"Textures/Etc/mercury.jpg");
    mercury->SetParent(Pivot2);
    mercury->Pos().x = 5.0f;

    // �ؿռ�
    neptune = new Sphere();
    neptune->GetMaterial()->SetDiffuseMap(L"Textures/Etc/neptune.jpg");
    neptune->SetParent(Pivot3);
    neptune->Pos().z = -20.0f;

    // ��
    jupiter = new Sphere();
    jupiter->GetMaterial()->SetDiffuseMap(L"Textures/Etc/jupiter.jpg");
    jupiter->SetParent(Pivot4);
    jupiter->Pos().z = 15.0f;
}

SphereScene::~SphereScene()
{
    delete sphere;
    delete earth;      // ����
    delete baseball;   // �߱���
    delete mars;       // ȭ��
    delete mercury;    // ��
    delete neptune;    // �ؿռ�
    delete jupiter;    // ��
}

void SphereScene::Update()
{
    sphere->Rot().y += DELTA;
    sphere->UpdateWorld();

    earth->UpdateWorld();     // ����
    earth->Rot().y += 1 * DELTA;

    baseball->UpdateWorld();  // �߱���

    Pivot->Rot().y += DELTA * 2;
    Pivot->UpdateWorld();

    Pivot2->Rot().y += DELTA * 0.5;
    Pivot2->UpdateWorld();

    Pivot3->Rot().y += DELTA * 0.2;
    Pivot3->UpdateWorld();

    Pivot4->Rot().y += DELTA * 0.4;
    Pivot4->UpdateWorld();

    mars->UpdateWorld();      // ȭ��
    mars->Rot().y += 2 * DELTA;

    mercury->UpdateWorld();   // ��
    mercury->Rot().y += 3 * DELTA;

    neptune->UpdateWorld();   // �ؿռ�
    neptune->Rot().y += 4 * DELTA;

    jupiter->UpdateWorld();   // ��
    jupiter->Rot().y += 5 * DELTA;
}

void SphereScene::PreRender()
{
}

void SphereScene::Render()
{
    sphere->Render();
    earth->Render();     // ����
    baseball->Render();  // �߱���
    mars->Render();      // ȭ��
    mercury->Render();   // ��
    neptune->Render();   // �ؿռ�
    jupiter->Render();
}

void SphereScene::PostRender()
{
}

void SphereScene::GUIRender()
{
    sphere->RenderUI();
}

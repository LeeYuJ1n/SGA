#include "Framework.h"
#include "CubeScene.h"

CubeScene::CubeScene()
{    
    cube = new Cube();
    //cube->GetMaterial()->SetDiffuseMap(L"Textures/Etc/sun.jpg");
    
    //��ǻ��� : ����(ȭ��) ����
    cube->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Fieldstone_DM.tga");
    //����ŧ���� : �ݻ�����(����) ����
    //cube->GetMaterial()->SetSpecularMap(L"Textures/Landscape/Fieldstone_SM.tga");
    //��ָ� : �ݻ����(����) ����
    //cube->GetMaterial()->SetNormalMap(L"Textures/Landscape/Fieldstone_NM.tga");


    // ť�꿡 ��ָ��� �������� �� Ȯ�� ������ Ư�̻���
    // - �鿡 ���� ���� ���� ���� Ȥ�� ������ �ݴ�� ���ư� ���� ����

    // ��ָʿ��� ����(�ݻ����) ���� ���� : ȭ���� r, g, b�� �ؼ��ϸ鼭 ������ �ǵ�
    // �ش� �ؽ�ó�� UV �������� �޶��� ���, �׸��� rgb���� �ؼ��� �ݻ�����
    // �� �ӿ��� ������ ���� ������ ���� Ʋ���� ���� �ִ�
    // -> �׷��� ť�꿡 ��ָ��� ������ ���� �ؽ�ó ���� ��ġ�� �Ű���־�� �ϰų�....
    // -> �ƿ� ó������ �ϳ��� ��ü�� ��Ÿ���� ���� ū 2D �̹��� �ϳ��� �غ����ָ� ����
    //    (��ü�� 2D�� ��ģ ����, ������ ������ ū �̹����� �ִ�)
}

CubeScene::~CubeScene()
{
    delete cube;
}

void CubeScene::Update()
{
    //cube->Rot().y += DELTA;
    cube->Rot().x += DELTA;

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
    cube->GetMaterial()->RenderUI();
}

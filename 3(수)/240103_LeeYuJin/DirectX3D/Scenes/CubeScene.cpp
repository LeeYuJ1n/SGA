#include "Framework.h"
#include "CubeScene.h"

CubeScene::CubeScene()
{    
    cube = new Cube();
    //cube->GetMaterial()->SetDiffuseMap(L"Textures/Etc/sun.jpg");
    
    //디퓨즈맵 : 색조(화소) 적용
    cube->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Fieldstone_DM.tga");
    //스페큘러맵 : 반사정도(질감) 적용
    //cube->GetMaterial()->SetSpecularMap(L"Textures/Landscape/Fieldstone_SM.tga");
    //노멀맵 : 반사방향(굴곡) 적용
    //cube->GetMaterial()->SetNormalMap(L"Textures/Landscape/Fieldstone_NM.tga");


    // 큐브에 노멀맵을 적용했을 때 확인 가능한 특이사항
    // - 면에 따라서 돌의 재질 느낌 혹은 굴곡이 반대로 돌아갈 때가 있음

    // 노멀맵에서 굴곡(반사방향) 결정 기준 : 화소의 r, g, b를 해석하면서 나오는 건데
    // 해당 텍스처의 UV 시작점이 달라질 경우, 그림의 rgb에서 해석된 반사방향과
    // 앱 속에서 지정된 빛의 방향이 서로 틀어질 수도 있다
    // -> 그래서 큐브에 노멀맵을 적용할 경우는 텍스처 적용 위치를 신경써주어야 하거나....
    // -> 아예 처음부터 하나의 입체를 나타내기 위한 큰 2D 이미지 하나를 준비해주면 좋다
    //    (입체를 2D로 펼친 듯한, 전개도 느낌의 큰 이미지가 있다)
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

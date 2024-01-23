#include "Framework.h"

#include "Scenes/TextureScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/ShaderScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/MatchingScene.h"

// 20일의 과제 : 팔로우 캠을 한번 적용해봅시다!
//              닌자 / 비행기 / 총알 중 하나를 선택해서 (총알은 까다로울 겁니다...)
//              해당 트랜스폼을 카메라가 따라가도록 해봅시다.

//              닌자, 비행기 : 움직이면 카메라가 따라가기 (배경이 있으면 카메라의 움직임을 알기 쉬울 겁니다)
//              총알 : 쏘면 첫 번째 총알을 카메라가 따라가다가, 총알이 사라지면(*추가 구현 필요) 총알을 쐈던 닌자나 비행기에게로

GameManager::GameManager()
{
    Create();

    uiViewBuffer = new MatrixBuffer();

    SCENE->Register("Plane", new TextureScene());
    SCENE->Register("Ninja", new AnimationScene());
    SCENE->Register("Shader", new ShaderScene());
    SCENE->Register("RTV", new RenderTargetScene());
    SCENE->Register("Match", new MatchingScene());

    SCENE->ChangeScene("Match");
}

GameManager::~GameManager()
{
    SCENE->Delete();
    delete uiViewBuffer;

    Delete();
}

void GameManager::Update()
{
    CAMERA->Update();

    Keyboard::Get()->Update();
    Timer::Get()->Update();

    SCENE->Update();
}

void GameManager::Render()
{
    SCENE->PreRender();
    
    Device::Get()->Clear();

    Font::Get()->GetDC()->BeginDraw();

    SCENE->Render();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    Font::Get()->RenderText(fps, { 100, WIN_HEIGHT - 10 });

    CAMERA->RenderUI();

    uiViewBuffer->SetVS(1);
    SCENE->PostRender();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    Observer::Get();

    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddStyle("PGothic", L"맑은 고딕");

    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("PGothic");

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    
    Observer::Delete();
    Font::Delete();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();
}

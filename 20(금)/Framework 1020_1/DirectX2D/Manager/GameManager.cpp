#include "Framework.h"

#include "Scenes/TextureScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/ShaderScene.h"
#include "Scenes/RenderTargetScene.h"

GameManager::GameManager()
{
    Create();

    uiViewBuffer = new MatrixBuffer();

    SCENE->Register("Plane", new TextureScene());
    SCENE->Register("Ninja", new AnimationScene());
    SCENE->Register("Shader", new ShaderScene());
    SCENE->Register("RTV", new RenderTargetScene());

    SCENE->ChangeScene("RTV");
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
    Font::Get()->AddStyle("PGothic", L"¸¼Àº °íµñ");

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

#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/CubeScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/TerrainScene.h"
#include "Scenes/SphereScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/PickerScene.h"

// 오늘의 실습 및 과제

// 1. "좌클릭으로 레이가 충돌한 물체를 고른다(픽한다)"는 것이 어떤 것인지
//    체험해봅시다 : 현재 충돌 씬에서 드래그할 때
//    물체가 (충돌체 0번이) 마우스를 따라다닐 수 있도록 합시다
//    (단, 물체가 3차원 내에서 원하지 않는 움직임을 보일 수 있으므로)
//    (물체의 Z축은 움직이지 않도록 합시다)

// 2. 만든 터레인 픽커의 노멀과 탄젠트 채우기에 도전해봅시다 (예습)

// * 복습 위주인 분들은 다시 자기 페이스에 맞춰서 복습해봅시다!

GameManager::GameManager()
{
    Create();

    SceneManager::Get()->Create("Grid", new GridScene());
    //SceneManager::Get()->Create("Start", new CubeScene());
    //SceneManager::Get()->Create("Start", new TerrainScene());
    //SceneManager::Get()->Create("Start", new SphereScene());
    // SceneManager::Get()->Create("Crash", new CollisionScene());
    SceneManager::Get()->Create("Pick", new PickerScene());

    SceneManager::Get()->Add("Grid");
    //SceneManager::Get()->Add("Start");
    // SceneManager::Get()->Add("Crash");
    SceneManager::Get()->Add("Pick");
}

GameManager::~GameManager()
{
    Delete();
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();    

    SceneManager::Get()->Update();

    Environment::Get()->Update();
}

void GameManager::Render()
{
    SceneManager::Get()->PreRender();
    
    Device::Get()->Clear();
    Font::Get()->GetDC()->BeginDraw();
    
    Environment::Get()->Set();    

    SceneManager::Get()->Render();
    
    //uiViewBuffer->SetVS(1);
    SceneManager::Get()->PostRender();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    Font::Get()->RenderText(fps, { 100, WIN_HEIGHT - 10 });
    
    static bool isActive = true;

    if (isActive)
    {
        ImGui::Begin("Inspector", &isActive);
        Environment::Get()->RenderUI();
        SceneManager::Get()->GUIRender();
        ImGui::End();
    }    

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
    Font::Get()->AddStyle("Default", L"배달의민족 주아");
    
    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");

    Texture::Add(L"Textures/Color/White.png");
    
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

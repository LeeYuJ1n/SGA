#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/CubeScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/TerrainScene.h"
#include "Scenes/SphereScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/PickerScene.h"
#include "Scenes/TerrainEditorScene.h"
#include "Scenes/ActorTestOneScene.h"
#include "Scenes/ActorTestTwoScene.h"


// 실습 겸 과제

// 오늘 작성한 추적 카메라에 대해서 복습하면서...

// 1. 추적 카메라와 자유 카메라가 씬에서 토글될 수 있게 해봅시다.
// 
// 2. 자유 카메라 상태에서만 지형 편집을 할 수 있게 해봅시다.
// 
// 3. 추적 카메라 상태에서만 플레이어 조작을 할 수 있게 해봅시다.

// 실습은 아니고 복습/예습

// 오늘 작성된 쿼드가 추적 카메라 상태에서 나오게 할 수 있는지 알아봅시다
// -> 쿼드가 나온다면 해당 상태에서 다른 캐릭터 UI도 띄울 수 있을지 알아봅시다
//    (예 : 미니맵...의 테두리, 체력바, 방향탐지기, 퀵슬롯 등)


GameManager::GameManager()
{
    Create();

    SceneManager::Get()->Create("Grid", new GridScene());
    SceneManager::Get()->Create("Cube", new CubeScene());
    SceneManager::Get()->Create("Terrain", new TerrainScene());
    SceneManager::Get()->Create("Sphere", new SphereScene());
    SceneManager::Get()->Create("Crash", new CollisionScene());
    SceneManager::Get()->Create("Pick", new PickerScene());
    SceneManager::Get()->Create("TerrainEditor", new TerrainEditorScene());
    SceneManager::Get()->Create("TestActor_1", new ActorTestOneScene());
    SceneManager::Get()->Create("TestActor_2", new ActorTestTwoScene());

    SceneManager::Get()->Add("Grid");
    //SceneManager::Get()->Add("Cube");
    //SceneManager::Get()->Add("Terrain");
    //SceneManager::Get()->Add("Sphere");
    //SceneManager::Get()->Add("Crash");
    //SceneManager::Get()->Add("Pick");
    //SceneManager::Get()->Add("TerrainEditor");
    SceneManager::Get()->Add("TestActor_1");
    //SceneManager::Get()->Add("TestActor_2");
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

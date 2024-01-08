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
#include "Scenes/ModelRanderScene.h"

//12.31 변경점 : UI 뷰포트 추가 (렌더타겟 스타일, 오르토그래픽[무원근] 표시)
//              버퍼를 통한 이미지 이동/필터를 쓸까 했습니다만, 그건 다음 기회에 다른 곳에서도 쓸 기회가 있을 것 같네요

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
    SceneManager::Get()->Create("ModelBase", new ModelRanderScene());

    SceneManager::Get()->Add("Grid");
    //SceneManager::Get()->Add("Cube");
    //SceneManager::Get()->Add("Terrain");
    //SceneManager::Get()->Add("Sphere");
    SceneManager::Get()->Add("Crash");
    //SceneManager::Get()->Add("Pick");
    //SceneManager::Get()->Add("TerrainEditor");
    //SceneManager::Get()->Add("TestActor_1");
    //SceneManager::Get()->Add("TestActor_2");
    //SceneManager::Get()->Add("ModelBase");
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

    Environment::Get()->PostSet(); // 12.31 추가
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

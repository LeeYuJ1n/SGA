#include "Framework.h"

#include "Scenes/CubeScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/SphereScene.h"
#include "Scenes/TerrainEditorScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/ModelExportScene.h"
#include "Scenes/ModelRenderScene.h"
#include "Scenes/ModelAnimationScene.h"
#include "Scenes/IntancingScene.h"
#include "Scenes/HumanScene.h"
#include "Scenes/NarutoScene.h"

// 주말의 과제

// 현재 우리는 나루토 클래스를 만들어서 캐릭터를 구현하는 데 성공했습니다!

// -> 이 나루토를 더욱 보강해서 씬에 구현해봅시다

// 1. 나루토를 위한 전용 씬을 만들어서 나루토를 구현해주세요
// 2. 나루토가 추적 카메라를 쓸 수 있도록 해주세요 (추적 카메라 복습)
// 3. cpp 내에서 빠졌던 TODO 영역의 코드를 완성해주세요

// 4. (옵션) 로봇 클래스를 적당히 구현해서 씬에 배치해주세요
//           (현재 로봇은 인스턴싱이어도 되고 아니어도 됩니다)
//           로봇에 있는 충돌체와 쿠나이가 충돌하면 변화가 생기게 해주세요
//           (예 : 충돌체 색이 바뀌거나, 로봇이 쓰러지는 동작을 재생하거나....)

// 123까지 되면 우리는 캐릭터의 조작 구현을 해내게 됩니다.
// +4까지 되면, NPC와의 (약간 폭력이 추가된) 상호작용을 할 수 있게 됩니다.


GameManager::GameManager()
{
    Create();

    SceneManager::Get()->Create("Grid", new GridScene());
    //SceneManager::Get()->Create("ModelExport", new ModelExportScene());

    //SceneManager::Get()->Create("Cube", new CubeScene());
    //SceneManager::Get()->Create("Sphere", new SphereScene());
    //SceneManager::Get()->Create("Terrain", new TerrainEditorScene());
    //SceneManager::Get()->Create("Collision", new CollisionScene());
    //SceneManager::Get()->Create("ModelRender", new ModelRenderScene());
    //SceneManager::Get()->Create("ModelAnimationScene", new ModelAnimationScene());
    //SceneManager::Get()->Create("Instancing", new IntancingScene());
    // SceneManager::Get()->Create("HumanTest", new HumanScene());
    SceneManager::Get()->Create("Naruto", new NarutoScene());

    SceneManager::Get()->Add("Grid");    
    //SceneManager::Get()->Add("ModelExport");
    SceneManager::Get()->Add("Naruto");
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
    
    Environment::Get()->PostSet();
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
        Environment::Get()->GUIRender();
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

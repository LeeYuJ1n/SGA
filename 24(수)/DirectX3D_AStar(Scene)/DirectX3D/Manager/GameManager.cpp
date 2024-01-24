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
#include "Scenes/GameScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/GBufferScene.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/AStarScene.h"

// 오늘의 실습 겸 과제

// 새로운 A*용 씬을 만들어주세요.

// 새로운 씬에는 지형(터레인, 블록, 터레인 에디터, 기타 지형 담당 무엇이든 가능)
// 그리고 캐릭터, 그리고 A* 클래스가 객체로 들어갑니다.

// 캐릭터는 지형 위에서 움직이고, 지형의 한 곳을 좌클릭하면 그곳으로 움직입니다.

// 호출은 A*에서 함수 호출을 통해서 길찾기를 해주세요.

// 캐릭터와 지형 담당 클래스는 필요하면 수정이나 작성을 추가로 하셔도 됩니다.
// A* 또한 필요하면 여러분이 수정을 더 하셔도 됩니다! (지금도 아마 호출이 가능하겠지만...)

// 힌트 : 2D에서 우리가 했던 A*를 활용해봅시다! (대충 비슷합니다. 같은 DX고...) 일자 : 1102
// 힌트 2 : 지형에 대한 정보 호출 함수들은 터레인 에디터, 블록 매니저 등에서 진행한 바 있습니다.

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
    //SceneManager::Get()->Create("HumanTest", new HumanScene());
    //SceneManager::Get()->Create("Game", new GameScene());
    //SceneManager::Get()->Create("RenderTarget", new RenderTargetScene());
    //SceneManager::Get()->Create("GeometryBuffer", new GBufferScene());
    //SceneManager::Get()->Create("ShadowScene", new ShadowScene());
    SceneManager::Get()->Create("AStar", new AStarScene());

    SceneManager::Get()->Add("Grid");
    //SceneManager::Get()->Add("ModelExport");
    //SceneManager::Get()->Add("HumanTest");
    //SceneManager::Get()->Add("Game");
    //SceneManager::Get()->Add("RenderTarget");
    //SceneManager::Get()->Add("GeometryBuffer");
    //SceneManager::Get()->Add("ShadowScene");
    SceneManager::Get()->Add("AStar");
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

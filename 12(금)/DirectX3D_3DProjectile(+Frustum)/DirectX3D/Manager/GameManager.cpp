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

// 오늘의 실습 겸 과제 : 투사체 클래스 적용해보기

// 1. 휴먼 씬에서 휴먼이 쿠나이를 던질 수 있게 해봅시다 (휴먼 동작은 없어도 됩니다)
//    (옵션) 나루토를 혹시 쓰시고 싶은 경우, 클립 목록을 참고해서 (fbx 참조 필요) 적당한 동작을 곁들여봅시다
//    -> 다음 시간에 실제로 해볼 겁니다

// 2. 쿠나이에 모델을 적용해봅시다

// 3. 쿠나이가 던지고 5초 뒤에 정말로 없어지는지 확인해봅시다

// 4. 쿠나이가 프러스텀 컬링이 된다면 어떻게 될까요? (*현실 게임에서는 그러면 안 되지만... 지금은 테스트니까요)

// 5. 휴먼이 (혹은 나루토가) 쿠나이 여러 개를 던질 수도 있을까요? 한번 생각해봅시다!


GameManager::GameManager()
{
    Create();

    SceneManager::Get()->Create("Grid", new GridScene());
    //SceneManager::Get()->Create("ModelExport", new ModelExportScene());

    //SceneManager::Get()->Create("Cube", new CubeScene());
    //SceneManager::Get()->Create("Sphere", new SphereScene());
    //SceneManager::Get()->Create("Terrain", new TerrainEditorScene());
    //SceneManager::Get()->Create("Collision", new CollisionScene());
    SceneManager::Get()->Create("ModelRender", new ModelRenderScene());
    //SceneManager::Get()->Create("ModelAnimationScene", new ModelAnimationScene());
    //SceneManager::Get()->Create("Instancing", new IntancingScene());
    //SceneManager::Get()->Create("HumanTest", new HumanScene());

    SceneManager::Get()->Add("Grid");    
    //SceneManager::Get()->Add("ModelExport");
    SceneManager::Get()->Add("ModelRender");
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

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


// �ǽ� �� ����

// ���� �ۼ��� ���� ī�޶� ���ؼ� �����ϸ鼭...

// 1. ���� ī�޶�� ���� ī�޶� ������ ��۵� �� �ְ� �غ��ô�.
// 
// 2. ���� ī�޶� ���¿����� ���� ������ �� �� �ְ� �غ��ô�.
// 
// 3. ���� ī�޶� ���¿����� �÷��̾� ������ �� �� �ְ� �غ��ô�.

// �ǽ��� �ƴϰ� ����/����

// ���� �ۼ��� ���尡 ���� ī�޶� ���¿��� ������ �� �� �ִ��� �˾ƺ��ô�
// -> ���尡 ���´ٸ� �ش� ���¿��� �ٸ� ĳ���� UI�� ��� �� ������ �˾ƺ��ô�
//    (�� : �̴ϸ�...�� �׵θ�, ü�¹�, ����Ž����, ������ ��)


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
    Font::Get()->AddStyle("Default", L"����ǹ��� �־�");
    
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

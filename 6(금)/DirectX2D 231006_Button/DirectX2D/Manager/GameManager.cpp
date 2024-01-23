#include "Framework.h"

#include "Scenes/TextureScene.h"
#include "Scenes/TempScene.h"
#include "Scenes/LoadingScene.h"

GameManager::GameManager()
{
    Create();

    //scene = new TextureScene();

    sceneData1 = new TextureScene(); // 텍스처 씬 : 진짜
    sceneData2 = new TempScene();    // 임시 씬 : 임시, 장면 변환 연출을 위한 "가짜"

    //로딩 씬 만들어서 scene에 할당
    loadingScene = new LoadingScene();
    scene = loadingScene;

    //scene = sceneData1; // 씬의 위치 = 진짜의 위치
    //scene = sceneData2; // 씬의 위치 = 가짜의 위치


    //씬 매니저로 써보기

    //씬 등록
    SceneManager::Get()->Register("PlaneScene", new TextureScene());
    SceneManager::Get()->Register("TempScene", new TempScene());
    SceneManager::Get()->Register("LoadingScene", new LoadingScene());

    //씬 중 하나로 전환
    SceneManager::Get()->ChangeScene("LoadingScene");
}

GameManager::~GameManager()
{
    delete scene;
    delete sceneData1;
    delete sceneData2;

    Delete();
}

void GameManager::Update()
{
    DebugInput();

    Keyboard::Get()->Update();
    Timer::Get()->Update();

    //scene->Update();
    SceneManager::Get()->Update();
}

void GameManager::Render()
{
    Device::Get()->Clear();

    //scene->Render();
    SceneManager::Get()->Render();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    ImGui::Text(fps.c_str());

    //scene->PostRender();
    //SceneManager::Get()->PostRender();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();

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
    Audio::Delete();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();
}

void GameManager::DebugInput()
{
    if (KEY_PRESS(VK_TAB)) // 탭을 누르고 있는 상태에서
    {
        if (KEY_DOWN('1'))
        {
            //scene = sceneData1; // 진짜를 부르기
            //scene->Init();

            ChangeScene(sceneData1, false);
        }

        if (KEY_DOWN('2'))
        {
            ChangeScene(sceneData2, false);
        }

        if (KEY_DOWN('3'))
        {
            ChangeScene(sceneData2, true);
        }
    }

    //로딩 씬이고, 로딩이 끝났다면, 스페이스바를 눌렀을 때 다음 씬... 씬1이 재생되도록
    if (scene == loadingScene &&
        ((LoadingScene*)scene)->LoadComplete())
    {
        if (KEY_DOWN(VK_SPACE))
        {
            ChangeScene(sceneData1, true);
        }

        // 여기서 "아무 키"나 눌렀을 때 같은 결과가 나오게 하는 방법

        // 1. 키보드 클래스에서 GetKeyboardState 함수의 값이 128인지 확인한다
        // 
        // 2. (사실 "아무 키"는 아닌 꼼수) 일반적으로 게임에서 이런 상황이 되었을 때 사람들이 흔히 누르는 키가 있다
        //    -> 컴퓨터라면 엔터, 스페이스바, 화살표, 탭, asdw 의 범위 중 하나를 누르게 되고,
        //    -> 마우스가 있을 경우 좌클릭, 콘솔이라면 패드의 도형 버튼 (혹은 ABXY) 같은 키를 습관적으로 처음 누른다
        //    -> 그러면 이들 키에 똑같은 조건문을 부여하면 마치 아무키나 눌러도 되는 것처럼 흉내나 구현이 가능

    }
}

void GameManager::ChangeScene(Scene* dest, bool toInit)
{
    scene = dest;
    if (toInit) scene->Init();
}
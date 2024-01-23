#include "Framework.h"

#include "Scenes/TextureScene.h"
#include "Scenes/TempScene.h"
#include "Scenes/LoadingScene.h"

GameManager::GameManager()
{
    Create();

    //scene = new TextureScene();

    sceneData1 = new TextureScene(); // �ؽ�ó �� : ��¥
    sceneData2 = new TempScene();    // �ӽ� �� : �ӽ�, ��� ��ȯ ������ ���� "��¥"

    //�ε� �� ���� scene�� �Ҵ�
    loadingScene = new LoadingScene();
    scene = loadingScene;

    //scene = sceneData1; // ���� ��ġ = ��¥�� ��ġ
    //scene = sceneData2; // ���� ��ġ = ��¥�� ��ġ


    //�� �Ŵ����� �Ẹ��

    //�� ���
    SceneManager::Get()->Register("PlaneScene", new TextureScene());
    SceneManager::Get()->Register("TempScene", new TempScene());
    SceneManager::Get()->Register("LoadingScene", new LoadingScene());

    //�� �� �ϳ��� ��ȯ
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
    if (KEY_PRESS(VK_TAB)) // ���� ������ �ִ� ���¿���
    {
        if (KEY_DOWN('1'))
        {
            //scene = sceneData1; // ��¥�� �θ���
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

    //�ε� ���̰�, �ε��� �����ٸ�, �����̽��ٸ� ������ �� ���� ��... ��1�� ����ǵ���
    if (scene == loadingScene &&
        ((LoadingScene*)scene)->LoadComplete())
    {
        if (KEY_DOWN(VK_SPACE))
        {
            ChangeScene(sceneData1, true);
        }

        // ���⼭ "�ƹ� Ű"�� ������ �� ���� ����� ������ �ϴ� ���

        // 1. Ű���� Ŭ�������� GetKeyboardState �Լ��� ���� 128���� Ȯ���Ѵ�
        // 
        // 2. (��� "�ƹ� Ű"�� �ƴ� �ļ�) �Ϲ������� ���ӿ��� �̷� ��Ȳ�� �Ǿ��� �� ������� ���� ������ Ű�� �ִ�
        //    -> ��ǻ�Ͷ�� ����, �����̽���, ȭ��ǥ, ��, asdw �� ���� �� �ϳ��� ������ �ǰ�,
        //    -> ���콺�� ���� ��� ��Ŭ��, �ܼ��̶�� �е��� ���� ��ư (Ȥ�� ABXY) ���� Ű�� ���������� ó�� ������
        //    -> �׷��� �̵� Ű�� �Ȱ��� ���ǹ��� �ο��ϸ� ��ġ �ƹ�Ű�� ������ �Ǵ� ��ó�� �䳻�� ������ ����

    }
}

void GameManager::ChangeScene(Scene* dest, bool toInit)
{
    scene = dest;
    if (toInit) scene->Init();
}
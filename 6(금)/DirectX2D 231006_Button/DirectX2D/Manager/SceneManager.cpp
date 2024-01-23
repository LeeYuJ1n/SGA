#include "Framework.h"

SceneManager::~SceneManager()
{
    //맵에 있는 모든 씬 지우기
    for (pair<string, Scene*> scene : scenes)
    {
        delete scene.second;
    }
}

void SceneManager::Update()
{
    if (curScene == nullptr) return;

    curScene->Update();
}

void SceneManager::Render()
{
    if (curScene == nullptr) return;

    curScene->Render();
}

void SceneManager::Register(string key, Scene* scene)
{
    //중복등록 방지
    if (scenes.count(key) > 0) return;

    scenes[key] = scene; // 이렇게도 맵이면 추가 가능
}

void SceneManager::ChangeScene(string key, bool init)
{
    if (scenes.count(key) == 0) return; //등록 씬이 없으면 종료
    if (scenes[key] == curScene) return; //지금 장면이 그 장면이어도 종료
    if (curScene != nullptr && init) {} //초기화 명령을 받았을 경우, 여기에 추가 코드

    curScene = scenes[key]; // 매개변수로 받은 장면으로 바꾸기 (다음 업데이트에서 장면 교체)

    if (init) curScene->Init(); //초기화 여부가 true일 경우 초기화까지 진행
}
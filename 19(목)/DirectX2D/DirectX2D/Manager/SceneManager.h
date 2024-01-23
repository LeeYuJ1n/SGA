#pragma once

class SceneManager : public Singleton<SceneManager>
{
private:
    friend class Singleton;

    SceneManager() = default;
    ~SceneManager();

public:

    void Update();
    void Render();
    void PostRender();

    // Register : 등록
    void Register(string key, Scene* scene); //매개변수 : 페어의 구성 (키와 값)

    void ChangeScene(string key, bool init = true);
    //씬 바꾸기, 매개변수는 씬의 이름(키) 그리고 초기화 여부(입력이 없으면 초기화 함)

private:

    //페어를 이용한 자료구조 = 맵
    map<string, Scene*> scenes;

    Scene* curScene = nullptr;
};


#pragma once

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Update();
    void Render();

private:
    void Create();
    void Delete();

    // 임시 씬 통제용 입력
    void DebugInput();

    void ChangeScene(Scene* dest, bool toInit);

private:
    Scene* scene;

    // 씬이 하나가 아닌 경우:

    // 필요한 씬을 로드해둔 뒤
    // -> 매니저에서 돌리는 위의 scene 변수에 주소를 맞춰주면 된다

    Scene* sceneData1;
    Scene* sceneData2;

    // 로딩 씬 등록

    Scene* loadingScene;
};
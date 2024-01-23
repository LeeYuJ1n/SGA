#include "Framework.h"

void GlobalEvent::operator()(string keyword)
{
    // 비행기 씬 확정 로딩

    if (keyword == "Start")
    {
        //씬 매니저 싱글턴을 통해 비행기 씬 호출
        SceneManager::Get()->ChangeScene("PlaneScene");
    }
}

void GlobalEvent::operator()(string keyword, string args)
{
    // 씬 로딩은 하는데 내용은 변수로 받기

    if (keyword == "LoadScene")
    {
        SceneManager::Get()->ChangeScene(args);
    }
}

#pragma once

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void Update() = 0;    

    virtual void Render() = 0;
    virtual void PostRender() = 0;

    //아래는 씬이 씬끼리 진행 여부를 주고받을 때 필요한 함수 2종
    virtual void Init() = 0; // Initiate : 초기화, 혹은 시작(Start)
    virtual void Quit() = 0; // Quit : 종료 (End)
};
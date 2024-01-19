#pragma once

class GameScene : public Scene
{
public:
    // ○ 생성자
    GameScene();

    // ○ 소멸자
    ~GameScene();

    // ○ Scene 클래스 기본 옵션 5가지
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render()  override;
    virtual void PostRender()  override;
    virtual void GUIRender()  override;

private:
    

private:
    // ○ Background
    Model* background;

    // ○ Character
    Naruto* naruto;
    // + 로봇 매니저, + 쿠나이 매니저

    // ○ BlendState
    // 블랜드 상태 설정 : WinAPI의 투명-알파-혼합 blt와 유사한 역할
    //                   지정된 색을 지워주고, 알파값을 적용하고, 주변 이미지와 혼합해준다
    BlendState* blendState[2];
    // BlendState : 이미지 위에 이미지를 덧그릴 때 결과가 어떻게 나올지를 결정하는 값

    // ○ SkyBox
    SkyBox* skyBox;
};


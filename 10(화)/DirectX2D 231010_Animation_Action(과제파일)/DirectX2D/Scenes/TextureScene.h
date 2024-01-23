#pragma once

// 오늘 할 것 : 어제 만든 콜라이더를 이용해서 충돌 상호작용 만들어보기

// -> 충돌을 일으키기 위해서는 콜라이더, 총알, 그리고... 맞아주는 쪽도 필요하다!

class TextureScene : public Scene
{
public:
    TextureScene();
    ~TextureScene();
        
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void Init() override;
    virtual void Quit() override;

private:

    Plane* plane;

    //맞아줄 쪽을 만들어보자
    //Enemy* enemy; //단일 적은 필요가 없다 (매니저 사용)

    vector<Bullet*> sceneBullets;

    Button* tmpButton;
};
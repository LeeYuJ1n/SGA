#pragma once

class AnimationScene : public Scene
{
public:
    AnimationScene();
    ~AnimationScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    virtual void Init() override;
    virtual void Quit() override;
private:
    Ninja* ninja;
    // Effect* testEff;
};
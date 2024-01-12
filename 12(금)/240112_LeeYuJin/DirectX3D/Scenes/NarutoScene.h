#pragma once

class NarutoScene : public Scene
{
public:
    NarutoScene();
    ~NarutoScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Naruto* naruto;
};


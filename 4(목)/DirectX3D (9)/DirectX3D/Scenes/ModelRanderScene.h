#pragma once

class ModelRanderScene : public Scene
{
public:
    ModelRanderScene();
    ~ModelRanderScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render()  override;
    virtual void PostRender()  override;
    virtual void GUIRender()  override;

private:
    Model* model;
};


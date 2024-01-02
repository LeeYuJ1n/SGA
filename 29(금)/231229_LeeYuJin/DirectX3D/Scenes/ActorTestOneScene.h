#pragma once
class ActorTestOneScene : public Scene
{
public:
    ActorTestOneScene();
    ~ActorTestOneScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    TerrainEditor* level;
    TestActor* player;
};


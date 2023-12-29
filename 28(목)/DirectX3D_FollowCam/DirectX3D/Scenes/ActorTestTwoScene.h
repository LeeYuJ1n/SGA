#pragma once
class ActorTestTwoScene : public Scene
{
public:
    ActorTestTwoScene();
    ~ActorTestTwoScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

    // (TRY or TODO) 다른 레벨(지형)이 있을 수도 있을까요??

    TestActor* player;
};
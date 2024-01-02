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
    // * 블록 매니저(싱글턴)가 이 씬에 쓰인다고 생각하고 불러와보겠습니다.
    TestActor* player;
};
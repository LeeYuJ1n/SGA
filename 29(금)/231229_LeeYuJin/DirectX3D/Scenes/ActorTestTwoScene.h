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

    // (TRY or TODO) �ٸ� ����(����)�� ���� ���� �������??
    // * ��� �Ŵ���(�̱���)�� �� ���� ���δٰ� �����ϰ� �ҷ��ͺ��ڽ��ϴ�.
    TestActor* player;
};
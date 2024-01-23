#pragma once

// ���� ������ �ʴ�, ����⸸ �ִ� "�ӽ� ���"�� ����

class TempScene : public Scene
{
public:
    TempScene();
    ~TempScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void Init() override;
    virtual void Quit() override;

private:

    Plane* plane;

};


#pragma once

class BillboardScene : public Scene
{
private:
    UINT COUNT = 100;

public:
    BillboardScene();
    ~BillboardScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    // 빌보드 : 원문은 "간판"
    //          프로그래밍에서는 언제나 카메라를 향하는 2D 텍스처를 지칭
    vector<Quad*> trees; // 나무 (그림 텍스처)
};


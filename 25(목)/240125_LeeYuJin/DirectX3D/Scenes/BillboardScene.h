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
    // ������ : ������ "����"
    //          ���α׷��ֿ����� ������ ī�޶� ���ϴ� 2D �ؽ�ó�� ��Ī
    vector<Quad*> trees; // ���� (�׸� �ؽ�ó)
};


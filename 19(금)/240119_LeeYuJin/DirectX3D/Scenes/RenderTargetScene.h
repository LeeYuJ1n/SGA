#pragma once

class RenderTargetScene : public Scene
{
public:
    // �� ������
    RenderTargetScene();

    // �� �Ҹ���
    ~RenderTargetScene();

    // �� Scene�� �⺻ 5�� �޴�
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;
        
private:
    // �� ���� ����
    bool isRenderTarget;

private:
    Model* forest;
    Human* human;          // ���� ��
    Human* imitationHuman; // ����â ���� ��

    // �׽�Ʈ�� ���� Ÿ�� �ν��Ͻ�
    RenderTarget* renderTarget;
    DepthStencil* depthstencil;

    // ��¿�
    Quad* quad;                    // 2D �ؽ�ó
    FloatValueBuffer* valueBuffer; // �Ҽ� �����
};


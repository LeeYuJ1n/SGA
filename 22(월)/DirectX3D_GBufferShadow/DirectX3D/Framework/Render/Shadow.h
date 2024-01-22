#pragma once
class Shadow
{
public:
    // �׸����� ������ �׷��� �ᱹ ����?
    // ->�׸����� ���� ����� ���� ���� ������ ������...
    //   (�׸��� ���� �� �κ��� ��� ���� ���� �� ������)

    // -> ���� ���⼭ ������ ����� ���� Ÿ���� ����, ���� ���ٽ� Ŭ������ ����
    //    �𵨰� �Ȱ��� ���¸�(=�Ȱ��� ����, �� �ٸ� ����) �� �� �� �׸��� (�� �������)
    //    �׸��� �׷��� ����� �Ƿ翧�� ���忡 �� �����ؼ� "��ġ��" �����

    Shadow(UINT width = 2000, UINT height = 2000);
    ~Shadow();

    void SetRenderTarget();
    void SetRender();
    void PostRender();
    void GUIRender();

private:
    void SetViewProjection();

private:
    // �׸����� ũ��(����, ����, ũ�����)
    UINT width;
    UINT height;
    float scale = 100;

    // ���� Ÿ�� ����
    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    // �� ��Ʈ�� ���� ��İ���(�������� ���) ����
    ViewBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;

    class Quad* quad;

};


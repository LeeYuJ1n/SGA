#pragma once

class GridScene : public Scene
{
private:
    const int MAX_VALUE = 100;

public:
    GridScene();
    ~GridScene();
        
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    void CreateMesh();

private:
    Material* material; 
    // ��Ƽ����, ��Ƽ����, ��Ʈ����
    // : �׸���, �׸��� ǥ���� �� ������(��� ����)�� ����� �� ��Ģ���� �����ϴ� ����
    //   �ٸ� ���δ� "� �׸��� ��� ǥ������ ���� Ŭ����(�ڵ�) / ������Ʈ(����)"

    Mesh<VertexColor>* mesh;

    UINT width, height;

    MatrixBuffer* worldBuffer;
};
#pragma once

class GameObject : public Transform
{
public:
    GameObject(wstring shaderFile = L"UV.hlsl"); // <-�ؽ�ó�� ���� ���� �̸� �غ��ϱ� ���� ���� ����
    ~GameObject();

    virtual void Update();
    virtual void Render();

    void SetRender();

protected:
    VertexShader* vertexShader;
    PixelShader* pixelShader;
    VertexBuffer* vertexBuffer = nullptr;
    IndexBuffer* indexBuffer = nullptr;
    MatrixBuffer* worldBuffer;
        
    vector<Vertex> vertices;
    vector<UINT> indices;
};
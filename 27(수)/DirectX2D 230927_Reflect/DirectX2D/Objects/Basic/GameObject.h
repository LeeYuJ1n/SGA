#pragma once

class GameObject : public Transform
{
public:
    GameObject(wstring shaderFile = L"UV.hlsl"); // <-텍스처가 사용될 것을 미리 준비하기 위한 파일 지정
    ~GameObject();

    virtual void Update();
    virtual void Render();

protected:
    VertexShader* vertexShader;
    PixelShader* pixelShader;
    VertexBuffer* vertexBuffer = nullptr;
    IndexBuffer* indexBuffer = nullptr;
    MatrixBuffer* worldBuffer;
        
    vector<Vertex> vertices;
    vector<UINT> indices;
};
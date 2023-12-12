#pragma once

class GameObject : public Transform
{
public:
    GameObject(wstring shaderFile = L"Tutorial.hlsl");
    ~GameObject();

    virtual void Render() {};
    virtual void SetRender();

    void SetShader(wstring shaderFile);

protected:
    VertexShader* vertexShader;
    PixelShader* pixelShader;    
    MatrixBuffer* worldBuffer;
};
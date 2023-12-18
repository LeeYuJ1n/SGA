#pragma once

class Material
{
public:
    Material();
    Material(wstring shaderFile);
    ~Material();

    void Set();
    
    void RenderUI();

    void SetShader(wstring shaderFile);
    void SetDiffuseMap(wstring textureFile);
    void SetSpecularMap(wstring textureFile);

private:
    string name;

    VertexShader* vertexShader;
    PixelShader* pixelShader;

    Texture* diffuseMap = nullptr;
    Texture* specularMap = nullptr;
};
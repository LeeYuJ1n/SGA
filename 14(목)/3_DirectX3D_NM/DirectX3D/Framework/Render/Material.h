#pragma once

class Material
{
private:
    enum MapType
    {
        DIFFUSE, SPECULAR, NORMAL
    };
    
public:
    class MaterialBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Float4 diffuse = { 1, 1, 1, 1 };            
            Float4 specular = { 1, 1, 1, 1 };
            Float4 ambient = { 1, 1, 1, 1 };

            float shininess = 24.0f;
            int hasNormalMap = 0;
            float padding[2];
        };

    public:
        MaterialBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        }

        Data& Get() { return data; }

    private:
        Data data;
    };

public:
    Material();
    Material(wstring shaderFile);
    ~Material();

    void Set();

    void RenderUI();

    void SetShader(wstring shaderFile);
    void SetDiffuseMap(wstring textureFile);
    void SetSpecularMap(wstring textureFile);
    void SetNormalMap(wstring textureFile);

private:
    void SelectMap(string name, MapType type);
    void UnselectMap(MapType type);

private:
    string name;

    VertexShader* vertexShader;
    PixelShader* pixelShader;

    Texture* diffuseMap = nullptr;
    Texture* specularMap = nullptr;
    Texture* normalMap = nullptr;

    MaterialBuffer* buffer;
};
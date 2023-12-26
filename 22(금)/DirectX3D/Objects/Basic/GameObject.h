#pragma once

class GameObject : public Transform
{
public:
    GameObject(wstring shaderFile = L"Light/NormalMapping.hlsl"); //노멀맵 (레거시 코드) 사용
    //GameObject(wstring shaderFile = L"Light/Light.hlsl"); //단순화된 셰이더 사용
    ~GameObject();

    virtual void Render() {};
    virtual void SetRender();
    virtual void RenderUI() override;
    
    Material* GetMaterial() { return material; }

protected:
    Material* material;    

    MatrixBuffer* worldBuffer;
};
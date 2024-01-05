#include "Framework.h"

GameObject::GameObject(wstring shaderFile)
{
    vertexShader = Shader::AddVS(L"Vertex" + shaderFile);
    pixelShader = Shader::AddPS(L"Pixel" + shaderFile);

    worldBuffer = new MatrixBuffer();
}

GameObject::~GameObject()
{
    if (vertexBuffer)
        delete vertexBuffer;

    if (indexBuffer)
        delete indexBuffer;

    delete worldBuffer;
}

void GameObject::Update()
{
    UpdateWorld();    
}

void GameObject::Render()
{    
    if (!isActive) return;

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    if(vertexBuffer)
        vertexBuffer->Set();
    if(indexBuffer)
        indexBuffer->Set();

    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}

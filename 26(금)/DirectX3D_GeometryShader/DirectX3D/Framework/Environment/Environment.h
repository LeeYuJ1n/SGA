#pragma once

class Environment : public Singleton<Environment>
{
private:
    friend class Singleton;

    Environment();
    ~Environment();

public:

    void Update();
    void GUIRender();

    void Set();
    void PostSet();

    void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
    void SetPerspective();
    void SetOrthographic();

    LightBuffer::Light* AddLight(); // 제2, 제3의 광원 추가

    Camera* GetMainCamera() { return mainCamera; }
    Matrix GetProjection() { return perspective; }

    // 만들어진 광원 호출 (기본적으로 0번 호출 가능)
    LightBuffer::Light* GetLight(UINT index) { return &lightBuffer->Get().lights[index]; }

private:
    void CreateProjection();
    void CreateState();

private:
    MatrixBuffer* projectionBuffer;       
    LightBuffer* lightBuffer;
    ViewBuffer* uiViewBuffer;
    
    SamplerState* samplerState;
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];
    DepthStencilState* depthStencilState[2];

    Camera* mainCamera;

    D3D11_VIEWPORT viewport;

    bool isWireMode = false;

    Matrix perspective;
    Matrix orthographic;
};
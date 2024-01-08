#pragma once

class Environment : public Singleton<Environment>
{
private:
    friend class Singleton;

    Environment();
    ~Environment();

public:

    void Update();
    void RenderUI();

    void Set();
    void PostSet();

    void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
    void SetPerspective();
    void SetOrthographic();

    Camera* GetMainCamera() { return mainCamera; }

    Matrix GetProjection() { return perspective; }

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
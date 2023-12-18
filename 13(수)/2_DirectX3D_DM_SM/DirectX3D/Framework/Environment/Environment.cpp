#include "Framework.h"

Environment::Environment()
{
    CreateProjection();
    CreateState();

    mainCamera = new Camera();
    lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
    delete projectionBuffer;  
    delete lightBuffer;

    delete mainCamera;

    delete samplerState;
    delete rasterizerState[0];
    delete rasterizerState[1];    
}

void Environment::Update()
{
    if (KEY_DOWN(VK_F1))
        isWireMode = !isWireMode;

    mainCamera->Update();
}

void Environment::RenderUI()
{
    if (ImGui::TreeNode("Environment"))
    {
        mainCamera->RenderUI();
        ImGui::Text("LightOption");
        ImGui::SliderFloat3("LightDir", (float*)&lightBuffer->Get(), -1, 1);
        ImGui::SliderFloat("Shininess", &lightBuffer->Get().shininess, 1, 50);
        ImGui::TreePop();
    }
    
}

void Environment::Set()
{
    SetViewport();
    SetProjection();

    if (isWireMode)
        rasterizerState[1]->SetState();
    else
        rasterizerState[0]->SetState();

    lightBuffer->SetPS(0);
}

void Environment::SetViewport(UINT width, UINT height)
{
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    DC->RSSetViewports(1, &viewport);
}

void Environment::SetProjection()
{
    projectionBuffer->SetVS(2);
}

void Environment::CreateProjection()
{
    //Matrix orthographic = XMMatrixOrthographicOffCenterLH(
    //    0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);
    
    Matrix perspective = XMMatrixPerspectiveFovLH(XM_PIDIV4,
        (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

    projectionBuffer = new MatrixBuffer();
    projectionBuffer->Set(perspective);  
}

void Environment::CreateState()
{
    samplerState = new SamplerState();
    samplerState->SetState();

    rasterizerState[0] = new RasterizerState();
    rasterizerState[1] = new RasterizerState();
    rasterizerState[1]->FillMode(D3D11_FILL_WIREFRAME);
}

//void Environment::CreateBlendState()
//{
//    D3D11_BLEND_DESC blendDesc = {};    
//    blendDesc.RenderTarget[0].BlendEnable = true;
//    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
//    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
//    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
//
//    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
//    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
//    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
//
//    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//    DEVICE->CreateBlendState(&blendDesc, &alphaBlendState);
//
//    float blendFactor[4] = {};
//    DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
//
//    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
//
//    DEVICE->CreateBlendState(&blendDesc, &additiveBlendState);
//}


#include "Framework.h"

Environment::Environment()
{
    CreateProjection();
    CreateSamplerState();
    CreateBlendState();
}

Environment::~Environment()
{
    delete projectionBuffer;
}

void Environment::CreateProjection()
{
    Matrix orthographic = XMMatrixOrthographicOffCenterLH(
        0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

    projectionBuffer = new MatrixBuffer();
    projectionBuffer->Set(orthographic);
    projectionBuffer->SetVS(2);
}

void Environment::CreateSamplerState()
{
    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;;        
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;      
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    //LOD(Level Of Detail) : 카메라의 거리에 따라서 퀄리티를 다르게 하는 것

    DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

    DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
    D3D11_BLEND_DESC blendDesc = {};    
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    DEVICE->CreateBlendState(&blendDesc, &blendState);

    float blendFactor[4] = {};
    DC->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

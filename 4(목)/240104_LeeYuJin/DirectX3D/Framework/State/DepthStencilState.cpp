#include "Framework.h"

DepthStencilState::DepthStencilState()
{
    // 뎁스와 스텐실 스테이트

    // 뎁스 : 이미지의 깊이. 화소의 경우 출력 우선순위, 정점의 경우네는 거리에 따른 컬링 등에 관여
    // 스텐실 : 이미지의 임의 절단과 투영 들에 사용되는 추가 버퍼

    desc.DepthEnable = true;
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    desc.DepthFunc = D3D11_COMPARISON_LESS;

    desc.StencilEnable = true;
    desc.StencilReadMask = 0xff;
    desc.StencilWriteMask = 0xff;

    desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    Changed();
}

DepthStencilState::~DepthStencilState()
{
    state->Release();
}

void DepthStencilState::SetState()
{
    DC->OMSetDepthStencilState(state, 1);
}

void DepthStencilState::DepthEnable(bool value)
{
    desc.DepthEnable = value;

    Changed();
}

void DepthStencilState::Changed()
{
    if (state != nullptr)
        state->Release();

    DEVICE->CreateDepthStencilState(&desc, &state);
}

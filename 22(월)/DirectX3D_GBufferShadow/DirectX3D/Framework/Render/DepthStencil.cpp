#include "Framework.h"

DepthStencil::DepthStencil(UINT width, UINT height, bool isStencil)
    : width(width), height(height), isStencil(isStencil)
{
    CreateDSVTexture(); // DSV를 거친/거칠 텍스처 만들기
    CreateDSV(); //DSV 만들기
    CreateSRV(); //SRV 만들기
}

DepthStencil::~DepthStencil()
{
    dsvTexture->Release();
    dsv->Release();
    srv->Release();
}

void DepthStencil::Clear()
{
    DC->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1, 0);
    // DX 제공 함수로 뷰 클리어, 우선순위 1.0까지 모두 지우고(1) 스텐실 적용 해제(0)
}

void DepthStencil::CreateDSVTexture()
{
    D3D11_TEXTURE2D_DESC depthDesc = {}; // 기본값대로 생성만 함
    //거기에 정보를 하나씩 구체적으로 채움
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = isStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
            //스텐실이면 데이터를 구분해서 뎁스-스텐실 데이터로, 아니면 모든 데이터가 하나의 유형이 되도록
    depthDesc.SampleDesc.Count = 1;
    depthDesc.Usage = D3D11_USAGE_DEFAULT; // 기본 유형으로 사용
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
            //DX용 부가옵션 : "이 설명 구조체는 뎁스 스텐실이고, 셰이더 리소스이기도 합니다."

    //다 적힌 정보에 따라 DC에서 텍스처 정보 생성
    DEVICE->CreateTexture2D(&depthDesc, nullptr, &dsvTexture);
    //DEVICE : 출력 연산으로서의(과정으로서의) DC. 말하자면 하드웨어의 추상적 표현
    //함수 : DX 제공
    // 매개변수 : 원본 정보, 추가정보(있다면), 결과가 보존될 변수

}

void DepthStencil::CreateDSV()
{
    D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc = {};
    depthViewDesc.Format = isStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
    depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // 데이터 규모 : 텍스처에서 요구하는 만큼

    DEVICE->CreateDepthStencilView(dsvTexture, &depthViewDesc, &dsv);
    // 위 함수에서 만든 텍스처와 + 이 함수에서 만든 부가 정보 구조체를 합쳐서 DSV 만들기
}

void DepthStencil::CreateSRV()
{
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderDesc = {};
    shaderDesc.Format = isStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_FLOAT;
    shaderDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

    DEVICE->CreateShaderResourceView(dsvTexture, &shaderDesc, &srv);
}

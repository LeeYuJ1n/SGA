#include "Framework.h"

DepthStencil::DepthStencil(UINT width, UINT height, bool isStencil)
    : width(width), height(height), isStencil(isStencil)
{
    CreateDSVTexture(); // DSV�� ��ģ/��ĥ �ؽ�ó �����
    CreateDSV(); //DSV �����
    CreateSRV(); //SRV �����
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
    // DX ���� �Լ��� �� Ŭ����, �켱���� 1.0���� ��� �����(1) ���ٽ� ���� ����(0)
}

void DepthStencil::CreateDSVTexture()
{
    D3D11_TEXTURE2D_DESC depthDesc = {}; // �⺻����� ������ ��
    //�ű⿡ ������ �ϳ��� ��ü������ ä��
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = isStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
            //���ٽ��̸� �����͸� �����ؼ� ����-���ٽ� �����ͷ�, �ƴϸ� ��� �����Ͱ� �ϳ��� ������ �ǵ���
    depthDesc.SampleDesc.Count = 1;
    depthDesc.Usage = D3D11_USAGE_DEFAULT; // �⺻ �������� ���
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
            //DX�� �ΰ��ɼ� : "�� ���� ����ü�� ���� ���ٽ��̰�, ���̴� ���ҽ��̱⵵ �մϴ�."

    //�� ���� ������ ���� DC���� �ؽ�ó ���� ����
    DEVICE->CreateTexture2D(&depthDesc, nullptr, &dsvTexture);
    //DEVICE : ��� �������μ���(�������μ���) DC. �����ڸ� �ϵ������ �߻��� ǥ��
    //�Լ� : DX ����
    // �Ű����� : ���� ����, �߰�����(�ִٸ�), ����� ������ ����

}

void DepthStencil::CreateDSV()
{
    D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc = {};
    depthViewDesc.Format = isStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
    depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // ������ �Ը� : �ؽ�ó���� �䱸�ϴ� ��ŭ

    DEVICE->CreateDepthStencilView(dsvTexture, &depthViewDesc, &dsv);
    // �� �Լ����� ���� �ؽ�ó�� + �� �Լ����� ���� �ΰ� ���� ����ü�� ���ļ� DSV �����
}

void DepthStencil::CreateSRV()
{
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderDesc = {};
    shaderDesc.Format = isStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_FLOAT;
    shaderDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

    DEVICE->CreateShaderResourceView(dsvTexture, &shaderDesc, &srv);
}

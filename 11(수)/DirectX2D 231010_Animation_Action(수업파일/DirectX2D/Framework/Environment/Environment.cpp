#include "Framework.h"

Environment::Environment()
{
    CreateProjection();
    CreateSamplerState();
    CreateBlendState();
    CreateRasterizerState();
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
    //LOD(Level Of Detail) : ī�޶��� �Ÿ��� ���� ����Ƽ�� �ٸ��� �ϴ� ��

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

void Environment::CreateRasterizerState() // ������ȭ ����
{
    // ���߿� �ٸ� �κ��� �߰��� ���� ������, ������ �ϴ� �����̽� �ø� ��������

    // ������ �ޱ����
    D3D11_RASTERIZER_DESC rasterizerDesc = {};

    // ���� �����Ϳ��� ���ϴ� ������ ���� ��...
    rasterizerDesc.CullMode = D3D11_CULL_NONE;  // �ø��� ���� �ʰڴ� : ��� �ؽ�ó�� ���̰ڴ�
    // D3D11_CULL_FRONT : ����Ʈ ���̽� �ø�, ���� ���� �ؽ�ó�� ������� ����
    // D3D11_CULL_BACK : �����̽� �ø�, �ڸ� ���� �ؽ�ó�� ������� ���� (���̷�ƮX 11�� �⺻ ����)
    // D3D11_CULL_NONE : ���̽� �ø� ���� (���̾ ���, �ھ ���)

    // *3Dȯ���� ���� �� ����Ʈ ���̽� �ø��̳� ���̽� �ø��� ���� �� �ʿ��� ���� �ִ� ���ΰ�? �׷����ϴ�
    // ����Ʈ ���̽� �ø��� ���� ? : ����, Ȥ�� �÷��̾� ĳ���Ͱ� ����� �Ѿ �� ���� ����� ǥ���� �� �����ϴ�
    // ���̽� �ø� ������ ���� ? : � �����ε� ���� �ӿ� ���� ��Ī�� �Ǵ� "�ݻ� ��"�� ������ ��

    rasterizerDesc.FillMode = D3D11_FILL_SOLID; // �߰� ��ó���� ����ó�� ����, �׸��� ��� ȭ�Ҹ� ���̰ڴ�
    // rasterizerDesc.DepthBias = // <- ���߿� �׸��̳� �ؽ�ó�� ���� �׸��� ���� �߻��ؾ� �� ��� Ȥ�� �׸��ڰ� ���� �� ���, �� ȭ�Ұ� ���� "����"�� ������ �� �ִ�

    // ������ �ݿ��ؼ� ���� ���������� ����� DC�� �ݿ�
    DEVICE->CreateRasterizerState(&rasterizerDesc, &rasterizerState); // (�Է� �޾ƾ� �� ��, ���;� �� ��)

    DC->RSSetState(rasterizerState);
}
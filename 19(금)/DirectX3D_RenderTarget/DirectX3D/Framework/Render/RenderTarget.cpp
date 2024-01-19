#include "Framework.h"

RenderTarget::RenderTarget(UINT width, UINT height, DXGI_FORMAT format)
	: width(width), height(height), format(format)
{
	CreateRTVTexture();
	CreateRTV();
	CreateSRV();
}

RenderTarget::~RenderTarget()
{
	// �ؽ�ó Ŭ������ ����, ������ ������ ��������� ������ ������ �����
	rtvTexture->Release();
	rtv->Release();
	srv->Release();
}

void RenderTarget::Set(DepthStencil* depthStencil, Float4 clearColor)
{
	DC->OMSetRenderTargets(1, &rtv, depthStencil->GetDSV());
	// DX ���� �Լ��� ���� ���� Ÿ�� ��ü�� ���� : ����Ʈ ����, �����, ���� ���ٽ� ���¿� �並 �Ű������� ����

	DC->ClearRenderTargetView(rtv, (float*)&clearColor);
	// �� �ʱ�ȭ (������ �ʱ�ȭ������ ���� ����(Desc, ������)�� �״�� ����� ��)
	// -> ���� ���� (�׸��� ���� ������ �ʱ�ȭ��, �׸��� ������ �� ������) �並
	//    ��°���(�ι��̾��Ʈ)�� ����

	depthStencil->Clear();

	Environment::Get()->Set();
	Environment::Get()->SetViewport(width, height);
}

void RenderTarget::SetMulti(RenderTarget** target, UINT count, DepthStencil* depthStencil, Float4 clearColor)
{
	vector<ID3D11RenderTargetView*> rtvs; // ���� Ÿ�� ��"��"

	FOR(count) // �Ű������� ������ ������ŭ
	{
		rtvs.push_back(target[i]->GetRTV()); // �Ű������� ���� ���� Ÿ��"��"�� i���� ���� �ֱ�
		DC->ClearRenderTargetView(rtvs.back(), (float*)&clearColor); // ���� ���� ���� Ÿ���� ���� ����
	}

	depthStencil->Clear(); // �ϴ� ���ʵ� �ʱ�ȭ

	DC->OMSetRenderTargets(count, rtvs.data(), depthStencil->GetDSV());
	// ���� ������ŭ ���� Ÿ�� �����ؼ� ��"��"�� �����ϰ�, �߰� �ɼ��� ����(������ Ŭ����)

	Environment::Get()->Set();
	// ���� ���� ����(��ġ�� ũ��)�� ���⼭�� ���� �ٷ��� �ʽ��ϴ�
	// �ʿ��ϸ� ������ - Ȥ�� �ܺο��� ���� ������ �ؾ� �Ѵ�
}

void RenderTarget::CreateRTVTexture()
{
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width            = width;
	desc.Height           = height;
	desc.MipLevels        = 1;
	desc.ArraySize        = 1;
	desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM; // ����(��ü 3Dȭ) ���� �⺻ RGB ����
	desc.SampleDesc.Count = 1;
	desc.Usage            = D3D11_USAGE_DEFAULT;
	desc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	DEVICE->CreateTexture2D(&desc, nullptr, &rtvTexture);
	// ������ ����ü, ������� �� Ŭ������ �ؽ�ó��
}

void RenderTarget::CreateRTV()
{
	D3D11_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format        = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	DEVICE->CreateRenderTargetView(rtvTexture, &desc, &rtv);
}

void RenderTarget::CreateSRV()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format              = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension       = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = 1; // �� ������ 1�� �ƴ� ��츦 ����ؼ� �ڵ常 �ۼ�

	DEVICE->CreateShaderResourceView(rtvTexture, &desc, &srv);
}

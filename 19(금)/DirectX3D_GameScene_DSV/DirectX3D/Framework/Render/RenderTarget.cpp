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
	// 텍스처 클래스에 없고, 윈도우 식으로 만드었으니 윈도우 식으로 지우기
	rtvTexture->Release();
	rtv->Release();
	srv->Release();
}

void RenderTarget::Set(DepthStencil* depthStencil, Float4 clearColor)
{
	DC->OMSetRenderTargets(1, &rtv, depthStencil->GetDSV());
	// DX 제공 함수를 통해 렌더 타겟 구체적 설정 : 뷰포트 개수, 결과물, 뎁스 스텐실 상태와 뷰를 매개변수로 지정

	DC->ClearRenderTargetView(rtv, (float*)&clearColor);
	// 뷰 초기화 (영역은 초기화했지만 내부 설명(Desc, 설정값)은 그대로 적용될 것)
	// -> 지금 만든 (그리고 최초 배경색을 초기화한, 그리고 설정을 또 적용한) 뷰를
	//    출력과정(인바이언먼트)에 적용

	depthStencil->Clear();

	Environment::Get()->Set();
	Environment::Get()->SetViewport(width, height);
}

void RenderTarget::SetMulti(RenderTarget** target, UINT count, DepthStencil* depthStencil, Float4 clearColor)
{
	vector<ID3D11RenderTargetView*> rtvs; // 렌더 타겟 뷰"들"

	FOR(count) // 매개변수로 지정된 개수만큼
	{
		rtvs.push_back(target[i]->GetRTV()); // 매개변수로 받은 렌더 타겟"들"의 i번쨰 값을 넣기
		DC->ClearRenderTargetView(rtvs.back(), (float*)&clearColor); // 새로 넣은 렌더 타겟의 배경색 지정
	}

	depthStencil->Clear(); // 일단 이쪽도 초기화

	DC->OMSetRenderTargets(count, rtvs.data(), depthStencil->GetDSV());
	// 받은 개수만큼 렌더 타겟 생성해서 뷰"들"에 적용하고, 추가 옵션은 없음(위에서 클리어)

	Environment::Get()->Set();
	// 여러 개의 영역(위치와 크기)은 여기서는 직접 다루지 않습니다
	// 필요하면 사전에 - 혹은 외부에서 따로 설정을 해야 한다
}

void RenderTarget::CreateRTVTexture()
{
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width            = width;
	desc.Height           = height;
	desc.MipLevels        = 1;
	desc.ArraySize        = 1;
	desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM; // 법선(자체 3D화) 없는 기본 RGB 형식
	desc.SampleDesc.Count = 1;
	desc.Usage            = D3D11_USAGE_DEFAULT;
	desc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	DEVICE->CreateTexture2D(&desc, nullptr, &rtvTexture);
	// 원본은 구조체, 결과물은 이 클래스의 텍스처로
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
	desc.Texture2D.MipLevels = 1; // 밉 레벨이 1이 아닐 경우를 대비해서 코드만 작성

	DEVICE->CreateShaderResourceView(rtvTexture, &desc, &srv);
}

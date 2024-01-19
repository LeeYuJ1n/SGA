#pragma once

class RenderTarget
{
	// ○ More
	
	// 렌더 타겟 : 렌더할 대상을 뷰포트 전체가 아닌 지정된 영역에 부분적으로 투사하는 것
	//            그리고 이 과정을 담당할 클래스를 지정하기도 한다

public:
	// ○ 생성자
	RenderTarget(UINT width  = WIN_WIDTH,
		         UINT height = WIN_HEIGHT,
		         DXGI_FORMAT = DXGI_FORMAT_R32G32B32A32_FLOAT);
	// 기본은 윈도우 전체 크기만큼, 일반 출력처럼

	// ○ 소멸자
	~RenderTarget();

	void Set(DepthStencil* depthStencil, Float4 clearColor = Float4(1 ,1, 1, 1)); // 뎁스 스텐실 자료 필요, 기본 색깔(배경색)은 하얀색
	static void SetMulti(RenderTarget** target,
		                 UINT count, 
		                 DepthStencil* depthStencil,
		                 Float4 clearColor = Float4(1, 1, 1, 1));
	// 뎁스 스텐실 자료 필요, 기본 색깔(배경색)은 하얀색
	// 그리고 1개 이상의 렌더 타겟 필요
	// (첫 매개변수 = 포인터의 배열 (혹은 포인터로 표시 가능한 데이터의 배열))

	ID3D11ShaderResourceView*& GetSRV() { return srv; } // &로 인해 변경 가능
	ID3D11RenderTargetView*& GetRTV() { return rtv; }   // &로 인해 변경 가능

private:
	void CreateRTVTexture();
	void CreateRTV();
	void CreateSRV();

private:
	// ○ 내부 데이터

	UINT width;
	UINT height;

	DXGI_FORMAT format; // 그래픽 형식 - 나중에 따로 이용할 떄를 위한 보험코드

	ID3D11Texture2D* rtvTexture;    //렌더 타겟용 재생성 텍스처 (시각적 결과)
	ID3D11RenderTargetView* rtv;    // 렌더 타겟 뷰
	ID3D11ShaderResourceView* srv;  // 셰이더 리소스
};


#pragma once

class GBuffer
{
	// G Buffer : 지오메트리(모양) 버퍼
	//            전체 월드의 형태(공간과 씬의 형태)를 빠르게 연산할 수 있도록 데이터를
	//            모으고 분류하는 버퍼 클래스

	// -> 전체 월드의 형태를 빠르게 연산해서 어쩔 건가? -> 투사할 거다
	// -> 렌더 타겟을 더욱 컴퓨터 입장에서는 빠르게, 사람 입장에서 보기 쉽게 분류하는 것

public:
	// ○ 생성자
	GBuffer();

	// ○ 소멸자
	~GBuffer();

	// ○ 함수
	void SetMultiRenderTarget();
	void PostRender();
	void SetSRVs();

private:
	// 여기에 필요한 렌더 타겟 정보들을 넣어둔다

	// 아래 두 줄 코드가 실제 코드이며, 나중에 사용할 때 주석을 풀어서 쓴다
	// vector<RenderTarget*> renderers;                // <- 이런 벡터로 만든 렌더 타겟"들"이 기본형
	// vector< ID3D11ShaderResourceView*> shaderViews; // 기본형에 대응하는 셰이더 리소스

	// ○ 샘플 데이더
	
	// 이하 데이터는 샘플 : 강의 진행 과정에서 쓰기 위한 임시 데이터
	// 구조는 위 기본혀과 같다 : 여러 개의 렌더 타겟을 각각 설정해 가면서 다른 화면을 띄우는 것이 목적
	RenderTarget* diffuseRender;
	RenderTarget* specularRender;
	RenderTarget* normalRender;

	DepthStencil* depthStencil;

	RenderTarget* rtvs[3];

	class Quad* quads[4]; // 나중에 띄울 쿼드는 4개
	ID3D11ShaderResourceView* srvs[4];
};


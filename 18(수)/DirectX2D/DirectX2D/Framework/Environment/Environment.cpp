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
    samplerDesc.Filter         = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;;        
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;      
    samplerDesc.MinLOD         = 0;
    samplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;
    //LOD(Level Of Detail) : 카메라의 거리에 따라서 퀄리티를 다르게 하는 것

    DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

    DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
    D3D11_BLEND_DESC blendDesc = {};    
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend    = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend   = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp     = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    // // 단일 블렌드 상태일 때 적용 가능한 기본 출력
    // DEVICE->CreateBlendState(&blendDesc, &blendState);
    // 
    // float blendFactor[4] = {};
    // DC->OMSetBlendState(blendState, blendFactor, 0xffffffff);

    // 복수 블렌드 상태일 때 적용 가능한 병합 출력
    DEVICE->CreateBlendState(&blendDesc, &alphaBlendState); // 블렌드 상태 설정을 알파로 넘긴다

    float blendFactor[4] = {};
    DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff); // 상태 설정을 받은 알파 상태로 병합상태를 만든다

    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE; // 색 정보를 추가 연산하지 않음 (1, 1, 1, 1)

    DEVICE->CreateBlendState(&blendDesc, &additiveBlendState); // 동일 정보를 이용해서 추가 블렌드까지 설정

    // -> 병합을 두 번 수행해서 출력하는 상태 설정이 이루어진다
}

void Environment::CreateRasterizerState() //래스터화 생성
{
    // 나중에 다른 부분이 추가될 수도 있지만, 지금은 일단 백페이스 컬링 해제부터

    // 데이터 받기부터
    D3D11_RASTERIZER_DESC rasterizerDesc = {};

    //받은 데이터에서 원하는 설정을 넣은 후...
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    // -> 컬링을 하지 않겠다 : 모든 텍스처를 보이겠다
    //D3D11_CULL_FRONT : 프론트 페이스 컬링, 앞을 향한 텍스처를 출력하지 않음
    //D3D11_CULL_BACK : 백 페이스 컬링, 뒤를 향한 텍스처를 출력하지 않음 (다이렉트X 11의 기본 설정)
    //D3D11_CULL_NONE : 페이스 컬링 없음 (앞이어도 출력, 뒤여도 출력)

    // *3D환경을 예로 들어도 프론트 페이스 컬링이나 페이스 컬링이 없는 게 필요할 때가 있단 말인가? 그렇습니다.
    // 프론트 페이스 컬링은 언제? : 내가, 혹은 플레이어 캐릭터가 절대로 넘어갈 수 없는 배경을 표현할 때 유용하다
    // 페이스 컬링 없음은 언제?   : 어떤 이유로든 게임 속에 나와 대칭이 되는 "반사 상"이 존재할 때

    rasterizerDesc.FillMode = D3D11_FILL_SOLID; //추가 재처리나 투명처리 없이, 그림의 모든 화소를 보이겠다
    // rasterizerDesc.DepthBias = // <- 나중에 그림이나 텍스처로 인한 그림자 등이 발생해야 할 경우 혹은 그림자가 져야 할 경우, 이 화소가 가질 "깊이"를 설정할 수 있다

    //설정을 반영해서 실제 상태정보를 만들고 DC에 반영
    DEVICE->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

    DC->RSSetState(rasterizerState);
}

void Environment::SetAlphaBlend()
{
    float blendFactor[4] = { 0, 0, 0, 0 };
    DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
    // 블렌드 병합 세팅 함수 호출 (을 통한 병합 상태 설정)
    // 매개변수 : 1. 호출하고 또 저장할 블렌드 상태 변수 (alphaBlendState)
    //           2. 병합 시의 기준 요소 (blendFactor, 보통은 모두 0)
    //           3. 제외할 화소정보가 있을 경우 입력 (혹은 없으면 0xffffffff)
    //              * 0xffffffff : int의 표기법 중 하나 (0x 표시 뒤에 16진수로 표기)
    //              바이트 기준으로 나눴을 때 각 2바이트씩 의미가 달라지기 때문에 보는 사람이 이해하기 쉬우라고 16진수로 굳이 표시

    // * 이 중에서 샘플 마스크가 수동 설정이 필요하다면 매개변수로 받으면 된다
}

void Environment::SetAdditiveBlend()
{
    float blendFactor[4] = { 0, 0, 0, 0 };
    DC->OMSetBlendState(additiveBlendState, blendFactor, 0xffffffff);
}
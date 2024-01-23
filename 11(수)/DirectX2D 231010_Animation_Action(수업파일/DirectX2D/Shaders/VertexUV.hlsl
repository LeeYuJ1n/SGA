// 버텍스 "UV" 셰이더

// 기본적으로는 버텍스 셰이더와 형태가 거의 같다
// 차이 : SV (버텍스가 가진 실제 정보) 대신 UV라는 자료를 사용한다

// UV : 텍스처의 상대 좌표를 지칭한다 (=텍스처도 트랜스폼처럼 자기만의 좌표 기준이 따로 있다)

// 조금 더 구체적으로.... 텍스처 등 프로그래밍에서 쓰이는 부가 시각 정보 좌표계는

// 원리상으로는 xyz 3차원 기하를 따르긴 하지만, 실제 구현된 행렬 공간과는 표현이 다르다는 것을 명확히 하기 위해서 (의도의 문제)

// 자기들이 사용하는 축의 이름을 u v w 라고 명명한다. 그래서 UV 좌표계

// 구분하자면, 같은 원론상의 축이지만...

// x y z : 일반적인 축
// u v w : 텍스터를 위한 UV좌표

cbuffer WorldBuffer : register(b0)
{
    matrix world;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, projection);
    output.uv = input.uv;
	
    return output;
}
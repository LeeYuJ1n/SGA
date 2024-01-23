#pragma once

class Environment : public Singleton<Environment>
{
private:
    friend class Singleton;

    Environment();
    ~Environment();

private:
    void CreateProjection();
    void CreateSamplerState();
    void CreateBlendState();
    void CreateRasterizerState(); // 래스터화 생성 함수

private:
    MatrixBuffer* projectionBuffer;

    ID3D11SamplerState* samplerState;        // 텍스처 샘플링(기본 출력)에 대한 설정
    ID3D11BlendState* blendState;            // 블렌드 (색 재처리)에 대한 설정
    ID3D11RasterizerState* rasterizerState;  // 래스터라이즈(벡터와 셰이더를 모니터용픽셀로 바꿔주는 일)에 대한 설정
                                             // 일종의 최종 확인을 그래픽에 시켜줄 수 있다 -> 래스터라이즈가 끝나면 나오는 결과는 모니터에 바로 나올 테니까
};
#pragma once

class Material
{
public:
    Material();
    Material(wstring shaderFile);
    ~Material();

    void Set();

    void RenderUI();

    void SetShader(wstring shaderFile);
    void SetDiffuseMap(wstring textureFile);
    
private:
    // 매티리얼 클래스가 기본적으로 가지는 것
    // -> 무슨 그림이냐 (가장 중요한 정보) : 코딩 식으로 말하면 이 정보는 절대 nullptr로 남아있으면 안 된다
    // -> 이 그림을 어떻게 표현할 것인가
    //    : 셰이더 설정
    //    : 코드나 엔진 등에서 추가로 정하는 각종 설정값(이미지 후보정, 채도, 명암, 즉석 질감 표현 등...)
    //    : 그래서 매티리얼들이 실제로 각 앱에서 어떻게 정의되는지는 보통 앱, 코드, 엔진마다 다르다

    string name; // 이름이라는 정보

    VertexShader* vertexShader; // 어떤 셰이더를 사용할 것인가
    PixelShader* pixelShader;   // 어떤 셰이더를 사용할 것인가

    Texture* diffuseMap = nullptr; // 초기값은 이렇게 주지만, 객체가 만들어질 때는 반드시 지정하는 그림이 있어야 한다
};
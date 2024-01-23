#pragma once

class ShaderScene : public Scene
{
public:
	ShaderScene();
	~ShaderScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Init() override;
	virtual void Quit() override;

private:
	// 한 그림에 여러 셰디어를 적용하는 씬

	// 실제 그림 (출력 대상)
	Quad* quad;

	// 필터로 그림이 쓰일 경우 해당 텍스처도 필요
	Texture* secondMap; // 두 번째 맵핑

	// 화소 정보를 주고받기 위한 버퍼들이 필요하다
	// -> 그런데 버퍼 내용들이 대체로 색, 정점 같은 숫자가 주로 쓰이고
	//    + 자료 내용도 필요에 따라 바뀔 수 있다
	//    -> 자료형은 고정에 가깝고, 정작 데이터의 의미는 경우에 따라 달라질 수도 있다
	//    -> 그냥 자료형이 고정된 버퍼가 있다면 이런 경우에는 더 호출이 편리해질 수 있다 (의미도 명확)
	
	// ConstBuffer* firstValueBuffer;
	// ConstBuffer* secondValueBuffer; // 자료형이 안 정해진 버퍼 (범용성 높지만 불편, 귀찮, 가끔 오류)

	IntValueBuffer* intValueBuffer;     // 정수만 받는 버퍼
	FloatValueBuffer* floatValueBuffer; // 소수만 받는 버퍼
};


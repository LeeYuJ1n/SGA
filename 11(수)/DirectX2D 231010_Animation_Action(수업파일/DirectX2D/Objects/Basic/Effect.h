#pragma once

class Effect : public Quad
{
public:
	Effect(wstring file, Vector2 maxFrame, float speed, bool isAdditive); // 이펙트 생성 시에 그림, 최대 프레임(끝날 시점의 그림), 속도와, "추가" 여부
	~Effect();

	void Update();
	void Render();
	void Play(Vector2 startPos);
	void End();

private:
	FrameBuffer* frameBuffer; // 각 이펙트가 독자적으로 가질 프레임 + 셰이더 정보

	// 이펙트의 특징 중 하나 : 게임의 속도와는 별개로 자기만의 속도가 필요할 수 있다
	float speed;               // 속도
	const float FPS = 10.0f;   // 기준 될 초당 프레임 재생수
	float delayTime = 1 / FPS; // 지연 시간, 혹은 재생속도 + 최초 재생시점
	float frameTime = 0;       // 프레임 간의 최소 간격

	// 생성시점이나 외부에 줄 자료가 필요할 때
	UINT curFrameNum = 0;
	UINT maxFrameNum = 0;
	UINT maxFrameX   = 0;

	// 이 애니메이션이 다른 조건에서 색이나 재생 분량에 영향을 줄 / 받을 것인가?
	bool isAdditive; // 추가 재생인가?
};


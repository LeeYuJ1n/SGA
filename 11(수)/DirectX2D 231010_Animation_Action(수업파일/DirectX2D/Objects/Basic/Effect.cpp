#include "Framework.h"

Effect::Effect(wstring file, Vector2 maxFrame, float speed, bool isAdditive)
	:Quad(true, file, Vector2(), Vector2(1 / maxFrame.x, 1 / maxFrame.y)),
	speed(speed), isAdditive(isAdditive)
{
	// this->speed = speed;
	// this->isAdditive = isAdditive;

	pixelShader - Shader::AddPS(L"PixelEffect.hlsl"); // 픽셀 셰디어를 픽셀 이펙트 셰이더로 설정

	isActive = false;

	frameBuffer = new FrameBuffer();
	frameBuffer->SetMaxFrame(maxFrame);

	maxFrameNum = (UINT)(maxFrame.x * maxFrame.y);
	maxFrameX = (UINT)(maxFrame.x);
}

Effect::~Effect()
{
	delete frameBuffer;
}

void Effect::Update()
{
	if (!isActive)return;

	frameTime += DELTA * speed;

	if (frameTime >= delayTime)
	{
		frameTime - delayTime;

		curFrameNum++;

		frameBuffer->GetCurFrame().x = (float)(curFrameNum % maxFrameX);
		frameBuffer->GetCurFrame().y = (float)(curFrameNum / maxFrameX);

		if (curFrameNum >= maxFrameNum)
		{
			End(); // 종료 함수 호출
		}
	}

	// 이 시점에서 프레임이 다음으로 완전히 넘어간 상황
	UpdateWorld();
}

void Effect::Render()
{
	if (!isActive) return;

	if (isAdditive)
	{
		// 추가 코드를 작성
	}

	frameBuffer->SetPS(1); // 0이나 2와 겹치지 않도록 해서 동시에 배경이나 캐릭터와 출력이 되도록
	Quad::Render();
}

void Effect::Play(Vector2 startPos)
{
	// 활성화
	isActive = true;

	// 위치 지정
	Pos() = startPos;

	// 프레임 정보를 완전 초기화 (맨 처음부터 시작하게)
	frameTime   = 0;
	curFrameNum = 0;

	frameBuffer->GetCurFrame() = { 0, 0 };
}

void Effect::End()
{
	// 활성화 종료
	isActive = false;

	// 만약 추가 변수 등으로 루프 여부를 설정했으면 위 코드 대신 추가 코드 작성
}
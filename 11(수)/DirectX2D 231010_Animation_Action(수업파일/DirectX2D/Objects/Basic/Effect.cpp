#include "Framework.h"

Effect::Effect(wstring file, Vector2 maxFrame, float speed, bool isAdditive)
	:Quad(true, file, Vector2(), Vector2(1 / maxFrame.x, 1 / maxFrame.y)),
	speed(speed), isAdditive(isAdditive)
{
	// this->speed = speed;
	// this->isAdditive = isAdditive;

	pixelShader - Shader::AddPS(L"PixelEffect.hlsl"); // �ȼ� �ε� �ȼ� ����Ʈ ���̴��� ����

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
			End(); // ���� �Լ� ȣ��
		}
	}

	// �� �������� �������� �������� ������ �Ѿ ��Ȳ
	UpdateWorld();
}

void Effect::Render()
{
	if (!isActive) return;

	if (isAdditive)
	{
		// �߰� �ڵ带 �ۼ�
	}

	frameBuffer->SetPS(1); // 0�̳� 2�� ��ġ�� �ʵ��� �ؼ� ���ÿ� ����̳� ĳ���Ϳ� ����� �ǵ���
	Quad::Render();
}

void Effect::Play(Vector2 startPos)
{
	// Ȱ��ȭ
	isActive = true;

	// ��ġ ����
	Pos() = startPos;

	// ������ ������ ���� �ʱ�ȭ (�� ó������ �����ϰ�)
	frameTime   = 0;
	curFrameNum = 0;

	frameBuffer->GetCurFrame() = { 0, 0 };
}

void Effect::End()
{
	// Ȱ��ȭ ����
	isActive = false;

	// ���� �߰� ���� ������ ���� ���θ� ���������� �� �ڵ� ��� �߰� �ڵ� �ۼ�
}
#pragma once

class Effect : public Quad
{
public:
	Effect(wstring file, Vector2 maxFrame, float speed, bool isAdditive); // ����Ʈ ���� �ÿ� �׸�, �ִ� ������(���� ������ �׸�), �ӵ���, "�߰�" ����
	~Effect();

	void Update();
	void Render();
	void Play(Vector2 startPos);
	void End();

private:
	FrameBuffer* frameBuffer; // �� ����Ʈ�� ���������� ���� ������ + ���̴� ����

	// ����Ʈ�� Ư¡ �� �ϳ� : ������ �ӵ��ʹ� ������ �ڱ⸸�� �ӵ��� �ʿ��� �� �ִ�
	float speed;               // �ӵ�
	const float FPS = 10.0f;   // ���� �� �ʴ� ������ �����
	float delayTime = 1 / FPS; // ���� �ð�, Ȥ�� ����ӵ� + ���� �������
	float frameTime = 0;       // ������ ���� �ּ� ����

	// ���������̳� �ܺο� �� �ڷᰡ �ʿ��� ��
	UINT curFrameNum = 0;
	UINT maxFrameNum = 0;
	UINT maxFrameX   = 0;

	// �� �ִϸ��̼��� �ٸ� ���ǿ��� ���̳� ��� �з��� ������ �� / ���� ���ΰ�?
	bool isAdditive; // �߰� ����ΰ�?
};


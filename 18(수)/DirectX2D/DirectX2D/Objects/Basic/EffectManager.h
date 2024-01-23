#pragma once

class EffectManager : public Singleton<EffectManager>
{
private:
	friend class Singleton;

	EffectManager() = default;
	~EffectManager();

public:
	void Update();
	void Render();

	// ����Ʈ �߰�
	void Add(string key, wstring file, float frame_x, float frame_y, float speed = 1.0f, bool isAdditive = false);
	void Add(string key, int poolSize, wstring file, float frame_x, float frame_y, float speed = 1.0f, bool isAdditive = false);
	
	// ����Ʈ ���
	void Play(string key, Vector2 pos);
	
	// ���� ����
	void SetColor(string key, float r, float g, float b, float a = 1.0f);

	// ���� �߰�...�ε� �ϴ� ���¸�
	void SetKF() {} // KF : Ű ������ �ε���

private:
	typedef vector<Effect*> Effects;   // �� ���� ����Ʈ�� ���� �ϳ��� ����
	map<string, Effects> totalEffects; // �� ����Ʈ ������ �����ϱ� ���� ��
};


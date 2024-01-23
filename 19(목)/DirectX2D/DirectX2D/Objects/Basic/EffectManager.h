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

	// 이펙트 추가
	void Add(string key, wstring file, float frame_x, float frame_y, float speed = 1.0f, bool isAdditive = false);
	void Add(string key, int poolSize, wstring file, float frame_x, float frame_y, float speed = 1.0f, bool isAdditive = false);
	
	// 이펙트 재생
	void Play(string key, Vector2 pos);
	
	// 색상 설정
	void SetColor(string key, float r, float g, float b, float a = 1.0f);

	// 길이 추가...인데 일단 형태만
	void SetKF() {} // KF : 키 프레임 인덱스

private:
	typedef vector<Effect*> Effects;   // 한 종류 이펙트당 벡터 하나씩 배정
	map<string, Effects> totalEffects; // 각 이펙트 종류를 관리하기 위한 맵
};


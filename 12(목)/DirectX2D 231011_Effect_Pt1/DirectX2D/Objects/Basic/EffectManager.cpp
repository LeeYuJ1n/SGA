#include "Framework.h"

EffectManager::~EffectManager()
{
	for (pair<string, Effects> effects : totalEffects)
	{
		for (Effect* effect : effects.second)
		{
			delete effect;
		}
	}
}

void EffectManager::Update()
{
	for (pair<string, Effects> effects : totalEffects)
	{
		for (Effect* effect : effects.second)
		{
			effect->Update();
		}
	}
}

void EffectManager::Render()
{
	for (pair<string, Effects> effects : totalEffects)
	{
		for (Effect* effect : effects.second)
		{
			effect->Render();
		}
	}
}

// 이펙트 추가
void EffectManager::Add(string key, wstring file, float frame_x, float frame_y, float speed, bool isAdditive)
{
	if (totalEffects.count(key) > 0) return; // 중복 방지

	// 맵에 등록하기 전에, 등록을 위한 이펙트 벡터부터 생성
	Effects effects(10);

	for (Effect*& effect : effects)
	{
		effect = new Effect(file, Vector2(frame_x, frame_y), speed, isAdditive);
	}

	totalEffects[key] = effects;
}

void EffectManager::Add(string key, int poolSize, wstring file, float frame_x, float frame_y, float speed, bool isAdditive)
{
	if (totalEffects.count(key) > 0) return; // 중복 방지

	// 맵에 등록하기 전에, 등록을 위한 이펙트 벡터부터 생성
	Effects effects(poolSize);

	for (Effect*& effect : effects)
	{
		effect = new Effect(file, Vector2(frame_x, frame_y), speed, isAdditive);
	}

	totalEffects[key] = effects;
}

// 이펙트 재생
void EffectManager::Play(string key, Vector2 pos)
{
	if (totalEffects.count(key) == 0) return; // 자료 적합(존재) 검사

	for (Effect * effect : totalEffects[key])
	{
		if (!effect->Active())
		{
			effect->Play(pos);
			return;
		}
	}
}

// 색상 설정
void EffectManager::SetColor(string key, float r, float g, float b, float a)
{
	if (totalEffects.count(key) == 0) return; // 자료 적합(존재) 검사

	for (Effect* effect : totalEffects[key])
	{
		effect->GetColor() = { r, g, b, a }; // 이펙트의 쿼드 정보에 색깔 할당
	}
}
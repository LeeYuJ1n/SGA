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

// ����Ʈ �߰�
void EffectManager::Add(string key, wstring file, float frame_x, float frame_y, float speed, bool isAdditive)
{
	if (totalEffects.count(key) > 0) return; // �ߺ� ����

	// �ʿ� ����ϱ� ����, ����� ���� ����Ʈ ���ͺ��� ����
	Effects effects(10);

	for (Effect*& effect : effects)
	{
		effect = new Effect(file, Vector2(frame_x, frame_y), speed, isAdditive);
	}

	totalEffects[key] = effects;
}

void EffectManager::Add(string key, int poolSize, wstring file, float frame_x, float frame_y, float speed, bool isAdditive)
{
	if (totalEffects.count(key) > 0) return; // �ߺ� ����

	// �ʿ� ����ϱ� ����, ����� ���� ����Ʈ ���ͺ��� ����
	Effects effects(poolSize);

	for (Effect*& effect : effects)
	{
		effect = new Effect(file, Vector2(frame_x, frame_y), speed, isAdditive);
	}

	totalEffects[key] = effects;
}

// ����Ʈ ���
void EffectManager::Play(string key, Vector2 pos)
{
	if (totalEffects.count(key) == 0) return; // �ڷ� ����(����) �˻�

	for (Effect * effect : totalEffects[key])
	{
		if (!effect->Active())
		{
			effect->Play(pos);
			return;
		}
	}
}

// ���� ����
void EffectManager::SetColor(string key, float r, float g, float b, float a)
{
	if (totalEffects.count(key) == 0) return; // �ڷ� ����(����) �˻�

	for (Effect* effect : totalEffects[key])
	{
		effect->GetColor() = { r, g, b, a }; // ����Ʈ�� ���� ������ ���� �Ҵ�
	}
}
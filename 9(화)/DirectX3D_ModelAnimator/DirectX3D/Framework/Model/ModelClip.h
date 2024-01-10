#pragma once

class ModelClip
{
	// ���� �����Ӻ� �޽ø� ��Ƽ� ������ "������"
	// -> �����̴� ������ ���� ����� �ְ� �޾ƾ� �ϹǷ�

private: // �ʿ��ϸ� public���� Ǯ� ������, �ִϸ����� ����� ���� �� �ʿ䰡 ����
	friend class ModelAnimator;

	ModelClip() = default; // �⺻ �����ڷθ� ���ڴ�
	~ModelClip();

	KeyFrame* GetKeyFrame(string boneName);

private:
	string name; // �� �������� �̸�
	UINT frameCount; // �� �������� ������ �������� ����
	float tickPerSecond; // �� �������� ����� �⺻ �ӵ� (1�ʿ� �� �� ���� ��ü�ϴ°�?)
	float duration; // ���� �ð�

	float playTime = 0; // ��� �ð� (0���� �ʱ�ȭ)

	unordered_map<string, KeyFrame*> keyFrames; // �������� ��
};


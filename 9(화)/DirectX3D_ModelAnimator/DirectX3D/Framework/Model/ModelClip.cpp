#include "Framework.h"

ModelClip::~ModelClip()
{
	for (auto keyFrame : keyFrames) // auto : �ƶ��� ���� �ڷ����� �ڵ����� �������ִ� ��ɾ�. ������ ��ȿ����, ������ ����
	// for (pair<string, KeyFrame*> keyFrame : keyFrames)
	{
		delete keyFrame.second; // string�� ���� �� ������ �Ǵϱ�
	}
}

KeyFrame* ModelClip::GetKeyFrame(string boneName)
{
	// Ű ������ �޾Ƽ� ��ȯ�ϱ�

	// ������ �ƹ��͵� ���� ������ ��ȯ
	if (keyFrames.count(boneName) == 0) return nullptr;

	// ������ �ִ´�� ��ȯ
	return keyFrames[boneName];
}

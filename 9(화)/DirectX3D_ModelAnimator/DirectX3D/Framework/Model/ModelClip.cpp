#include "Framework.h"

ModelClip::~ModelClip()
{
	for (auto keyFrame : keyFrames) // auto : 맥락에 따라 자료형을 자동으로 참조해주는 명령어. 느리고 비효율적, 오류도 있음
	// for (pair<string, KeyFrame*> keyFrame : keyFrames)
	{
		delete keyFrame.second; // string은 굳이 안 지워도 되니까
	}
}

KeyFrame* ModelClip::GetKeyFrame(string boneName)
{
	// 키 프레임 받아서 반환하기

	// 없으면 아무것도 없는 포인터 반환
	if (keyFrames.count(boneName) == 0) return nullptr;

	// 있으면 있는대로 반환
	return keyFrames[boneName];
}

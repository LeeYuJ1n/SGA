#include "Framework.h"

ModelClip::~ModelClip()
{
    for (auto keyFrame : keyFrames) // auto : �ƶ��� ���� �ڷ����� �ڵ����� �������ִ� ��ɾ�. ������ ��ȿ����, ������ ����
    //for (pair<string, KeyFrame*> keyFrame : keyFrames)
    {
        delete keyFrame.second; // string�� ���� �� ������ �Ǵϱ�
    }
}

void ModelClip::Init()
{
    eventIter = events.begin();
    playTime = 0.0f;
    duration = frameCount / tickPerSecond;
}

void ModelClip::Excute()
{
    if (events.empty()) return;
    if (eventIter == events.end()) return;

    float ratio = playTime / duration;

    if (eventIter->first > ratio) return;

    eventIter->second();
    eventIter++;
}

KeyFrame* ModelClip::GetKeyFrame(string boneName)
{
    // Ű ������ �޾Ƽ� ��ȯ�ϱ�

    // ������ �ƹ��͵� ���� ������ ��ȯ
    if (keyFrames.count(boneName) == 0) return nullptr;

    //������ �ִ� ��� ��ȯ
    return keyFrames[boneName];
}

void ModelClip::SetEvent(Event event, float timeRatio)
{
    if (events.count(timeRatio) > 0) return;

    events[timeRatio] = event;
}

#pragma once

class ModelClip
{
    // ���� �����Ӻ� �޽��� ��Ƽ� ������ "������"
    // -> �����̴� ������ ���� ����� �ְ�޾ƾ� �ϹǷ�

private: // �ʿ��ϸ� public���� Ǯ� ������, �ִϸ����� ����� ���� �� �ʿ䰡 ����
    friend class ModelAnimator;
    friend class ModelAnimatorInstancing;

    ModelClip() = default; // "�⺻ �����ڷθ� ���ô�"
    ~ModelClip();

    void Init();
    void Excute();

    KeyFrame* GetKeyFrame(string boneName);

public:
    void SetEvent(Event event, float timeRatio);

private:
    string name; // �� �������� �̸�

    UINT frameCount; // �� �������� ������ �������� ����
    float tickPerSecond; // �� �������� ����� �⺻ �ӵ� (1�ʿ� �� �� ���� ��ü�ϴ°�?)
    float duration;  // ���� �ð�

    float playTime = 0.0f;

    unordered_map<string, KeyFrame*> keyFrames;

    map<float, Event> events;
    map<float, Event>::iterator eventIter;
};
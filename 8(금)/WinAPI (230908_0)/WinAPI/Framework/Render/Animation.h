#pragma once

class Animation
{
private:
    const float FRAME_PER_SECOND = 10.0f;

public:
    Animation(POINT imageFrame, float speed = 1.0f);
    ~Animation() = default;

    void Update();

    void SetDefault(bool loop = false, bool pingpong = false);
    void SetPart(int start, int end, bool loop = false, bool pingpong = false);

    void SetPingpong();

    void Play() { isPlay = true, curFrameNum = 0; }
    void Stop();

    void SetSpeed(float speed) { this->speed = speed; }

    bool IsPlay() { return isPlay; }
    POINT GetFrame() { return frames[action[curFrameNum]]; }

    void SetEndEvent(function<void()> event) { endEvent = event; }

private:
    vector<POINT> frames;
    vector<int> action;

    int curFrameNum = 0;

    POINT imageFrame;

    bool isPlay = false;
    bool isLoop = false;

    float playTime = 0.0f;
    float speed;
    float intervalTime = 0.0f;

    function<void()> endEvent = nullptr;
};
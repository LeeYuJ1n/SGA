#pragma once

using namespace FMOD;

class Audio : public Singleton<Audio>
{
private:
    friend class Singleton;

    const int MAX_CHANNEL = 20;
    // 채널 : 셰이더의 슬롯 레지스터와 비슷한 개념. 동시 출력 가능한 최대 데이터 숫자
    //       동시에 여러 소리를 재생할 경우, 각각 다른 채널로 출력된다

    struct SoundInfo
    {
        Sound* sound = nullptr;
        Channel* channel = nullptr;

        ~SoundInfo()
        {
            sound->release();
        }
    };

    Audio();
    ~Audio();

public:
    void Update();

    void Add(string key, string file,
        bool bgm = false, bool loop = false);

    void Play(string key, float valume = 1.0f); //재생
    void Stop(string key); //정지
    void Pause(string key); // 일시 정지
    void Resume(string key); // 멈춘 곳에서 재개

    bool IsPlaySound(string key);

private:
    System* soundSystem;

    unordered_map<string, SoundInfo*> sounds;
};
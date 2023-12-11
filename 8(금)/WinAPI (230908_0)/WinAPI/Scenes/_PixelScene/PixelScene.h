#pragma once

class PixelScene : public Scene
{
    //픽셀 충돌 구현 전용 씬

public:
    PixelScene();
    ~PixelScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

private:
    //플레이어
    PixelCharacter* player;

    // 배경 (단순한 배경 그림x, 가능하면 바닥일 수도 있도록 해보고 싶습니다!)
    Landscape* land;


/////////////////////////////////////////////////////////////////
    //진행도 (총 진행도 수치는 임시입니다)
private:

    float totalProcess = 300.0f;

    float currentProcess = 0;
    float lastProcess = 0;

    bool ProcessChanged()
    {
        if (currentProcess != lastProcess)
        {
            lastProcess = currentProcess;
            return true;
        }
        else return false;
    }
};


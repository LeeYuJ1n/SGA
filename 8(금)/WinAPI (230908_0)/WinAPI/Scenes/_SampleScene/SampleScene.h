#pragma once
class SampleScene : public Scene
{
public:
    SampleScene();
    ~SampleScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

private:
    Landscape* landscape;
    SampleCharacter* player;

    ImageRect* land;

    bool isLoop = false;
};


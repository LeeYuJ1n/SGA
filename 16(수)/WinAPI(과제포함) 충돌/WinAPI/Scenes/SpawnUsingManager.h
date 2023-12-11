#pragma once

class SpawnUsingManager : public Scene
{
public:
    SpawnUsingManager();
    ~SpawnUsingManager();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

private:
    HBRUSH hBrush;

    //POINT rectPos = { (int)CENTER_X, (int)CENTER_Y };
    Rect* rect;

    int speed = 10;
};


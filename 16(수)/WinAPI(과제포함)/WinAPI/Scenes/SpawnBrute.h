#pragma once

class SpawnBrute : public Scene
{
public:
    SpawnBrute();
    ~SpawnBrute();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

private:
    HBRUSH hBrush;

    //POINT rectPos = { (int)CENTER_X, (int)CENTER_Y };
    Rect* rect;

    int speed = 10;
};


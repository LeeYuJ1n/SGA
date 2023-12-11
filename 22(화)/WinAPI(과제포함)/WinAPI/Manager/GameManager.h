#pragma once

class GameManager : public Singleton<GameManager>
{
private:
    friend class Singleton;

    GameManager();
    ~GameManager();

public:
    void Init(HWND hWnd);

    void Update();
    void Render();

    HWND GetHWND() { return hWnd; }

private:
    static GameManager* instance;

    Scene* scene;

    HWND hWnd = nullptr;
    HDC hdc = nullptr;

    HDC hBackDC = nullptr;
    HBITMAP hBackBitmap = nullptr;
};
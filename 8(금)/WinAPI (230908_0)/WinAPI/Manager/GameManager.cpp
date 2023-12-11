#include "Framework.h"

#include "Scenes/_SampleScene/SampleScene.h"
#include "Scenes/_PixelScene/PixelScene.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()    
{    
    Init();

    Timer::Get()->SetLockFPS(60);

    //scene = new SampleScene();
    scene = new PixelScene();
}

GameManager::~GameManager()
{
    delete scene;

    Timer::Delete();
    Keyboard::Delete();
    Texture::Delete();
}

void GameManager::Init()
{
    hdc = GetDC(hWnd);

    hBackDC = CreateCompatibleDC(hdc);
    hBackBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
    SelectObject(hBackDC, hBackBitmap);    

    Timer::Get();
    Keyboard::Get();

    SetBkMode(hBackDC, TRANSPARENT);
}

void GameManager::Update()
{
    if (KEY_DOWN(VK_TAB))
        Texture::SetDebug();

    Timer::Get()->Update();
    Keyboard::Get()->Update();

    scene->Update();
}

void GameManager::Render()
{
    PatBlt(hBackDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);

    //InvalidateRect(hWnd, nullptr, false);
    scene->Render(hBackDC);

    Timer::Get()->Render(hBackDC);

    BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
        hBackDC, 0, 0, SRCCOPY);
}

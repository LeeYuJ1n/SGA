#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/SpawnBrute.h"
#include "Scenes/SpawnUsingManager.h"
#include "Scenes/SpawnCircleScene.h"
#include "Scenes/BitmapScene.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()    
{    
    // scene = new TutorialScene();
    // scene = new SpawnBrute();
    // scene = new SpawnUsingManager();
    // scene = new SpawnCircleScene();
    scene = new BitmapScene();
}

GameManager::~GameManager()
{
    delete scene;

    Timer::Delete();
    Keyboard::Delete();
}

void GameManager::Init(HWND hWnd)
{
    this->hWnd = hWnd;
    hdc = GetDC(hWnd);

    hBackDC = CreateCompatibleDC(hdc);
    hBackBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
    SelectObject(hBackDC, hBackBitmap);    

    Timer::Get();
    Keyboard::Get();
}

void GameManager::Update()
{
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

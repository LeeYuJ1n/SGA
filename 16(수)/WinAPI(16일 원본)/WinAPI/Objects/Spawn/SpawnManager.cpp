#include "Framework.h"

SpawnManager::SpawnManager()
{
    spawnObjects.resize(POOL_SIZE);
    for (SpawnObject*& spawnObject : spawnObjects)
    {
        spawnObject = new SpawnObject();
    }
}

SpawnManager::~SpawnManager()
{
    for (SpawnObject* spawnObject : spawnObjects)
        delete spawnObject;
}

void SpawnManager::Update()
{
    if(KEY_DOWN(VK_LBUTTON))
    {
        for (SpawnObject* spawnObjecct : spawnObjects)
        {
            if (!spawnObjecct->Active())
            {
                spawnObjecct->Spawn();
                playTime = 0.0f;
                break;
            }
        }
    }

    for (SpawnObject* spawnObjecct : spawnObjects)
    {
        spawnObjecct->Update();
    }
}

void SpawnManager::Render(HDC hdc)
{
    for (SpawnObject* spawnObjecct : spawnObjects)
    {
        spawnObjecct->Render(hdc);
    }

    wstring scoreText = L"Score : " + to_wstring(score);
    TextOut(hdc, (int)CENTER_X, 0, scoreText.c_str(),
        (int)scoreText.size());
}

void SpawnManager::DestoryObject(Vector2 point)
{
    for (SpawnObject* spawnObject : spawnObjects)
    {
        if (spawnObject->IsCollision(point))
        {
            spawnObject->Destroy();
            score++;
            return;
        }
    }
}

void SpawnManager::DestoryObject(Rect* rect)
{
    for (SpawnObject* spawnObject : spawnObjects)
    {
        if (spawnObject->IsCollision(rect))
        {
            spawnObject->Destroy();
            score++;
            return;
        }
    }
}

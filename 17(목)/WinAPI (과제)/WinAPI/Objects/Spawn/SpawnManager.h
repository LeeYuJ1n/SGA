#pragma once
#include <Objects/Bullet1.h>

class SpawnManager : public Singleton<SpawnManager>
{
private:
    const UINT POOL_SIZE = 50;
    const float SPAWN_TIME = 1.0f;

private:
    friend class Singleton;

    SpawnManager();
    ~SpawnManager();

public:
    void Update();
    void Render(HDC hdc);

    void DestoryObject(Vector2 point);
    void DestoryObject(Rect* rect);
    void DestoryObject(Bullet1* bullet);

public:
    vector<SpawnObject*> spawnObjects;

    float playTime = 0.0f;

    UINT score = 0;
};
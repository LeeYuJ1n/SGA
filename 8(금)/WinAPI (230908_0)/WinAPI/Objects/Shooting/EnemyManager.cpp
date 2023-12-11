#include "Framework.h"

EnemyManager::EnemyManager()
{
    CreateObjects("Enemy", 50);
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
    playTime += DELTA;

    if (playTime >= SPAWN_TIME)
    {
        Enemy* enemy = (Enemy*)Pop("Enemy");
        enemy->Spawn();

        playTime = 0.0f;
    }

    PoolingManager::Update();
}

void EnemyManager::CreateObjects(string key, UINT poolSize)
{
    vector<GameObject*> enemies(poolSize);

    for (GameObject*& enemy : enemies)
    {
        enemy = new Enemy();
    }

    totalObjects[key] = enemies;
}

Enemy* EnemyManager::Collision(const GameObject* object)
{
    vector<GameObject*> enemies = totalObjects["Enemy"];

    for (GameObject* enemy : enemies)
    {
        if (enemy->IsCollision(object))
        {
            return (Enemy*)enemy;
        }
    }

    return nullptr;
}

void EnemyManager::SetTarget(GameObject* target)
{
    vector<GameObject*> enemies = totalObjects["Enemy"];

    for (GameObject* enemy : enemies)
    {
        ((Enemy*)enemy)->SetTarget(target);
    }
}

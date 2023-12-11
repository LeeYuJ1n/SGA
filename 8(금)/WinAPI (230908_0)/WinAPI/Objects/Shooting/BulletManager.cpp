#include "Framework.h"

BulletManager::BulletManager()
{
    CreateObjects("PlayerBullet", 50);
    CreateObjects("EnemyBullet", 50);
}

BulletManager::~BulletManager()
{
}

void BulletManager::CreateObjects(string key, UINT poolSize)
{
    vector<GameObject*> bullets(poolSize);

    for (GameObject*& bullet : bullets)
    {
        bullet = new Bullet();   
        bullet->tag = key;
    }

    totalObjects[key] = bullets;
}

void BulletManager::Fire(const Vector2& pos)
{
    Bullet* bullet = (Bullet*)Pop("PlayerBullet");
    bullet->Fire(pos);
}

void BulletManager::Fire(const Vector2& pos, const Vector2& direction)
{
    Bullet* bullet = (Bullet*)Pop("EnemyBullet");
    bullet->Fire(pos, direction);
}

bool BulletManager::Collision(const GameObject* object, string key)
{
    vector<GameObject*> bullets = totalObjects[key];

    for (GameObject* bullet : bullets)
    {
        if (bullet->IsCollision(object))
        {
            bullet->isActive = false;
            return true;
        }
    }

    return false;
}

void BulletManager::CollisionBullet(string key1, string key2)
{
    vector<GameObject*> bullets = totalObjects[key1];

    for (GameObject* bullet : bullets)
    {
        if (Collision(bullet, key2))
        {
            bullet->isActive = false;
            return;
        }
    }
}

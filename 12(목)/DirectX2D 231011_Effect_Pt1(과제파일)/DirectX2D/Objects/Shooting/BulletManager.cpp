#include "Framework.h"

BulletManager::BulletManager()
{
    bullets.resize(30);
    enemyBullets.resize(30);

    for (Bullet*& bullet : bullets)
        bullet = new Bullet();

    for (Bullet*& bulletE : enemyBullets)
        bulletE = new Bullet(L"Textures/Shooting/triEnemy.png"); //Ŀ���� ���� �̸����� �� �Ѿ� �����ϱ�
}

BulletManager::~BulletManager()
{
    for (Bullet* bullet : bullets)
        delete bullet;

    for (Bullet* bulletE : enemyBullets)
        delete bulletE;

    //�Ҹ� �Ŵ����� ���� �� ��� ���� ��� �Ѿ��� �ϰ�����
    for (vector<Bullet*>* v : totalBullets)
    {
        for (Bullet* b : *v)
        {
            delete b;
        }
    }
}

void BulletManager::Update()
{
    // WinAPI���� ���� �ڵ带 �ٽ� ���� : �ȿ� ���� �Ҹ��� DX������ �ٲ� ��

    for (Bullet* bullet : bullets)
        bullet->Update();

    for (Bullet* bulletE : enemyBullets)
        bulletE->Update();


    for (vector<Bullet*>* v : totalBullets)
    {
        for (Bullet* b : *v)
        {
            //�̷��� ��� ���� ��� �Ѿ��� ������ �ʿ䰡 �ִٸ� ���⼭ ��� �ۼ�
        }
    }
}

void BulletManager::Render()
{
    for (Bullet* bullet : bullets)
        bullet->Render();

    for (Bullet* bulletE : enemyBullets)
        bulletE->Render();
}

void BulletManager::Fire(Vector2 pos, Vector2 direction)
{
    for (Bullet* bullet : bullets)
    {
        if (!bullet->Active())
        {
            bullet->Fire(pos, direction);
            return;
        }
    }
}

void BulletManager::EnemyFire(Vector2 pos, Vector2 direction)
{
    //for (Bullet* bulletE : enemyBullets)
    for (Bullet* bulletE : *sceneBullets)
    {
        if (!bulletE->Active())
        {
            bulletE->Fire(pos, direction);
            return;
        }
    }
}

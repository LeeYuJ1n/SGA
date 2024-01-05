#include "Framework.h"

BulletManager::BulletManager()
{
    bullets.resize(30);
    enemyBullets.resize(30);

    for (Bullet*& bullet : bullets)
        bullet = new Bullet();

    for (Bullet*& bulletE : enemyBullets)
        bulletE = new Bullet(L"Textures/Shooting/triEnemy.png"); //커스텀 파일 이름으로 적 총알 생성하기
}

BulletManager::~BulletManager()
{
    for (Bullet* bullet : bullets)
        delete bullet;

    for (Bullet* bulletE : enemyBullets)
        delete bulletE;

    //불릿 매니저가 죽을 때 모든 적의 모든 총알을 일괄삭제
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
    // WinAPI에서 쓰던 코드를 다시 적용 : 안에 들어가는 불릿이 DX용으로 바뀔 뿐

    for (Bullet* bullet : bullets)
        bullet->Update();

    for (Bullet* bulletE : enemyBullets)
        bulletE->Update();


    for (vector<Bullet*>* v : totalBullets)
    {
        for (Bullet* b : *v)
        {
            //미래에 모든 적의 모든 총알을 관리할 필요가 있다면 여기서 기능 작성
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

#pragma once

class BulletManager : public Singleton<BulletManager>
{
private:
    friend class Singleton;

    BulletManager();
    ~BulletManager();

public:
    void Update();
    void Render();

    void Fire(Vector2 pos, Vector2 direction);
    void EnemyFire(Vector2 pos, Vector2 direction); //적이 쓰기 위한 사격 함수

    vector<Bullet*> GetBullets() { return bullets; }
    vector<Bullet*> GetEnemybullet() { return enemyBullets; } //적의 총알 벡터 반환
    vector<Bullet*> GetSceneBullet() { return *sceneBullets; }

    void RegisterSceneBullet(vector<Bullet*>* sceneBullets)
        { this->sceneBullets = sceneBullets; }

    void RegisterEnemyBullet(vector<Bullet*>* enemyBullets)
        { totalBullets.emplace_back(enemyBullets); }

private:
    vector<Bullet*> bullets;

    //적이 쏘기 위한 총알도 만들자
    vector<Bullet*> enemyBullets;

    //지금 당장은 필요가 없지만 명목상 존재하는 총알 변수
    vector<Bullet*>* sceneBullets;

    //적의 총알을 모두 가져오기 위한 통합 관리용 변수 (이중 벡터)
    vector<vector<Bullet*>*> totalBullets;
};
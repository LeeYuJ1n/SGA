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
    void EnemyFire(Vector2 pos, Vector2 direction); //���� ���� ���� ��� �Լ�

    vector<Bullet*> GetBullets() { return bullets; }
    vector<Bullet*> GetEnemybullet() { return enemyBullets; } //���� �Ѿ� ���� ��ȯ
    vector<Bullet*> GetSceneBullet() { return *sceneBullets; }

    void RegisterSceneBullet(vector<Bullet*>* sceneBullets)
        { this->sceneBullets = sceneBullets; }

    void RegisterEnemyBullet(vector<Bullet*>* enemyBullets)
        { totalBullets.emplace_back(enemyBullets); }

private:
    vector<Bullet*> bullets;

    //���� ��� ���� �Ѿ˵� ������
    vector<Bullet*> enemyBullets;

    //���� ������ �ʿ䰡 ������ ���� �����ϴ� �Ѿ� ����
    vector<Bullet*>* sceneBullets;

    //���� �Ѿ��� ��� �������� ���� ���� ������ ���� (���� ����)
    vector<vector<Bullet*>*> totalBullets;
};
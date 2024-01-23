#pragma once

class Plane;

class EnemyManager : public Singleton<EnemyManager>
{
private:
    friend class Singleton;

    EnemyManager();
    ~EnemyManager();

public:
    void Update();
    void Render();

    vector<Enemy*> GetEnemies() { return enemies; }

    //�� �Ŵ����� �÷��̾�� ������ ���, ǥ�� ���� �ޱ�
    void SetTarget(Plane* target) { this->target = target; }

private:

    int numberOfEnmemies = 3;

    vector<Enemy*> enemies;

    //�� �Ŵ����� �÷��̾�� ������ ���
    Plane* target = nullptr; // target : �� ���忡�� �÷��̾�� ǥ���̴ϱ�
};


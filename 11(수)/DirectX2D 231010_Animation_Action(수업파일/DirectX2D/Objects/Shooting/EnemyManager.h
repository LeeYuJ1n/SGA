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

    //적 매니저가 플레이어에게 개입할 경우, 표적 정보 받기
    void SetTarget(Plane* target) { this->target = target; }

private:

    int numberOfEnmemies = 3;

    vector<Enemy*> enemies;

    //적 매니저가 플레이어에게 개입할 경우
    Plane* target = nullptr; // target : 적 입장에서 플레이어는 표적이니까
};


#pragma once

class EnemyManager : public PoolingManager, public Singleton<EnemyManager>
{
private:
    const float SPAWN_TIME = 1.0f;

public:
    EnemyManager();
    ~EnemyManager();

    virtual void Update() override;

    virtual void CreateObjects(string key, UINT poolSize) override;

    Enemy* Collision(const GameObject* object);

    void SetTarget(GameObject* target);

private:
    float playTime = 0.0f;
};
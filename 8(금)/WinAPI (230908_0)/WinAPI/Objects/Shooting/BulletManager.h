#pragma once
#include "Scenes/_SampleScene/Landscape.h"

class BulletManager : public PoolingManager, public Singleton<BulletManager>
{
public:
    BulletManager();
    ~BulletManager();

    virtual void CreateObjects(string key, UINT poolSize) override;

    void Fire(const Vector2& pos);
    void Fire(const Vector2& pos, const Vector2& direction);

    bool Collision(const GameObject* object, string key);

    void CollisionBullet(string key1, string key2);

    // ����� �ȼ��� �ε�ģ �Ѿ��� �����Ѵٸ�, �� �Ѿ��� ����
    // cpp�� ���� ������ ������� �ۼ�
    GameObject* CollisionLand(Landscape* land)
    {
        // �Ѿ� ������ ��� �ʿ��ϴ�
        vector<GameObject*> bullets = totalObjects["EnemyBullet"];

        for (GameObject* bullet : bullets)
        {
            if (!bullet->isActive) continue;
            
            float height = land->GetPixelHeight(bullet->pos, RGB(0, 178, 255));

            if (bullet->pos.y > height) // �� �Ѿ��� �ٴں��� ���� = �Ѿ��� �ٴ��� �վ���
            {
                bullet->isActive = false; // �ε�ģ �Ѿ��� ����
                return bullet;            // �Ѿ� ��ȯ
            }
        }

        // ������� ���� ����� �ε�ģ �Ѿ��� ���ų�, �̹� �� �ε��ļ� active�� �ƴϴ�
        return nullptr;
    }
};
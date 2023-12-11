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

    // 배경의 픽셀과 부딪친 총알이 존재한다면, 그 총알을 도출
    // cpp로 가야 하지만 헤더에서 작성
    GameObject* CollisionLand(Landscape* land)
    {
        // 총알 정보가 모두 필요하다
        vector<GameObject*> bullets = totalObjects["EnemyBullet"];

        for (GameObject* bullet : bullets)
        {
            if (!bullet->isActive) continue;
            
            float height = land->GetPixelHeight(bullet->pos, RGB(0, 178, 255));

            if (bullet->pos.y > height) // ← 총알이 바닥보다 낮다 = 총알이 바닥을 뚫었다
            {
                bullet->isActive = false; // 부딪친 총알을 끄고
                return bullet;            // 총알 반환
            }
        }

        // 여기까지 오면 현재는 부딪친 총알이 없거나, 이미 다 부딪쳐서 active가 아니다
        return nullptr;
    }
};
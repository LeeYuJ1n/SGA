#include "Framework.h"

EnemyManager::EnemyManager()
{
    enemies.resize(numberOfEnmemies);

    for (Enemy*& enemy : enemies)
    {
        enemy = new Enemy();
        enemy->Pos() = { Random(0.0f, (float)WIN_WIDTH),
                         Random(0.0f, (float)WIN_HEIGHT) };
    }
}

EnemyManager::~EnemyManager()
{
    for (Enemy* enemy : enemies)
        delete enemy;
}

void EnemyManager::Update()
{
    // 플레이어 vs 총알 코드 구현의 가장 단순한 형태 :
    // -> 총알이 만들어지는 곳에서 바로 충돌도 구현

    //for (Bullet* bullet : BulletManager::Get()->GetEnemybullet())
    //{
    //    Vector2 overlap = { 0, 0 };
    //    if (bullet->GetCollider()->IsRectCollision((RectCollider*)target->GetCollider(), &overlap))
    //    {
    //        //원래 할 일 : 플레이어로부터 해로운 일이 벌어질 함수를 호출
    //        //            -> 플레이어가 죽거나 해로워지는 함수를 밖에 노출시켜야 한다는 뜻도 된다
    //        //            -> 설계자의 취향에 따라서는 그런 방식을 선호하지 않을 수도 있다
    //
    //        // 그렇다면? -> 그냥 이 코드를 플레이어한테 적용해도 되지 않을까?
    //
    //        //지금 할 일 : 총알 없어지기
    //        bullet->Active() = false;
    //        bullet->GetCollider()->Active() = false;
    //    }
    //}


    for (Enemy* enemy : enemies)
    {
        //업데이트를 하기 전에 충돌 검사와 제어를 한다
        for (Bullet* bullet : BulletManager::Get()->GetBullets())
        {
            //충돌했으면
            if (enemy->Collision( (RectCollider*)bullet->GetCollider() ))
            {
                //적은 한 번 죽고 다른 곳에서 부활
                enemy->Respawn(); //함수 호출로 변경

                //총알 비활성화
                bullet->Active() = false;
                bullet->GetCollider()->Active() = false; // 임시 처치로 콜라이더와 불릿 활성화 여부 동기화
            }
        }
        
        // 여기서 플레이어와 충돌했을 때 코드를 제어해도 된다
        if (target != nullptr &&
            enemy->Collision((RectCollider*)target->GetCollider()))
        {
            // 기본 : 이 자리에는 플레이어에게 해로운 기능이 들어옵니다.

            // 테스트용 : 적이 리스폰합니다.
            enemy->Respawn();
        }


        // 사격도 호출
        // 원래 : '사격 관제'라는 함수를 만들고, 그 함수를 부르고,
        //        다시 거기서 플레이어의 표적 정보를 받았어야... 하는데
        //        지금 코드에 표적의 변수 정보가 있으므로 바로 써도 되겠습니다
        enemy->Fire(target->GlobalPos());

        //여기까지 오면 부딪친 일이 있는 사각형은 이미 통제가 끝났을 테고
        // 충돌이 안 된 적들만 있을 것

        // 그 적들을 업데이트
        enemy->Update();
    }
}

void EnemyManager::Render()
{
    for (Enemy* enemy : enemies)
        enemy->Render();
}
#include "Framework.h"

Enemy::Enemy() : Quad(L"Textures/Shooting/rectEnemy.png")
{
    tag = "Enemy";
    
    collider = new RectCollider(texture->GetSize());
    collider->SetParent(this);

    bullets.resize(16); // <- 16진수로 10H

    for (Bullet*& bullet : bullets)
        bullet = new Bullet(L"Textures/Shooting/triEnemy.png");

    BulletManager::Get()->RegisterEnemyBullet(&bullets); //전체관리용 매니저에 등록
}

Enemy::~Enemy()
{
    delete collider;

    //삭제는 매니저가 일괄통합관리로...
    //for (Bullet* bullet : bullets)
    //    delete bullet;
}

void Enemy::Update()
{
    //총알을 받아서 반복문으로 검사
    //for (Bullet* bullet : BulletManager::Get()->GetBullets())
    //{
    //    //총알이 부딪칠 경우 충돌 연산을 수행하는 함수 호출
    //    Collision((RectCollider*)bullet->GetCollider()); // 인터페이스로 반환된 총알의 실제 콜라이더를 사각형으로 형변환
    //    // (단 위와 같은 형변환은 결국 실제 대상이 정말로 사각형일 때 의미가 있다)
    //}

    GameObject::Update();
    collider->Update();

    //기본적으로는 자기 총알은 자기가 관리
    for (Bullet* bullet : bullets)
        bullet->Update();
}

void Enemy::Render()
{
    Quad::Render();
    collider->Render();

    for (Bullet* bullet : bullets)
        bullet->Render();
}

bool Enemy::Collision(RectCollider* target)
{
    Vector2 overlap = { 0, 0 };
    return collider->IsRectCollision(target, &overlap);
}

void Enemy::Respawn()
{
    localPosition = { Random(0.0f, (float)WIN_WIDTH), Random(0.0f, (float)WIN_HEIGHT) };
}

//자동이라 할지라도 "사격"이니만큼 외부에서 조건에 따라 호출해주면 더 좋고
//매개변수도 있으니 'target'을 지정을 누가 해주면 더 적절하게 쓸 수 있다
// -> 에너미 매니저에서 쓰면 좋다
void Enemy::Fire(Vector2 target)
{
    if (!isActive) return; //비활성화 시 실행하지 않음 (보험용)

    cooldown -= DELTA; //쿨다운을 시간에 맞추어 내리기

    if (cooldown <= 0) //쿨다운이 다 차면
    {
        cooldown = interval; // 쿨다운을 간격 설정 수치로 리셋

        Vector2 direction = (target - localPosition).GetNormalized(); // 방향 구하기 (정규화 필수)
        //BulletManager::Get()->Fire(localPosition, direction); // <-이 코드를 쓰면 자기 총알에 자기가 맞는다

        //자기가 쏜 총알에 자기가 안 맞도록 하는 여러 방법이 있다
        // - 처음부터 자기가 안 맞을 곳에서 총알이 나가게 한다 (물리엔진이 중요하게 쓰이는 게임에서 자주 취하는 조치)
        // - 총알 하나하나에 ID 혹은 비슷한 고유정보를 줘서 총을 쏜 당사자에게 영향을 주지 못하게 한다 (잘못하면 자폭 내기 좋은 게임에서 자주 취하는 조치)
        // - 그냥 다른 총알을 쏘게 한다 (맞으면 내가 죽는 총알과 맞으면 표적이 죽는 총을 둘을 구분해서 쏜다 : 2D 슈터 게임에서 자주 쓴다)
        //   + 더 많은 방법 있음

        // 지금은 위 셋 중 세 번째 방법을 사용한다

        //BulletManager::Get()->EnemyFire(localPosition, direction); // 불릿매니저에 등록된 전체용 변수를 쓰는 경우

        //그냥 자기 총알에서 직접 하나 골라 쏘기
        for (Bullet* bullet : bullets)
        {
            if (!bullet->Active())
            {
                bullet->Fire(localPosition, direction);
                return;
            }
        }
    }
}
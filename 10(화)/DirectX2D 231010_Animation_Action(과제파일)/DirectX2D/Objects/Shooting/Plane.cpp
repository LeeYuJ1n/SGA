#include "Framework.h"

Plane::Plane() : Quad(L"Textures/Shooting/airplane.png")
{
    //그림을 가진 쿼드를 가진 독자 클래스가 만들어질 것
    //기본적으로 "존재"는 확보
    
    //오늘은 총알이 만들어질 테니 총알에 대비한 코드 몇 줄 더

    tag = "Airplane"; //비행기용 식별명 (태그) 부여
    BulletManager::Get(); // 싱글턴 호출만

    // 터렛을 플레인에서 만들기
    turret = new Quad(L"Textures/Shooting/player.png");
    turret->SetParent(this);
    turret->Pos() = { 100, 0 }; //상대 위치 조정

    // 콜라이더 생성
    collider = new RectCollider(texture->GetSize());
    collider->SetParent(this);
}

Plane::~Plane()
{
    //BulletManager::Delete(); // 불릿매니저 삭제 (지금은 어차피 얘 말곤 안 쓰니까)
                             // 적도 등장하고 총을 쏠 경우, 이 코드는 씬으로 가는 편이 좋을 수도

    //만든 변수도 삭제
    delete collider;
    delete turret;
}

void Plane::Update()
{
    //움직이는 함수 호출하기
    Move();
    Rotate();
    Fire();
    //상황에 따른 대응 코드 호출하기
    Crash();

    //자기 (부모) 업데이트
    GameObject::Update();
    collider->Update();

    //총알 업데이트
    //BulletManager::Get()->Update();

    turret->Update();
}

void Plane::Render()
{
    //자기 렌더
    Quad::Render();
    collider->Render();

    //총알 렌더
    //BulletManager::Get()->Render();
    turret->Render();
}

void Plane::Move()
{
    //비행기 입장에서 전후좌우로 움직이기
    if (KEY_PRESS('A')) localPosition += Up() * DELTA * 200.0f;
    if (KEY_PRESS('D')) localPosition -= Up() * DELTA * 200.0f;
    if (KEY_PRESS('W')) localPosition += Right() * DELTA * 200.0f;
    if (KEY_PRESS('S')) localPosition -= Right() * DELTA * 200.0f;
}

void Plane::Rotate()
{
    // 회전하기
    // (현 좌표계 기준) z축으로 회전을 해서 롤링을 수행하면
    // -> 비행기(그림이) 회전

    if (KEY_PRESS('Q')) localRotation.z += DELTA * 10.0f;
    if (KEY_PRESS('E')) localRotation.z -= DELTA * 10.0f;

    // 포탑 회전 (의도한 대로 안 되면 임시로 다시 재우기)
    if (KEY_PRESS('Z')) turret->Rot().z += DELTA * 5.0f;
    if (KEY_PRESS('C')) turret->Rot().z -= DELTA * 5.0f;
}

void Plane::Fire()
{
    //만든 불릿 매니저에서 함수를 호출

    // 포탑을 바로 적용 가능 (포탑의 존재 의의는 결국 총알 나갈 위치를 재지정하는 게 목적이니까)
    // 게임이라면, 총을 쏘는 건 캐릭터고, 총이란 물건은 그냥 총알 나갈 장소를 지정하는 것이라고 생각할 수도
    if (KEY_DOWN(VK_LBUTTON))
    {
        //BulletManager::Get()->Fire(localPosition, Right()); // 포탑이 없는 경우
        //BulletManager::Get()->Fire(turret->GlobalPos(), Right()); // 포탑이 있고, 비행기 방향으로 쏠 때
        BulletManager::Get()->Fire(turret->GlobalPos(), turret->Right()); //포탑이 있고 포탑의 오른쪽 방향으로 쏠 때

        // 총을 쏠 때도 봉크!
        Audio::Get()->Play("Bonk");
    }
}

void Plane::Crash()
{
    // 적 중에 누구라도 부딪치면 일어날 일이니까

    //for (Enemy* enemy : EnemyManager::Get()->GetEnemies())
    //{
    //    if (enemy->Collision((RectCollider*)collider))
    //    {
    //        //적과 플레이어가 부딪친 경우
    //        // 플레이어가 죽는 경우 여기에 코드 작성
    //
    //        // 테스트: 적이 죽었다가 다른 곳에서 다시 생긴다
    //        //        == 위치이동
    //
    //        enemy->Respawn();
    //    }
    //}

    //총알 충돌

    // 아래 코드는 이대로는 쓸 수 없다.
    // 이유 : 다른 인스턴스와 본 조건문이 동시에 호출이 되고 있어서 + 한 변수에 여러 인스턴스가 호출을 시도해서
    //        -> 주요 데이터가 싱글턴에 있어서 그렇다.
    //for (Bullet* bullet : BulletManager::Get()->GetSceneBullet())
    //{
    //    Vector2 overlap = { 0, 0 };
    //    if (collider->IsRectCollision((RectCollider*)bullet->GetCollider(), &overlap))
    //    {
    //        bullet->Active() = false;
    //        bullet->GetCollider()->Active() = false;
    //    }
    //}

    // 그러면 지금의 이 문제를 어떻게 해결할 수 있을까?
    // -> 대부분의 다른 문제들처럼 원인이 없어지면 제일 좋다
    // -> 적 총알이(본체가) 싱글턴에 없으면 되겠네?

    // -> 적 총알이 싱글턴에 없다면, 어디로?
    // -> 후보지는 여러 군데가 있는데, 그 중 첫 번째는 바로 전체 씬 그 자체 (TextureScene.h)
    // -> 씬에 변수를 직접 만들어서, 호출이 그때그때 다른 경로(호출자->싱글턴)로 오는 게 아니라
    // -> 씬이라는 최종 목적지에서 다 걸러져서 차례대로 호출되어 가게 만들면
    // -> 튀는 문제를 유의미하게 줄일 수도 있고, 실행이 안되는 문제도 해결이 된다

    // -> 씬에서 각 개체의 결속을 관리한다는 약점이 있다
    // -> 씬이 바뀔 경우, 거기에도 똑같은 변수를 또 만들어줘야 한다는 뜻 (안 그러면 씬 바뀔 때 적은 총알이 없다)

    // -> 위의 약점을 극복하면서, 문제도 해결하는 다른 후보지가 하나 더 있다
    // -> 바로 적 자체

    // 오늘 코딩이 알려주는 사실 : 코드는 논리도 중요하고, 호출할 때의 상황도 중요하다
    //                           호출이 엉키면 맞는 코드도 실행이 안 되는 틀린 코드로 바뀐다
    //                           특히 멀티코어 멀티스레드 환경에서 이런 부분은 주의

    // 그래서, 여러 곳에서 호출하면 안 되는 데이터가 있다면, 되도록 실제 접근자만 접근할 수 있도록
    // 상속이나 멤버 변수 관계를 설정해주면, 연산은 느려진다. 대신에 원하지 않았던 결과는 유의미하게 줄일 수 있다.
    // -> 대표적인 것이 적의 총알, 적의 기술, 적의 필살기.... 등

    // 그런데, 각 개체가 자기 데이터를 따로 가져야 된다면, ~~~ 매니저는 그럼 왜 있냐????

    // 그래도 매니저가 있으면 좋은 이유 둘 :
    // 1. 외부 실행이 편해진다 (이 프레임워크의 게임매니저) -> 한 번 만들면 이전 단계는 더 신경쓰지 않을 수 있다
    // 2. 그 모든 것에도 불구하고 완전 통합 관리 함수가 필요할 수 있기 때문에 (예 : 일괄삭제, 리셋...)

    for (Enemy* enemy : EnemyManager::Get()->GetEnemies())
    {
        for (Bullet* bullet : enemy->GetBullets())
        {
            Vector2 overlap = { 0, 0 };
            if (collider->IsRectCollision((RectCollider*)bullet->GetCollider(), &overlap))
            {
                // 충돌이 나면 봉크!
                // Audio::Get()->Play("Bonk"); // 출력은 좋다 -> 그런데 소리가 너무 다다다닥

                //총알이 부딪치면 사라진다
                //bullet->Active() = false;
                //bullet->GetCollider()->Active() = false;

                // 총알이 반사되는 것을 호출한다
                bullet->ReflectByVector( (RectCollider*)collider, &overlap);
                //bullet->Reverse();
            }
        }
    }
}
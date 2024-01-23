#pragma once

// 적(혹은 표적) : 플레이어와 마찬가지로 텍스처를 받는 트랜스폼 객체

class Enemy : public Quad
{
public:
    //DX, 그것도 C++, 그것도 상속받음으로써 존재하는 모든 객체의 존재사명 4종
    Enemy();
    ~Enemy();
    void Update();
    void Render();

    //두 충돌 영역이(충돌체가) 부딪쳤을 때, 최소 한 쪽에서는 어떤 일이 일어날지
    // 연산이 정해져 있어야 한다
    // 이번에는 그 역할을 이 "적" 클래스가 맡도록 한다
    //void Collision(RectCollider* target); // 매개변수를 조금 더 구체적으로도 지정 가능
    bool Collision(RectCollider* target);

    // 죽고 다시 나오기 (=위치 이동)
    void Respawn();

    // 적도 총을 쏜다???
    // 준비물 : 총을 쏜다는 행위, 총을 쏠 위치 (표적), NPC이기 때문에 필요한... "언제 쏠 건가"
    void Fire(Vector2 target); //총 쏘는 행동 (그리고 매개변수로 쏠 위치)

    vector<Bullet*> GetBullets() { return bullets; }

private:
    //충돌 영역(충돌체)
    Collider* collider;

    // 언제 쏠 건가를 정하는 두 변수
    float cooldown = 1; // 사전 쿨다운 설정
    float interval = 1; // 공격 간의 간격 (지금은 2초마다 규칙적으로 총을 쏘게 한다는 의미)


    //전용 총알 만들기
    vector<Bullet*> bullets;
    //총알의 기본 관리는 주인이 다 하지만, 그래도 전체관리가 필요할 경우를 대비해
    //매니저에 등록해두면 좋기는 하다
};


#pragma once
class Robot
{
private:
    //enum class STATE // <- 이 경우 클래스명 "STATE" 사용이 강제
                       //    단점 : 타자가 귀찮고 참조 속도도 (아주 아주 조금) 느리다
                       //  **장점** : enum 값이 중복될 때, 반드시 의도한 값을 호출 가능
    enum State
    {
        STAND_UP,
        WALK,
        RUN,
        HIT,
        DYING,
        // 상태명의 기준 : fbx의 클립명 (첫 글자 대문자, 나머지 소문자. 예: "Dying")
    };

public:
    Robot(Transform* transform); // 원하면 인스턴싱 가능
    ~Robot();

    void Update();
    void Render();

    SphereCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

private:

    // 모델을 안에서 추가할 거라면 여기에 멤버 변수 추가할 것
    // (밖에서 만들면 그럴 필요 없음!)

    Transform* transform;
    SphereCollider* collider;

    float moveSpeed = 30;

    Vector3 velocity; // 점프에 써도 되지만 아니어도 되는 범용 변수
                      // 움직일 때, 아닐 때 등등에 전부 사용 가능
    

};
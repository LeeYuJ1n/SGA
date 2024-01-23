#pragma once

class Bullet : public Quad
{
public:
    Bullet();
    Bullet(wstring file); // 스트링 문자열로 파일 이름이 들어올 경우, 해당 파일에 해당하는 텍스처를 커스텀 생성하게
    ~Bullet();

    void Update();
    void Render();

    //위 함수 : 개체용 함수 4종

    //총알을 위한 함수
    void Fire(Vector2 pos, Vector2 direction);

    Collider* GetCollider() { return collider; }

    void ReflectByVector(RectCollider* obj, Vector2* overlap, float additionalForce = 0);
    // 사각형 반사 함수, 매개변수는 차례로 부딪친 사각형, 부딪쳤을 때의 모양(방향), 추가 힘
    // 마지막 매개변수인 추가 힘은 기본으로 0이라는 값을 주었기 때문에 호출 시 입력을 하지 않아도 된다

    void Reverse() { direction *= -1; }

private:

    //총알은 winAPI에서도 그랬던 것처럼 자기만의 추가 정보가 필요하다

    Vector2 direction;
    //고유 방향 : winAPI와는 조금 다르게, 실제 방향 못지 않게 "발사시 입력된 방향"을 저장하는 수단에 가깝다
    //           -> 실제 객체 방향은? 트랜스폼이 있으니까
    //           "발사시 입력된 방향"이 필요한 이유? - 쏘는 비행기의 방향이 어떨지 모르니까

    //총알 속도
    float speed = 200.0f;

    Collider* collider; // <- 선언은 콜라이더로 하고, 생성을 구체적
};


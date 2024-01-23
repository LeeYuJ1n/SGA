#include "Framework.h"

Bullet::Bullet() : Quad(L"Textures/Shooting/playerBullet2.png")
{
    tag = "Bullet";

    //총알이 만들어지면 제일 먼저 할 일

    //총알이 어디서 만들어질까? -> 지금 이 구조에선, 불릿매니저
    //불릿매니저는 언제 만들어질까? 언제 불릿을 만들까? -> 게임 시작하는 순간에
    //그 때, 총알이 "작동"을 하고 있으면? -> 의도하지 않은 결과

    //활성화 변수를 설정 (비활성)
    isActive = false;

    // 이런 활성화/비활성화는 게임에서 유용한 개체 통제 수단이 된다
    // -> 로딩은 했지만 눈에는 안 보이는 (다시 나타날 때 로딩이 필요 없는) 상태를 만들어낼 수 있다
    // -> 대부분의 게임 개발 프레임워크, 혹은 엔진에 실제로 이런 용도의 변수가 존재한다 -> 잘 찾고 호출해야 한다
    //    최소한 현재 지명도 있는 상용/프리 엔진에는 모두 이런 변수가 있다 (이름은 각각 다르다)
    //    언리얼, 유니티, 고도, 패스, 프로스트바이트, 게임브라이오(게임브리오).... 모두 다!

    //    간혹 없거나 못 찾을 수도 있지만... 그 때도 만들어서라도 쓰는 편이 좋다!


    // 콜라이더 생성 (여기서 렉트 콜라이더로 생성 : 인터페이스 사용)
    collider = new RectCollider(texture->GetSize()); //텍스처 크기로 속성 생성
    // 콜라이더의 위치는 언제나 자기 자신=총알의 위치여야 한다 (코드에서나 다르지 개념적으로 이 둘은 사실 하나다!)
    collider->SetParent(this); //콜라이더의 부모(결속된 트랜스폼)을 자기 자신(총알 자체)으로

    collider->Active() = false;

    // * 콜라이더의 활성화 관리 방법 1. 불릿의 활성화가 바뀔 때 일일이 찾아가서 바꿔준다
    //   -> 간단, 확실, 귀찮.    (방법 2는 Collider.cpp에서 확인)
}

// 지금은 적 총알 만드는 용도로 사용중
Bullet::Bullet(wstring file) : Quad(file) //파일 이름으로 총알 만들기
{
    tag      = "EnemyBullet"; // 나중에 태그도 바뀌어야 한다면 매개변수 하나 더 받으면 된다
    isActive = false;
    collider = new RectCollider(texture->GetSize());

    collider->SetParent(this);
    collider->Active() = false;

    localScale = { 0.3f, 0.3f };
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    // 총알은 만들어지고 나면 스스로 할 일 : "앞으로 나아가기"

    if (!isActive) return; //활성화가 안 된 경우 이 함수 바로 종료

    // 위치 설정 (시간마다 갱신)

    // 정석 : 트랜스폼에서 실제 정보를 가져와서 다시 피드백 연산을 수행
    // localPosition += { localRotation.x * DELTA * speed, localRotation.y * DELTA * speed };

    // 꼼수 : "저장용" 변수에도 어차피 같은 값이 들어갔는데, 굳이 트랜스폼까지 가서 자료를 또 가져올 필요가?
    localPosition += direction * DELTA * speed;

    //총알이 뷰포트(가시 영역=지금은 위도우)를 벗어나면 활성화가 꺼지게

    if (localPosition.x < 0 || localPosition.x > WIN_WIDTH)
        isActive = false;

    if (localPosition.y < 0 || localPosition.y > WIN_HEIGHT)
        isActive = false;

    // 총알 위치 갱신 끝

    // 게임오브젝트로서의 다른 부분도 갱신하면 된다
    GameObject::Update(); //부모의 동명 함수 호출

    //collider->UpdateWorld(); // <-실체를 위한 부가 요소로서 존재하기 때문에 UPDATE와는 형태가 다르다
    collider->Update(); //추가 함수 대응 Update 호출
}

void Bullet::Render()
{
    Quad::Render(); // 쿼드의 렌더 호출

    //현재 코드만 보면 어차피 부모 함수를 쓰는 거라 자식 함수 존재 의미 자체가 없긴 하다
    // 그런데도 굳이 자식에 동명 함수를 써서(오버라이드해서) 부모 함수를 직접 부르는 귀찮은 짓은 왜 하느냐?
    // -> 의도의 문제 (= "이 게임에 등장하는 모든 개체는 "업데이트와 렌더 함수가 있어야 한다!"는 의도를 표현)

    // 이런 비효율은 왜 필요하냐? -> 우리가 만드는 게 결국 게임이라서.
    // 1. 나중에 바뀔 수 있어야 한다 (그리고 그 바꿈을 수행하는 사람은 내가 아닐 수 있다)
    // 2. 보통은 여러 명이 만든다 (그리고 우리도 도중에 남이 만든 코드를 개선해야 할 수 있다)

    // 협력이 필요하고 유지보수가 필요한 앱이라면, 적절한 비효율도 오히려 필요하다


    // 콜라이더 렌더
    collider->Render();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
    // 발사!

    isActive      = true; //발사가 될 때, 활성화
    localPosition = pos; //위치

    this->direction = direction; // 매개변수를, this의 변수 안으로 할당

    // 이것이 this 포인터가 존재하는 이유 : 동명의 변수를 사용하면서도 서로를 구분하기 위해서
    // 이런 식으로 사용하는 this는 너무나도 중요해서... 포인터가 생략되는 후기 언어에서조차 this만큼은 남겨놓는다!
    // 파이썬, 자바, C#, 이들 언어를 쓰는 각종 엔진(유니티, 고도) + 심지어 언리얼도 포인터 일부는 생략할 수 있는데 this만큼은 절대 안 지운다

    //트랜스폼 정보에도 매개변수 값을 반영
    localRotation.z = direction.Angle(); // 벡터의 각도를 내어서 z축 회전 정보에 주도록 한다
}

void Bullet::ReflectByVector(RectCollider* obj, Vector2* overlap, float additionalForce)
{
    
    //총알이 실제로 어느 벡터변에 부딪쳤는지 알기 위한 계산하기

    Vector2 floor; //바닥

    //총알이 부딪쳤을 때 사각형의 어느 쪽에 부딪쳤는지를 방향에 따라 판별
    // 위에서 부딪쳤으면 (비스듬하더라도) 사각형의 "위"에 해당하는 벡터가 반사면일 테고
    // 옆에서 부딪쳤으면 "양 옆 중 한 곳"에 해당하는 벡터가 반사면일 테다

    if (overlap->x > overlap->y) // 수직 충돌 (=접촉면의 모양이 가로로 납작 = 위나 아래에서 부딪쳤다)
    {
        // 충돌이 수직이니 사각형의 "위" (혹은 아래) 에 해당하는 변이 반사 변이 된다

        floor  = { obj->R(), obj->T() }; // 사각형의 오른쪽과 위쪽을 x, y로 하는 점 벡터
        floor -= { obj->L(), obj->T() }; // 원본에서 새로운 좌표를 빼서, 해당 종점에서 원본 종점으로 가는 선 벡터 작성
    }
    else //수평 충돌
    {
        // 옆에서 부딪쳤으니 사각형의 "옆"을 나타내는 변 = 수직에 가까운 각도가 반사 기준이 된다
        floor  = { obj->L(), obj->B() }; // 사각형의 왼쪽과 아래쪽
        floor -= { obj->L(), obj->T() }; // 빼는 점(새로운 시점)은 똑같이 왼쪽 위
    }
    // 이 시점에서 뭐가 됐은 반사변은 반드시 구해진 것이 된다

    // 이 반사변을 기준으로 만드는, 반사 계산에 이용할, 반사용 법선
    Vector2 reflect = floor.Normal(); //원본 법선 내기
    reflect         = reflect.GetNormalized(); // 정규화하기 (단위 벡터와 동등한, 길이 1인 벡터로)

    //위에서 만든 반사용 벡터와 총알이 원래 가지고 있는 방향 벡터를 점곱
    // (=두 벡터가 같은 각도로 찍어눌릴 경우 두 선의 길이가 가질 상호비율)

    float ratio = direction.Dot(reflect);

    //이 비율을 반사용 벡터(정규화가 끝난 수직 벡터)에 다시 곱해서 길이를 또 줄이기
    reflect *= ratio; //방향벡터와 y 좌표가 동일한 새로운 벡터가 나온다

    //이 벡터를 원본 방향에 두 번 더하거나... 혹은 그냥 2를 곱한 다음 더한다

    reflect *= 2;
    direction -= reflect; // 방향에 조정된 벡터를 더하면서 새롭게 변경
                          // 코드상에선 방향 벡터가 종점을 나타내기 때문에 계산을 할 때
                          // 새로운 종점을 찾기 위해 빼기 계산을 한다

    localRotation.z = direction.Angle();

    //모든 반사가 끝난 뒤에, 속도에 추가될 힘이 있을 경우 적용
    if (additionalForce != 0) speed += additionalForce;
}
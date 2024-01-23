#include "Framework.h"

Button::Button(wstring file)
    : Quad(file)
{
    collider = new RectCollider(size); // 여기서 size : 부모의 멤버 변수, 쿼드의 크기 = 그림의 크기
    collider->SetParent(this);
}

Button::Button(Vector2 size)
    : Quad(size)
{
    collider = new RectCollider(size); // 여기서 size : 지금 매개변수로 받은 Vector2 (위 코드와 철자가 같아도 호환 불가)
    collider->SetParent(this);
}

Button::~Button()
{
    delete collider;
}

void Button::Update()
{
    if (!isActive) return;

    if (collider->IsPointCollision(mousePos))
    {
        //이 안으로 들어왔으면 마우스 커서가 버튼 위에 놓인 상황

        //스테이터스가 정확히 업이냐 다운이냐를 먼저 판정 (bool을 이용)
        if (KEY_DOWN(VK_LBUTTON))
            isDownCheck = true;

        // 버튼의 상태는 둘 중 하나. 1. 눌리고+떼지는 상태(클릭) 2.마우스오버
        if (KEY_PRESS(VK_LBUTTON)) state = DOWN;
        else state = OVER;

        //스테이터스가 정확히 업이냐 다운이냐를 판정
        //enum을 쓸 경우 아래의 조건문을 활용 (위 if문 안에 넣으면 더 확실)
        //if (KEY_DOWN(VK_LBUTTON)) state = DOWN;
        //else if (KEY_UP(VK_LBUTTON)) state = UP;

        //enum이든, bool을 썼든, 위 코드를 통해서 아래 명제를 판별 가능
        // "마우스가 버튼 위로 올라갔고, 거기서 좌클릭을 했다-> 그러므로 버튼을 눌렀다"

        // 버튼이 동작을 수행하는 방법
        // 1. 지금처럼 충돌과 판정을 외부에서도 확인을 해서, 해당 경우에 연산을 수행 (키보드와 비슷한 방법)
        // 2. 반대로, 이 버튼에 어떤 동작을 미리 지정해뒀다가 누를 때 예약한 연산을 수행 (콜백과 비슷한 방법)
        // -> 여기서는 2번 방법으로 시도

        //버튼에 예약한 연산이 수행되는 시점은 사실 개발자가 정하기 나름
        // (버튼 누르자마자 수행, 일정 시간 눌러야 수행)
        // -> 여기서는 버튼을 눌렀다가 (크기가 주는 것까진 보고 나서) 떼면 수행하는 걸로
        if (isDownCheck && KEY_UP(VK_LBUTTON))
        {
            // 버튼 뗐다!

            if (event != nullptr) event(); //예약된 이벤트가 있으면 (함수 포인터에 할당된 값이 있으면) 수행
            if (paramEvent != nullptr) paramEvent(object); //예약된 "매개변수" 이벤트가 있으면 수행

            //그리고 연산 수행 후, 버튼 눌림을 해제
            isDownCheck = false;
        }
    }
    else
    {
        //여기로 들어왔으면 마우스 커서가 버튼 밖으로 나간 상황
        state = NONE;

        //bool로 눌림체크를 했다면 여기서도 리셋 코드를 넣어야 한다
        if (KEY_UP(VK_LBUTTON))
            isDownCheck = false;
    }

    //위에서 만든 상태에 따라 버튼에 시각적 피드백을 준다
    // -> 색이 바뀔 수도, 이펙트가 버튼이나 커서에 뜰 수도....
    // -> 지금은 트랜스폼을 이용해서 줄 수 있는 피드백을 준다 : 크기 조절
    switch(state)
    {
    case Button::NONE:
        localScale = { 1, 1 };
        break;
    case Button::DOWN:
        localScale = { 0.75f, 0.75 };
        break;
    case Button::OVER:
        localScale = { 1.1f, 1.1f };
        break;
    }

    //자기 업데이트 (그림 제어가 포함되면 쿼드 업데이트, 아니면 트랜스폼만 업데이트)
    Quad::Update();
    //Transform::UpdateWorld();

    //그리고 충돌체도 업데이트
    collider->Update();
    //collider->UpdateWorld();
}

void Button::Render()
{
    if (!isActive) return;

    Quad::Render(); //부모 렌더 처리 = 자기 출력
    collider->Render(); //콜라이더도 출력
}
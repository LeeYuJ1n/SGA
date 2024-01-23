#pragma once

class Button : public Quad
{
//public:
protected:
    enum State
    {
        NONE,
        //PRESSED, RELEASED, //좀 더 객관적인 표현, 엔진 툴 등과 같이 쓰면 좋다
        DOWN, UP, //좀 더 직관적인 표현, GetKeyboardState 함수 등과 잘 어울린다 (이 프레임워크와도!)
        OVER,
    };

public:

    //생성자를 만들 때, 부모 생성자에 토스해줄 매개변수를 같이 지정
    Button(wstring file);
    Button(Vector2 size);
    ~Button();

    // 사물이 가져야 할 인터페이스 (의도의 문제가 어느 정도 포함된)
    void Update();
    void Render();

    // 버튼에게 있어서는 이쪽이 더 필수 (외부에서도, 내부에서도 버튼이 눌림을 판정하기 위해서)
    RectCollider* GetCollider() { return collider; }

private:
    // 콜라이더 (눌림판정용)
    RectCollider* collider;

    // 눌림 그 자체가 데이터로 받아와질 수 있도록 만들어야 한다
    
    //코드를 통한 상태표현
    //int stateCode = 0; // 0 : 기본 상태, 1 : 눌린 상태.... 애니메이션의 액션코드와 같은 원리

    //enum을 통한 상태표현
    State state = NONE;

    //상태 코드와는 별개로 특정한 동시적 상태를 표현하기 위한 변수는 bool로 한번 더 체크
    bool isDownCheck = false; // 이 버튼이 정말 눌렸는가를 확인사살하는 변수


    // 버튼이 동작을 수행하는 방법
        // 1. 지금처럼 충돌과 판정을 외부에서도 확인을 해서, 해당 경우에 연산을 수행 (키보드와 비슷한 방법)
        // 2. 반대로, 이 버튼에 어떤 동작을 미리 지정해뒀다가 누를 때 예약한 연산을 수행 (콜백과 비슷한 방법)
        // -> 여기서는 2번 방법으로 시도

    //연산을 예약 후 수행하기 위해 필요한 것

    // 1. 예약할 연산을 지정해서 받을 변수
    // 2. 예약하기 위한 외부 기능

    // 1번의 수행 방법 : 함수 포인터 (정확, 신속)
    // void (*FuncName)(); // <- FuncName이라는 이름의 함수 포인터

    // ...그런데, 위 함수 포인터에는 작은 약점이 하나 있다
    // -> 바로 매개변수의 지정에 자유롭지 못하다는 것. (위 예시의 경우, 매개변수가 없는 코드만 등록가능)

    // 위 함수 포인터 대신 쓸 수 있는, c++의 추가 제공 기능 : std::function
    // -> 함수 객체화 코드, 함수처럼 불러오거나 쓸 수 있는 모든 종류의 인터페이스 코드를
    //    객체처럼 저장할 수 있게 만드는 자료형 제작 기능

    //std::function<void()> event = nullptr; // evect라는 이름의 "함수 포인터" 비슷한 것
    Event event = nullptr; //위 코드와 똑같다 (typedef 사용)
    // 찐 함수 포인터와의 차이점 : std::function 클래스가 주는 추가 제공 기능 등을 활용해서
    //                           매개변수가 있는 경우에도, 형변환이 필요한 경우에도 제한적으로 자유 대응 가능
    //                           매개변수가 있어도 없어도 된다는 뜻인가? -> 쓰면서 알아보자

    //std::function<void(void*)> paramEvent = nullptr; // 매개변수가 있을 경우 사용 가능한 버전
    ParamEvent paramEvent = nullptr; //위 코드와 똑같다 (typedef 사용)

    void* object; //"대상"이라는 이름으로만 지칭되는, 자료형이 뭔지도 모르는 그냥 메모리 주소
    //void* : 자료형이 뭔지 몰라서 지정조차 하지 않은 포인터를 가리킨다 (함수나 변수에서 void는 "없다"는 뜻)
    //        어떤 자료형의 메모리 주소도 받을 수 있지만, 이 자체로는 어떤 연산도 수행할 수 없다
    //        -> 보통은 여기에 메모리 주소를 담은 후, 연산할 때는 형변환 수행

    // 위 세 코드를 이용해서, 매개변수가 없거나 있는 함수, 매개변수가 있어야 되는 함수에 대응 가능

public: //위에 만든 "함수 포인터"들을 세팅하기 위한 외부용 기능
    void SetEvent(Event event) { this->event = event; }
    void SetParamEvent(ParamEvent event) { this->paramEvent = event; }
    void SetObejct(void* object) { this->object = object; }
};


#pragma once
class Human : public ModelAnimator
{
private:
    enum class ACTION
    {
        IDLE,
        RUN,
        JUMP,
    };

public:
    Human();
    ~Human();

    void Update();
    void Render();
    void GUIRender();

private:
    // 나중에 자식 개체가 붙거나 별도 연산 대상이 생기면 코드 추가
    // 자식 개체 : 모자, 배낭, 방탄조끼, 손에 든 무기 등
    // 별도연산 대상 : 발소리 체크를 위한 "내 발" 혹은 무기를 쥐기 위한 "내 손"

    // 예 : 쇠지렛대를 무기로 사용해, 손에 쥐기
    // Crowbar* crowbar;    //쇠지렛대 (근접 무기)
    Transform* mainHand; //주로 쓰는 손 (보통은 오른쪽인)
    Model* kunai;        // 쿠나이 (투척용 무기)

private:

    void ClipSync(); // 액션이 바뀌었을 때 동작을 재생하는 함수
    void Control();
    void Jump(); // 지금은 좌표격자(높이 0)가 마치 땅인 것처럼 만들어도 OK
                 // 혹은 존재하는 터레인 에디터 혹은 블록 매니저와 연결하거나....

    // 움직임용 변수들...

    ACTION action; // 수행 중인 액션

    // 일단은 예시 (써도 좋고, 수정해도 좋고....)
    float moveSpeed    = 0;
    float jumpVelocity = 0;
    float jumpForce    = 0.5f;
    float gravityMult  = 0.5f;

    // 현재 점프를 하는 중인가? (아니다 = false)
    bool isJump = false;
};
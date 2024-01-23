#pragma once

class Ninja : public GameObject
{
private:
    enum ActionType
    {
        IDLE = 0, RUN, JUMP,
        ATTACK = 10,
        JUMP_ATTACK, THROW, JUMP_THROW,
        DEAD, GLIDE, SLIDE, 
    };

public:
    Ninja();
    ~Ninja();

    void Update();
    void Render();

    // 캐릭터는 왼쪽을 보고 있는가?
    // 현재 다이렉트 x 환경에서 그림으로 표현된 캐릭터가 "왼쪽"을 보고 있다면 다음 두 조건 중 하나가 충족
    // 크기(x가 0보다 작아짐), 혹은 Y각도(180도)
    bool IsLeft() { return this->Rot().y == XM_PI; } // 왼쪽 여부 판별 가능

private:
    void Control();
    void Move();
    void Jump();
    void Attack();
    void SetIdle();
    void SetAction(ActionType type);
    void SetActionCode(int typeCode);
    void CreateActions();
    void StackCommandLR();

private:
    map<ActionType, Action*> actions;

    ActionType curAction = IDLE;
};
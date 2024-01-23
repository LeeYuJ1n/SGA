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

private:
    void Control();

    void Move();
    void Jump();
    void Attack();

    void SetIdle();

    void SetAction(ActionType type);
    void SetActionCode(int typeCode);

    void CreateActions();    

private:
    map<ActionType, Action*> actions;

    ActionType curAction = IDLE;
};
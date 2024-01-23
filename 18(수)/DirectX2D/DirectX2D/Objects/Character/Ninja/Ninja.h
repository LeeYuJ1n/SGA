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

    // ĳ���ʹ� ������ ���� �ִ°�?
    // ���� ���̷�Ʈ x ȯ�濡�� �׸����� ǥ���� ĳ���Ͱ� "����"�� ���� �ִٸ� ���� �� ���� �� �ϳ��� ����
    // ũ��(x�� 0���� �۾���), Ȥ�� Y����(180��)
    bool IsLeft() { return this->Rot().y == XM_PI; } // ���� ���� �Ǻ� ����

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
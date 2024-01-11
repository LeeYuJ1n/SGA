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
    // ���߿� �ڽ� ��ü�� �ٰų� ���� ���� ����� ����� �ڵ� �߰�
    // �ڽ� ��ü : ����, �賶, ��ź����, �տ� �� ���� ��
    // �������� ��� : �߼Ҹ� üũ�� ���� "�� ��" Ȥ�� ���⸦ ��� ���� "�� ��"

    // �� : �������븦 ����� �����, �տ� ���
    // Crowbar* crowbar;    //�������� (���� ����)
    Transform* mainHand; //�ַ� ���� �� (������ ��������)
    Model* kunai;        // ���� (��ô�� ����)

private:

    void ClipSync(); // �׼��� �ٲ���� �� ������ ����ϴ� �Լ�
    void Control();
    void Jump(); // ������ ��ǥ����(���� 0)�� ��ġ ���� ��ó�� ���� OK
                 // Ȥ�� �����ϴ� �ͷ��� ������ Ȥ�� ��� �Ŵ����� �����ϰų�....

    // �����ӿ� ������...

    ACTION action; // ���� ���� �׼�

    // �ϴ��� ���� (�ᵵ ����, �����ص� ����....)
    float moveSpeed    = 0;
    float jumpVelocity = 0;
    float jumpForce    = 0.5f;
    float gravityMult  = 0.5f;

    // ���� ������ �ϴ� ���ΰ�? (�ƴϴ� = false)
    bool isJump = false;
};
#pragma once
class SampleCharacter : public Rect
{
private:

    //�׼��� ������. ���� �ֿ� int �ڵ�� ����ߴ�
    // "���� ���� ���� �ϰ� �ִ°�?"�� ��Ÿ���� �ڷ���
    enum ActionType
    {
        IDLE, RUN, WALK, JUMP, JUMP_DOWN,
        HURT, DEAD,
        ATTACK_1, ATTACK_2, ATTACK_3,
        RUN_ATTACK
    };

    //ĳ������ �⺻ ����. ����� �����̶� ���� �������� ���ȭ
    //...���߿� ������ ���� ������� ������ �ٲ��� �Ѵٸ� const�� ������ �� ����
    const float WALK_SPEED = 500.0f; //�ȴ� �ӵ�
    const float RUN_MULT = 1.5f;     //�޸� ��� �ȴ� �ӵ��� ���� �¼�

    const float JUMP_POWER = 750.0f; //�����
    const float GRAVITY = 1500.0f;   //�߷°� (������ ����߸��� ���)
    const float BOTTOM_CHECK = 10.0f; //�ٴڿ� ���� ���ƴ°�, �׳� ������ �� �ߴ°��� �Ǻ��� �ȼ� ����

    const float GHOST_TIME = 3.0f;        // �¾��� �� �����̴� �ð� (=�̷� ��� ������ ��� ���߰ų�, ĳ���Ͱ� ������ �Ǵ� ���� ����)
    const float ALPHA_SPEED = 1000.0f;    // �����̴� �ӵ�

    const float ATTACK_DELAY = 0.1f;  //���� �Է��� ���޾� �Ͼ�� ���ϰ� �ϴ� �ൿ ���� �ð�
    const float ATTACK_COMBO = 0.5f;  //���� �� Ȥ�� �Ŀ� ���� ������ �̾ �߻��� �� �ֵ��� �ϴ� �޺� ��� �ð�

public:
    SampleCharacter();
    ~SampleCharacter();

    void Update();
    void Render(HDC hdc);

private:
    void Jump();          // �ٱ�
    void GetHit();        // ���±�
    void EndGetHit();     // ���±� ���� (���� �Լ�)
    void Die();           // �ױ�

    void Attack();              // ����
    void Attack_Run();          // �޸��鼭 ���� (���� �Լ�)
    void Attack_GetCombo();     // �޺� ����
    void Attack_InputDelay();   // �Է� ���� ����
    void EndAttack();           // ���� ���� (���� �Լ�)

    bool OnGround();            // (bool ��ȯ�� �ִ�) ĳ���Ͱ� �� ���� �ִ°�?
    void WalkAndRun();          // �Ȱ� �޸��� (���� �̵�)

    void AutoAnimation();               // �ڵ� �ִϸ��̼� (Ư�� ���ǿ��� �Է��̳� �Լ� ȣ�� ���̵� �׼��� �ٲ��� �� �� : �������� ��)
    void SetAction(ActionType type);    // �׼��� �Ű������� ���� �����ϱ�

    void CreateAnimations();     // (������ �߿� ȣ���ϴ�) �ִϸ��̼� �����

private:
    Texture* texture;           // �� ĳ���Ͱ� ����� ��Ʋ�� �ؽ�ó (=��������Ʈ ��Ʈ)

    ImageRect* imageRect;       // �� ĳ������ �ؽ�ó�� ��µǱ� ���� ���� (�̹��� ����)
    Vector2 imageOffset;        // �̹����� ��߳� ���, ��ġ�� �ٷ���� ���� ����ġ

    map<ActionType, Animation*> animations;   // �ִϸ��̼� ���� (��)

    ActionType curAction = IDLE; // ������ �׼�

    bool isLeft = false; // ������ ���� �ִ°�?

    float yVelocity = 0.0f; // ������ �̵� �ӵ�
    UINT jumpCount = 0;     // ������ Ƚ��

    UINT attackCount = 0;               // ������ Ƚ��
    float attackInputDelay = 0;         // ���� �Է� ���� ����
    float attackComboCurrentTime = 0;   // ���� �޺� �Է� ����
    bool isAttacking = false;           // ���� ���ΰ�?

    bool isGhost = false;               // ���� ���� �����ΰ�? (����, Ȥ�� �Ͻ� ����)
    float ghostTime = 0.0f;             // ���� ���� ������ ���, ���� ������� ���� �ð�

    float alphaValue = 255;             // ���� ���� (=���úҰ���. "�������� ����")
    bool isIncreaseAlpha = false;       // ���� ���� ���� �� ���İ� �þ ���ΰ�? (������ ��꿡 ���)

    bool isHighProfile = false;         // ���� "�Ҷ�������" �����ΰ�?
                                        // �Ҷ������� = ���� ĳ���Ͱ� �ൿ�� �� ũ��, �ò�����, ���ϰ� �ϴ� ����
                                        // ���� -> ������, �ȱ� -> �޸���, �Ϲݻ��� -> ��������

    wstring attacks;                    // �α� : ���� Ƚ�� ���� ����ϰ� ������ ����ص� �Ǵ� ���� (���� �̻��)
};


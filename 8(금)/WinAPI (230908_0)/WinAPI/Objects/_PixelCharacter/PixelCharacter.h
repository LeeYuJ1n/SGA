#pragma once

class PixelCharacter : public Rect
{
    // �ȼ� �浹 �� ���� ���� ���� ĳ����
    // �̵�, ����, "�� ���"�� ���� ������ҽ��ϴ�!
    // �� �ڼ��� ������ �ڵ峪 �ּ� ���� "���� ĳ����"�� �������ּ���!
private:

    enum ActionType
    {
        IDLE, RUN, JUMP, JUMP_DOWN, FIRE
    };

    float WALK_SPEED = 700.0f;
    float JUMP_POWER = 700.0f;
    float GRAVITY = 1500.0f;
    float BOTTOM_CHECK = 10.0f;

public:
    PixelCharacter();
    ~PixelCharacter();

    void Update();
    void Render(HDC hdc);

    float GetSpeedX() { return xVelocity; }
    float GetSpeedY() { return yVelocity; }

    // �� �� ���൵ ����
    // * �� ��� �ܿ� "ī�޶�" Ŭ������ �ִٸ� �� ���ϰ� ��ġ ����
    //   ....�մϴٸ� ����� ����ȭ�� ���� �ܼ��� ����� ���ڽ��ϴ�.
    void SetProcessLimit(float value) { maxProcessInScene = value; }
    float GetProcess() { return currentProcessInScene; }

    // �ٴ� ���� �ޱ�
    void SetLand(Landscape* target) { curLand = target; }

private:
    //�̵� (�ٱ�, �޸���)
    void Jump();
    void Run();

    //��� (�Ѿ��� ���� �Ŵ��� ����)
    void Fire();
    void Fire_End();

    //��������
    void FallAnimation();

    //�ִϸ��̼� ���� (�׼� �Ҵ�, �ִϸ��̼� �ʱ�ȭ)
    void SetAction(ActionType type);
    void CreateAnimations();

private:
    //�ؽ�ó�� ����
    Texture* texture;
    ImageRect* imageRect;
    Vector2 imageOffset;

    //���İ� �ٲ�� ���⼭ �ݿ��ؾ� ������...
    int baseAlpha = 255;
    float texAlpha = 1.0f;
    float Alpha() { return (float)baseAlpha * texAlpha; }

    //�ִϸ��̼ǰ� �׼�
    map<ActionType, Animation*> animations;
    ActionType curAction = IDLE;

    //�̵� ���� (����?, �߻翩��, �ӵ�, ���� Ƚ��)
    bool isLeft = false;
    bool isFiring = false;
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    UINT jumpCount = 0;

    //�� �� ���൵ (ĳ���Ͱ� �����ϰ�, ���� ����ȭ)
    float currentProcessInScene = 0;
    float maxProcessInScene;

    //�ӽ� ������ : �ǹٴ��� �����?
    float minHeight = WIN_HEIGHT;

    Landscape* curLand;

    HBRUSH skyBrush;
    HPEN skyPen;
};


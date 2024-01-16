#pragma once
class Robot
{
private:
    //enum class STATE // <- �� ��� Ŭ������ "STATE" ����� ����
                       //    ���� : Ÿ�ڰ� ������ ���� �ӵ��� (���� ���� ����) ������
                       //  **����** : enum ���� �ߺ��� ��, �ݵ�� �ǵ��� ���� ȣ�� ����
    enum State
    {
        STAND_UP,
        WALK,
        RUN,
        HIT,
        DYING,
        // ���¸��� ���� : fbx�� Ŭ���� (ù ���� �빮��, ������ �ҹ���. ��: "Dying")
    };

public:
    Robot(Transform* transform); // ���ϸ� �ν��Ͻ� ����
    ~Robot();

    void Update();
    void Render();

    SphereCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

private:

    // ���� �ȿ��� �߰��� �Ŷ�� ���⿡ ��� ���� �߰��� ��
    // (�ۿ��� ����� �׷� �ʿ� ����!)

    Transform* transform;
    SphereCollider* collider;

    float moveSpeed = 30;

    Vector3 velocity; // ������ �ᵵ ������ �ƴϾ �Ǵ� ���� ����
                      // ������ ��, �ƴ� �� �� ���� ��� ����
    

};
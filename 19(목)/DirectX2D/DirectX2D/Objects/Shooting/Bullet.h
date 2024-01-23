#pragma once

class Bullet : public Quad
{
public:
    Bullet();
    Bullet(wstring file); // ��Ʈ�� ���ڿ��� ���� �̸��� ���� ���, �ش� ���Ͽ� �ش��ϴ� �ؽ�ó�� Ŀ���� �����ϰ�
    ~Bullet();

    void Update();
    void Render();

    //�� �Լ� : ��ü�� �Լ� 4��

    //�Ѿ��� ���� �Լ�
    void Fire(Vector2 pos, Vector2 direction);

    Collider* GetCollider() { return collider; }

    void ReflectByVector(RectCollider* obj, Vector2* overlap, float additionalForce = 0);
    // �簢�� �ݻ� �Լ�, �Ű������� ���ʷ� �ε�ģ �簢��, �ε����� ���� ���(����), �߰� ��
    // ������ �Ű������� �߰� ���� �⺻���� 0�̶�� ���� �־��� ������ ȣ�� �� �Է��� ���� �ʾƵ� �ȴ�

    void Reverse() { direction *= -1; }

private:

    //�Ѿ��� winAPI������ �׷��� ��ó�� �ڱ⸸�� �߰� ������ �ʿ��ϴ�

    Vector2 direction;
    //���� ���� : winAPI�ʹ� ���� �ٸ���, ���� ���� ���� �ʰ� "�߻�� �Էµ� ����"�� �����ϴ� ���ܿ� ������
    //           -> ���� ��ü ������? Ʈ�������� �����ϱ�
    //           "�߻�� �Էµ� ����"�� �ʿ��� ����? - ��� ������� ������ ��� �𸣴ϱ�

    //�Ѿ� �ӵ�
    float speed = 200.0f;

    Collider* collider; // <- ������ �ݶ��̴��� �ϰ�, ������ ��ü��
};


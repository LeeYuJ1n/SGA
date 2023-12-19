#pragma once
#include "Objects/Basic/GameObject.h" //�浹ü ����� ���� �о��� ��� ���ӿ�����Ʈ ������ �����ϱ� ���� (��ȣ ������ ���)

// 2D(�����)-3D(���� �� �� ��İ���) ������ ����� ���踦 �����ϱ� ���� "����"
struct Ray
{
    // ������ ���� �ϴ� ��
    // 1. �� ������ ��𼭺��� �Դ°�?
    // 2. �� ������ ���� ���°�?

    Vector3 pos;
    Vector3 dir;

    Ray() {}
    Ray(Vector3 pos, Vector3 dir) : pos(pos), dir(dir)
    {
        //this->pos = pos;
        //this->dir = dir;
    }
};

// ������ �����Ѵٸ�, �ش� ������ ��ü�� �ε�ģ ������ ���� ���̴�
// �ش� ������ ǥ���ϱ� ���� ���� ����ü

struct Contact //����
{
    string tag; //������ �̸�
    //�� �浹 ������ ����� ����ĳ���� ��� ��ȯ�� �Ͼ�� ��, �ش� ��찡 �ʿ��� ��Ȳ���� �˷���
    // 1. �浹�� ������ ������ �̸�, 2. ������ ���� ������ ���ȴ�
    // �׷��� 1, 2������ ������� ���� ��� (���ǿ� �̸��� ����, ������ ���� ����� ��ü �� ��ȣ�ۿ��� ��)
    // ������ ������ �ϱ� ���� �±� ������ �� �ʿ��ϴ�

    // ������ ���� �׸� : ��� �ε��ƴ°�(�浹��),
    // ���� �ε�ġ����� ������ �󸶳� �Դ°�(�Ÿ�)

    Vector3 hit;
    float distance; // �Ÿ��� "�׳� ����"�� �׳� ����(=��Į��)�� ǥ��
};

// ������ ������ Ȱ���ϴ� �ܼ��� ������ �浹ü Ŭ���� �����
// + �������̽��� ���� ȣȯ�� ���̱�

//class Collider : public Transform // 2D������ ���, �⺻������ �Ӽ��� �̾�޴� Ʈ�� ����
class Collider : public GameObject  // �⺻��(Ʈ�������� �⺻ ���� ��ü)�� �ְ�, �ű⿡ ���ο� �Ӽ��� �ο��ϴ� ������Ʈ ����
{
protected: //��ӹ��� ���� �浹ü�� ���� �����ϵ���
    
    enum class Type
    {
        //RECT, CIRCLE // ���簢��, �� : 2D�� ��Ī
        //CUBE, SPHERE // <- "���� ����"(������Ƽ�� ��)�� 3D ��Ī
        BOX, SPHERE, // ���� ���̴� 3D �浹ü�� ��Ī��
    };

    const float PUSH_SPEED = 500.0f;

public:
    Collider();
    ~Collider();

    void Render(); //����

    bool IsCollision(Collider* collider); //�浹 �Ǻ�

    // Ÿ�Ժ� �浹 ���� �Ǻ� ���� ����� (�������̽�)
    // 
    // ������ �浹ü (�⺻ �浹 ���� : �� �浹�̳� �� �浹�� ����)
    virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact = nullptr) = 0;
    // �Ű������� ���� IN�� OUT : ���� �ڵ�� �ƴϰ�, �׳� ���߿� ���� �� �� �Ű������� ������ �� ����ϱ� ���� �޸�
    // IN Ray ray : �Լ��� ���� ����"��" ���ڴ� // OUT Contact* contact : �� �Լ��� ����� ������ ��ȯ���� ������ �� ����ü�� ��ڴ�

    virtual bool IsSphereCollision(class SphereCollider* collider) = 0;
    virtual bool IsBoxCollision(class BoxCollider* collider) = 0;

    // �����ÿ� �浹ü ���̱� ��� ������ ���ΰ�

    void SetColor(Float4 color) { material->GetData().diffuse = color; } // ���� ����
    void SetColor(float r, float g, float b)
    {
        material->GetData().diffuse = { r, g, b, 1 };
    }

    //���� ���
    void RenderOnOff() { isRender = !isRender; } // A = !A : bool ���� ���� ���� ������
    static void RenderOnOffAll() { allRender = !allRender; } // ����(����)�Լ�ȭ - ��� ������ �ϰ����� (�����ɼ�)
    void RenderLineToggle() { isRenderAsLine = !isRenderAsLine; }

protected:

    virtual void MakeMesh() = 0; // Ʈ�������� �޽� ����� : �̹����� �浹ü�� ����

    Type type; //�浹ü ���� ����

    Mesh<Vertex>* mesh; // �������� ���� ��� Ʋ

    bool isRender; // ���� ���� (Ʈ�������� �� �޴� ��� ���� �����) : ������ �� �ص� �浹�� �ؾ� �� �� �־
    static bool allRender;

    bool isRenderAsLine = true;
};


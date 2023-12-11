#pragma once
#include "Objects/Bullet1.h"

class SpawnCircleScene : public Scene
{
public:
    SpawnCircleScene();
    ~SpawnCircleScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

private:
    HBRUSH hBrush;
    HPEN hPen;

    //POINT rectPos = { (int)CENTER_X, (int)CENTER_Y };
    Rect* rect;

    Circle* circle; // ���׶��
    float speed = 10; // ���׶�̸� �����̰� �;, �����̴� �ӵ�

    // ���� �׸����� �մϴ�
    float length = 120;
    float angle;
    Vector2 pos;

    int toggle;

    // �Ѿ��� ���� �ν��Ͻ� : �Ҵ� �� ���� ��� ���
    vector<Bullet1*> bullets;
    float bulletSize = 10; // �Ѿ� ũ�⸦ ���⼭ �̸� ����
    int bulletCount = 5;   // �� ���� �� �� �ִ� �Ѿ� ���� �̸� ����

    // �簢�� ������ ���� �ν��Ͻ��� ���� (���� ������Ʈ ���) : ������ ����
    vector<SpawnObject*> rects;
    // �߰� ������ �ʿ��ϰ�����, �ʿ��� �� ���ƿ��ڽ��ϴ�

    // �ݻ� ���� �Ǻ��ϱ� (�׸��� �Ѿ� �ݻ���� ȣ������)
    void ReflectBullet(Bullet1* bullet, SpawnObject* rect) // �Ű������� �Ѿ˰� �簢�� �ʿ�
    {
        // ���� ũ���� ���� �簢�� �����
        Vector2 diameter = { bullet->GetRadius() * 2, bullet->GetRadius() * 2 };
        Rect tempRect(bullet->Pos(), diameter);

        // �ִ��� �� ���� �簢���� �������� ������ ������ �ٽ� ���Ѵ�
        float _left = tempRect.Left() > rect->Left() ? tempRect.Left() : rect->Left();
        float _right = tempRect.Right() < rect->Right() ? tempRect.Right() : rect->Right();
        float _top = tempRect.Top() > rect->Top() ? tempRect.Top() : rect->Top();
        float _bottom = tempRect.Bottom() < rect->Bottom() ? tempRect.Bottom() : rect->Bottom();

        // ������ ���鳢�� �ٽ� �Ÿ��� �����Ѵ�
        float xDiff = _right - _left;
        float yDiff = _bottom - _top;

        // �� ����� ���ؼ� (�� �簢���� ���� ������ �ʾ�����...)
        // ������ �簢���� ����� ���� ���� ������ ��� �����

        // ���⼭ ���� ���� ������ �Ÿ��� ���� �簢���� ��絵 ������ �� ������

        // �� �簢���� �����ϸ� = xDiff�� �� ũ�� ���� �浹�� �Ͼ �� (���Ϲ���)
        if (xDiff > yDiff)
        {
            // �����浹

            // ���� �ǵ� : �Ѿ˿��� "�浹"�̶�� �Լ��� �����ؼ� �ҷ����� ������

            float currentAngle = bullet->Angle();

            bullet->SetStat((PHI * 2) - currentAngle, bullet->Speed());
            // ȣ��  = ������, ȣ�� ���ϱ� ������ = ȣ(�� ȣ�� ����)
            // ȣ�� ���ϱ� ������ ���ϱ� 2 = �� (360��)
        }
        else
        {
            // �����浹
            float currentAngle = bullet->Angle();

            bullet->SetStat(PHI - currentAngle, bullet->Speed());
        }
    }
};


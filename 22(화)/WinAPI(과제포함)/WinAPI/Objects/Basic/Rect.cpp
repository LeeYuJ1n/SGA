#include "Framework.h"

Rect::Rect(Vector2 pos, Vector2 size)
    : GameObject(pos), size(size)
{
}

Rect::Rect(float left, float top, float right, float bottom)
{
    pos.x = (left + right) * 0.5f;
    pos.y = (top + bottom) * 0.5f;

    size.x = abs(right - left);
    size.y = abs(bottom - top);
}

void Rect::Render(HDC hdc)
{
    if (!isActive)
        return;

    int left = (int)(pos.x - size.x * 0.5f);
    int right = (int)(pos.x + size.x * 0.5f);
    int top = (int)(pos.y - size.y * 0.5f);
    int bottom = (int)(pos.y + size.y * 0.5f);

    Rectangle(hdc, left, top, right, bottom);
}

bool Rect::IsCollision(const Vector2& point) const
{
    if (!isActive)
        return false;

    if (point.x > Left() && point.x < Right())
    {
        if (point.y > Top() && point.y < Bottom())
            return true;
    }

    return false;
}

bool Rect::IsCollision(const Rect* rect) const
{
    if (!isActive) return false;
    if (!rect->isActive) return false;

    if (rect->Left() < Right() && rect->Right() > Left())
    {
        if (rect->Top() < Bottom() && rect->Bottom() > Top())
        {
            return true;
        }
    }

    return false;
}

bool Rect::IsCollision(const Circle* circle) const
{
    // �� �� Ȱ��ȭ���� ����ǵ��� return�� �ۼ�
    if (!isActive) return false;
    if (!circle->isActive) return false;
    // ���ȭ�� �Լ��� ����� �ƴ� �Լ��� ���� ���Ѵ�
    // �������� ���� Ŭ���������� (��� �Լ��� ���� ��, ��) ���ٿ� ������ �ɸ���
    // (Ŭ���� ������ �ο��� ������� Ÿ Ŭ������ ���ѵ� ���ٱ� ������ ���ݵ� ������ ���Ѵ�)
    // �׷��� �������� ��? �������� �⺻������ �Ȱ��� Ŭ�����ϱ�..(���赵�� �����ϴϱ�)

    // �ذ� ����� ��
    // 1. �Լ��� ����� �ƴ� �ɷ� �ٲٰų� : �ּ�å. �׷��� �̹� �ۼ��� �� �� �� �� ���� �ٲٸ� ������
    // 2. Active()�� ����� �ٲٰų� " ����å. ���ȭ�� �Լ��� ���߿� �����ϱ⵵ �����
    // 3. ������ ���ٱ��� public���� �ٲ������ �ȴ� : ��å. �׷��� �̹� �ۼ��� �� ��� �� ��Ȳ�̸� ���� ���������� Ȯ��

    // �� �簢���� ���� �߽��� ��ġ���踦 ����...
    
    // �簢���� �߽��� �Ǵ� ���ڰ� ���� �ȿ� ���� �߽��� ���� ������
    // ���� ������ �ִ�Ÿ����� �簢���� �浹
    bool isCross = false; // ���ڰ� ������ �Դ°�? (�������� �ʱ�ȭ)

    if (circle->pos.x > Left() && circle->pos.x < Right()) isCross = true;
    if (circle->pos.y > Top() && circle->pos.y < Bottom()) isCross = true;

    if (isCross)
    {
        // ���� ���� ũ�⸦ ���ͷ� �̸� ���� (�����̶�� ���)
        Vector2 diameter = { circle->GetRadius() * 2, circle->GetRadius() * 2 };
        Rect tempRect(circle->pos, diameter);
        // �� ������ ũ���, �� ��ġ�� ��ġ�� �ϴ� ������ �簢�� �����

        // �簢������ �浹! ...�ϰ� ����� ��ȯ�ϸ� �ȴ�
        // (���� �簢���� �浹 �ó����� #2 : ���ڰ� ���� ����)
        return this->IsCollision(&tempRect);
    }
    else
    {
        // �ó����� #1 : ���ڰ� ���� �ۿ� ���� �ִ� ���
        // �� ���� �簢���� �������� ������ �ϴ� ���

        // �簢���� ������ ������ ������
        Vector2 vertex[4]; // vertex : ������
        vertex[0] = { Left(), Top() };
        vertex[1] = { Left(), Bottom() };
        vertex[2] = { Right(), Top() };
        vertex[3] = { Right(), Bottom() };

        // �������� �ݺ������� ������
        for (Vector2 point : vertex)
        {
            // ���� ���� �浹�Ѵٸ�
            if (circle->IsCollision(point))
            {
                return true; // ����ȯ
            }
        }
    }
    // ������� ���� 1. ���ڰ� ������ �ƴϰ� 2. �������� ���� �������� ���� ��
    // �� ���� �� ��ģ ��

    return false;
}

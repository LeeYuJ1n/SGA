#include "Framework.h"
#include "SpawnCircleScene.h"

SpawnCircleScene::SpawnCircleScene()
{
    // ��Ŭ ����
    circle = new Circle(Vector2(CENTER_X, CENTER_Y), 50);

    hBrush = CreateSolidBrush(RGB(0, 255, 0));
    hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
}

SpawnCircleScene::~SpawnCircleScene()
{
    delete rect;
    delete circle;

    DeleteObject(hBrush);
}

void SpawnCircleScene::Update()
{
    int width = WIN_WIDTH;
    int height = WIN_HEIGHT;

    // asdw�� �Է��ϸ� �����̰�
    if (KEY_PRESS(VK_LEFT))
    {
        circle->Pos() += Vector2(-speed, 0);
    }
    if (KEY_PRESS(VK_DOWN))
    {
        circle->Pos() += Vector2(0, speed);
    }
    if (KEY_PRESS(VK_RIGHT))
    {
        circle->Pos() += Vector2(speed, 0);
    }
    if (KEY_PRESS(VK_UP))
    {
        circle->Pos() += Vector2(0, -speed);
    }

    // ���� �׸��� �غ� : ������ ������ ���� ����
    angle = -atan2(mousePos.y - circle->Pos().y, mousePos.x - circle->Pos().x);
    // atan2 : ź��Ʈ �ﰢ�Լ��� ���ؼ� ������ ���س��� �Լ��� �����ϴ� ����� ver2
    // �ﰢ�Լ��� ����(y�� ����)�� ����� ��� ����(y�� ������ ���߷��� ���ʵ� -1 ���ϱ�
    // ������ ��ǥ
    pos.x = circle->Pos().x + cos(angle) * length;
    pos.y = circle->Pos().y + -sin(angle) * length;

    // ���� ������ �׸� ���� : �ϳ��� "��ž"�� ���� ���� �׷����� �׸��� ����
    //                        �� ��°�� ������ �ٽ� �׸��鼭 �ﰢ�Լ��� �Ӽ��� �����ϱ� ����
    //                        �� �ᱹ ������ �� ���� ����, ������ ������ ����

    // ���⼭ ��Ŭ�� �� "�Ѿ�" ����
    if (KEY_DOWN(VK_LBUTTON))
    {
        bullets.push_back(new Bullet1(circle->Pos(), 10));
        bullets[bullets.size() - 1]->SetStat(angle, 20); // ���� �׸��⿡ �� ���� �״�� �ֱ�
        bullets[bullets.size() - 1]->Go();
    }

    // ������ ���⼭ �������ͽ��� ������������,
    // ���� ó������ Ŭ���� ���� �������ͽ��� �־������
    // �� ���� �Ѿ��� �׳� "��⸸"�ص�(������ ȣ���ص�) �ٷ� ������ ��!!!
}

void SpawnCircleScene::Render(HDC hdc)
{
    SelectObject(hdc, hBrush);
    circle->Render(hdc);

    // ���� �׸���
    SelectObject(hdc, hPen);
    // ������ ���� �߽�
    MoveToEx(hdc, circle->Pos().x, circle->Pos().y, NULL);
    // ������ �׸����� ��ġ����
    LineTo(hdc, pos.x, pos.y);

    // �Ѿ˵�...
    for (Bullet1* bullet : bullets)
    {
        bullet->RefreshLocation();
        bullet->Render(hdc);
    }
}

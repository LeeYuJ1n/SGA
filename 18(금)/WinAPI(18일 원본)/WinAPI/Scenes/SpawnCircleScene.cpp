#include "Framework.h"
#include "SpawnCircleScene.h"

SpawnCircleScene::SpawnCircleScene()
{
    srand(GetTickCount64());

    // �Ѿ��� �̸� ����
    bullets.resize(500);

    // for each ���
    for (Bullet1*& bullet : bullets)
    {
        bullet = new Bullet1(Vector2(), bulletSize); 
        // ��ġ, ����. ũ��, �̸� ������ ���

        // ��Ƽ�굵 ����, ���߱�
        bullet->Active() = false;
        bullet->Stop();
    }

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
        // bullets.push_back(new Bullet1(circle->Pos(), 10));
        // bullets[bullets.size() - 1]->SetStat(angle, 20); // ���� �׸��⿡ �� ���� �״�� �ֱ�
        // bullets[bullets.size() - 1]->Go();

        for (Bullet1* bullet : bullets)
        {
            if (bullet->Active() == false)
            {
                bullet->SetStat(angle, speed); // ������ �ӵ� �ο�
                bullet->Pos() = circle->Pos(); // ��ġ ����
                bullet->Go();                  // "����!"
                bullet->Active() = true;       // Ȱ��ȭ (����)
                break; // �� �Ѿ˸� Ȱ��ȭ�ϰ�, �ٸ� �Ѿ��� (�ݺ��� �߿�) �� ������ �ʱ�
            }
        }
    }

    if (KEY_DOWN(VK_RBUTTON))
    {
        rects.push_back(new SpawnObject());
        rects[rects.size() - 1]->Spawn();
    }

    // ������ ���⼭ �������ͽ��� ������������,
    // ���� ó������ Ŭ���� ���� �������ͽ��� �־������
    // �� ���� �Ѿ��� �׳� "��⸸"�ص�(������ ȣ���ص�) �ٷ� ������ ��!!!

    // �浹�� ���� ��� ������ �ݺ��� ����
    
    // �� �Ѿ���...
    for (Bullet1* bullet : bullets)
    {
        // * for each���� ���۵Ǳ� ���� whileó�� ���ο��� ����� ������ �̸� �ʱ�ȭ ����
        // ���⼭�� �簢�� ������ �ݺ��ڸ� �̸� ���� ��ġ�� �����
        vector<SpawnObject*>::iterator itRect = rects.begin();
        // �� �簢����....
        for (SpawnObject* rect : rects)
        {
            // �浹�� �����״ٸ�
            if (bullet->IsCollision(rect))
            {
                // ������ �����Ѵ�
                // �ݻ�� ��� ����?

                // 1. ��� �ݻ�ƴ°�? ("��� �ݻ�ƴ°�?")
                //    �� �ڸ��� ����, ������ ����, ��Ȳ�� ����
                //    �� �� �� �ȿ� �Լ��� �ִ� ���� ����

                // 2. �ݻ��ؼ� ��� �Ǵ°�? �� �Ѿ��� ����

                // �� ������ ������ ù �Լ��� ������� ����� ȣ��
                // (1. ���� ��, 2. ���� �Լ� ������ ȣ��)
                ReflectBullet(bullet, rect);

                // �簢���� ����� �ʹ�
                rect->Destroy(); // �ð����� �� Ȱ��ȭ ����
                // �׸��� �긦 ���Ϳ� �޸𸮿��� ������ �ؾ� �ϴµ�..
                SpawnObject* rectDelete = rect;
                rects.erase(itRect); // �Ʊ� ���� �ݺ��� ������ �̿��� ��Ÿ���� ����
                delete rectDelete; // �޸𸮿��� ����
                break; // �簢�� �ݺ��� ��ü�� �ߴ� (���� ȿ�� ���̱� �� �ݺ��� �ʱ�ȭ����)
            }
            // �浹�� �� �Ͼ�ٸ�...
            // ���� �簢���� �˻��ϱ� ���� �ݺ��� ������ ���� (���� �簢���� �����ϵ���)
            itRect++;
        }
    }
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
        if (bullet->Active()) // Ȱ��ȭ�� ���� �����ϵ���
        {
            bullet->RefreshLocation();
            bullet->Render(hdc);
        }
    }

    if (rects.size() > 0)
    {
        for (SpawnObject* rect : rects)
        {
            rect->Render(hdc);
        }
    }
}

#include "Framework.h"

Plane::Plane() : Quad(L"Textures/Shooting/airplane.png")
{
    //�׸��� ���� ���带 ���� ���� Ŭ������ ������� ��
    //�⺻������ "����"�� Ȯ��
    
    //������ �Ѿ��� ������� �״� �Ѿ˿� ����� �ڵ� �� �� ��

    tag = "Airplane"; //������ �ĺ��� (�±�) �ο�
    BulletManager::Get(); // �̱��� ȣ�⸸

    // �ͷ��� �÷��ο��� �����
    turret = new Quad(L"Textures/Shooting/player.png");
    turret->SetParent(this);
    turret->Pos() = { 100, 0 }; //��� ��ġ ����

    // �ݶ��̴� ����
    collider = new RectCollider(texture->GetSize());
    collider->SetParent(this);
}

Plane::~Plane()
{
    //BulletManager::Delete(); // �Ҹ��Ŵ��� ���� (������ ������ �� ���� �� ���ϱ�)
                             // ���� �����ϰ� ���� �� ���, �� �ڵ�� ������ ���� ���� ���� ����

    //���� ������ ����
    delete collider;
    delete turret;
}

void Plane::Update()
{
    //�����̴� �Լ� ȣ���ϱ�
    Move();
    Rotate();
    Fire();
    //��Ȳ�� ���� ���� �ڵ� ȣ���ϱ�
    Crash();

    //�ڱ� (�θ�) ������Ʈ
    GameObject::Update();
    collider->Update();

    //�Ѿ� ������Ʈ
    //BulletManager::Get()->Update();

    turret->Update();
}

void Plane::Render()
{
    //�ڱ� ����
    Quad::Render();
    collider->Render();

    //�Ѿ� ����
    //BulletManager::Get()->Render();
    turret->Render();
}

void Plane::Move()
{
    //����� ���忡�� �����¿�� �����̱�
    if (KEY_PRESS('A')) localPosition += Up() * DELTA * 200.0f;
    if (KEY_PRESS('D')) localPosition -= Up() * DELTA * 200.0f;
    if (KEY_PRESS('W')) localPosition += Right() * DELTA * 200.0f;
    if (KEY_PRESS('S')) localPosition -= Right() * DELTA * 200.0f;
}

void Plane::Rotate()
{
    // ȸ���ϱ�
    // (�� ��ǥ�� ����) z������ ȸ���� �ؼ� �Ѹ��� �����ϸ�
    // -> �����(�׸���) ȸ��

    if (KEY_PRESS('Q')) localRotation.z += DELTA * 10.0f;
    if (KEY_PRESS('E')) localRotation.z -= DELTA * 10.0f;

    // ��ž ȸ�� (�ǵ��� ��� �� �Ǹ� �ӽ÷� �ٽ� ����)
    if (KEY_PRESS('Z')) turret->Rot().z += DELTA * 5.0f;
    if (KEY_PRESS('C')) turret->Rot().z -= DELTA * 5.0f;
}

void Plane::Fire()
{
    //���� �Ҹ� �Ŵ������� �Լ��� ȣ��

    // ��ž�� �ٷ� ���� ���� (��ž�� ���� ���Ǵ� �ᱹ �Ѿ� ���� ��ġ�� �������ϴ� �� �����̴ϱ�)
    // �����̶��, ���� ��� �� ĳ���Ͱ�, ���̶� ������ �׳� �Ѿ� ���� ��Ҹ� �����ϴ� ���̶�� ������ ����
    if (KEY_DOWN(VK_LBUTTON))
    {
        //BulletManager::Get()->Fire(localPosition, Right()); // ��ž�� ���� ���
        //BulletManager::Get()->Fire(turret->GlobalPos(), Right()); // ��ž�� �ְ�, ����� �������� �� ��
        BulletManager::Get()->Fire(turret->GlobalPos(), turret->Right()); //��ž�� �ְ� ��ž�� ������ �������� �� ��

        // ���� �� ���� ��ũ!
        Audio::Get()->Play("Bonk");
    }
}

void Plane::Crash()
{
    // �� �߿� ������ �ε�ġ�� �Ͼ ���̴ϱ�

    //for (Enemy* enemy : EnemyManager::Get()->GetEnemies())
    //{
    //    if (enemy->Collision((RectCollider*)collider))
    //    {
    //        //���� �÷��̾ �ε�ģ ���
    //        // �÷��̾ �״� ��� ���⿡ �ڵ� �ۼ�
    //
    //        // �׽�Ʈ: ���� �׾��ٰ� �ٸ� ������ �ٽ� �����
    //        //        == ��ġ�̵�
    //
    //        enemy->Respawn();
    //    }
    //}

    //�Ѿ� �浹

    // �Ʒ� �ڵ�� �̴�δ� �� �� ����.
    // ���� : �ٸ� �ν��Ͻ��� �� ���ǹ��� ���ÿ� ȣ���� �ǰ� �־ + �� ������ ���� �ν��Ͻ��� ȣ���� �õ��ؼ�
    //        -> �ֿ� �����Ͱ� �̱��Ͽ� �־ �׷���.
    //for (Bullet* bullet : BulletManager::Get()->GetSceneBullet())
    //{
    //    Vector2 overlap = { 0, 0 };
    //    if (collider->IsRectCollision((RectCollider*)bullet->GetCollider(), &overlap))
    //    {
    //        bullet->Active() = false;
    //        bullet->GetCollider()->Active() = false;
    //    }
    //}

    // �׷��� ������ �� ������ ��� �ذ��� �� ������?
    // -> ��κ��� �ٸ� ������ó�� ������ �������� ���� ����
    // -> �� �Ѿ���(��ü��) �̱��Ͽ� ������ �ǰڳ�?

    // -> �� �Ѿ��� �̱��Ͽ� ���ٸ�, ����?
    // -> �ĺ����� ���� ������ �ִµ�, �� �� ù ��°�� �ٷ� ��ü �� �� ��ü (TextureScene.h)
    // -> ���� ������ ���� ����, ȣ���� �׶��׶� �ٸ� ���(ȣ����->�̱���)�� ���� �� �ƴ϶�
    // -> ���̶�� ���� ���������� �� �ɷ����� ���ʴ�� ȣ��Ǿ� ���� �����
    // -> Ƣ�� ������ ���ǹ��ϰ� ���� ���� �ְ�, ������ �ȵǴ� ������ �ذ��� �ȴ�

    // -> ������ �� ��ü�� ����� �����Ѵٴ� ������ �ִ�
    // -> ���� �ٲ� ���, �ű⿡�� �Ȱ��� ������ �� �������� �Ѵٴ� �� (�� �׷��� �� �ٲ� �� ���� �Ѿ��� ����)

    // -> ���� ������ �غ��ϸ鼭, ������ �ذ��ϴ� �ٸ� �ĺ����� �ϳ� �� �ִ�
    // -> �ٷ� �� ��ü

    // ���� �ڵ��� �˷��ִ� ��� : �ڵ�� ���� �߿��ϰ�, ȣ���� ���� ��Ȳ�� �߿��ϴ�
    //                           ȣ���� ��Ű�� �´� �ڵ嵵 ������ �� �Ǵ� Ʋ�� �ڵ�� �ٲ��
    //                           Ư�� ��Ƽ�ھ� ��Ƽ������ ȯ�濡�� �̷� �κ��� ����

    // �׷���, ���� ������ ȣ���ϸ� �� �Ǵ� �����Ͱ� �ִٸ�, �ǵ��� ���� �����ڸ� ������ �� �ֵ���
    // ����̳� ��� ���� ���踦 �������ָ�, ������ ��������. ��ſ� ������ �ʾҴ� ����� ���ǹ��ϰ� ���� �� �ִ�.
    // -> ��ǥ���� ���� ���� �Ѿ�, ���� ���, ���� �ʻ��.... ��

    // �׷���, �� ��ü�� �ڱ� �����͸� ���� ������ �ȴٸ�, ~~~ �Ŵ����� �׷� �� �ֳ�????

    // �׷��� �Ŵ����� ������ ���� ���� �� :
    // 1. �ܺ� ������ �������� (�� �����ӿ�ũ�� ���ӸŴ���) -> �� �� ����� ���� �ܰ�� �� �Ű澲�� ���� �� �ִ�
    // 2. �� ��� �Ϳ��� �ұ��ϰ� ���� ���� ���� �Լ��� �ʿ��� �� �ֱ� ������ (�� : �ϰ�����, ����...)

    for (Enemy* enemy : EnemyManager::Get()->GetEnemies())
    {
        for (Bullet* bullet : enemy->GetBullets())
        {
            Vector2 overlap = { 0, 0 };
            if (collider->IsRectCollision((RectCollider*)bullet->GetCollider(), &overlap))
            {
                // �浹�� ���� ��ũ!
                // Audio::Get()->Play("Bonk"); // ����� ���� -> �׷��� �Ҹ��� �ʹ� �ٴٴٴ�

                //�Ѿ��� �ε�ġ�� �������
                //bullet->Active() = false;
                //bullet->GetCollider()->Active() = false;

                // �Ѿ��� �ݻ�Ǵ� ���� ȣ���Ѵ�
                bullet->ReflectByVector( (RectCollider*)collider, &overlap);
                //bullet->Reverse();
            }
        }
    }
}
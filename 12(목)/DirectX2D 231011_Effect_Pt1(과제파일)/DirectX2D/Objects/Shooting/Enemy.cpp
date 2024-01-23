#include "Framework.h"

Enemy::Enemy() : Quad(L"Textures/Shooting/rectEnemy.png")
{
    tag = "Enemy";
    
    collider = new RectCollider(texture->GetSize());
    collider->SetParent(this);

    bullets.resize(16); // <- 16������ 10H

    for (Bullet*& bullet : bullets)
        bullet = new Bullet(L"Textures/Shooting/triEnemy.png");

    BulletManager::Get()->RegisterEnemyBullet(&bullets); //��ü������ �Ŵ����� ���
}

Enemy::~Enemy()
{
    delete collider;

    //������ �Ŵ����� �ϰ����հ�����...
    //for (Bullet* bullet : bullets)
    //    delete bullet;
}

void Enemy::Update()
{
    //�Ѿ��� �޾Ƽ� �ݺ������� �˻�
    //for (Bullet* bullet : BulletManager::Get()->GetBullets())
    //{
    //    //�Ѿ��� �ε�ĥ ��� �浹 ������ �����ϴ� �Լ� ȣ��
    //    Collision((RectCollider*)bullet->GetCollider()); // �������̽��� ��ȯ�� �Ѿ��� ���� �ݶ��̴��� �簢������ ����ȯ
    //    // (�� ���� ���� ����ȯ�� �ᱹ ���� ����� ������ �簢���� �� �ǹ̰� �ִ�)
    //}

    GameObject::Update();
    collider->Update();

    //�⺻�����δ� �ڱ� �Ѿ��� �ڱⰡ ����
    for (Bullet* bullet : bullets)
        bullet->Update();
}

void Enemy::Render()
{
    Quad::Render();
    collider->Render();

    for (Bullet* bullet : bullets)
        bullet->Render();
}

bool Enemy::Collision(RectCollider* target)
{
    Vector2 overlap = { 0, 0 };
    return collider->IsRectCollision(target, &overlap);
}

void Enemy::Respawn()
{
    localPosition = { Random(0.0f, (float)WIN_WIDTH), Random(0.0f, (float)WIN_HEIGHT) };
}

//�ڵ��̶� ������ "���"�̴ϸ�ŭ �ܺο��� ���ǿ� ���� ȣ�����ָ� �� ����
//�Ű������� ������ 'target'�� ������ ���� ���ָ� �� �����ϰ� �� �� �ִ�
// -> ���ʹ� �Ŵ������� ���� ����
void Enemy::Fire(Vector2 target)
{
    if (!isActive) return; //��Ȱ��ȭ �� �������� ���� (�����)

    cooldown -= DELTA; //��ٿ��� �ð��� ���߾� ������

    if (cooldown <= 0) //��ٿ��� �� ����
    {
        cooldown = interval; // ��ٿ��� ���� ���� ��ġ�� ����

        Vector2 direction = (target - localPosition).GetNormalized(); // ���� ���ϱ� (����ȭ �ʼ�)
        //BulletManager::Get()->Fire(localPosition, direction); // <-�� �ڵ带 ���� �ڱ� �Ѿ˿� �ڱⰡ �´´�

        //�ڱⰡ �� �Ѿ˿� �ڱⰡ �� �µ��� �ϴ� ���� ����� �ִ�
        // - ó������ �ڱⰡ �� ���� ������ �Ѿ��� ������ �Ѵ� (���������� �߿��ϰ� ���̴� ���ӿ��� ���� ���ϴ� ��ġ)
        // - �Ѿ� �ϳ��ϳ��� ID Ȥ�� ����� ���������� �༭ ���� �� ����ڿ��� ������ ���� ���ϰ� �Ѵ� (�߸��ϸ� ���� ���� ���� ���ӿ��� ���� ���ϴ� ��ġ)
        // - �׳� �ٸ� �Ѿ��� ��� �Ѵ� (������ ���� �״� �Ѿ˰� ������ ǥ���� �״� ���� ���� �����ؼ� ��� : 2D ���� ���ӿ��� ���� ����)
        //   + �� ���� ��� ����

        // ������ �� �� �� �� ��° ����� ����Ѵ�

        //BulletManager::Get()->EnemyFire(localPosition, direction); // �Ҹ��Ŵ����� ��ϵ� ��ü�� ������ ���� ���

        //�׳� �ڱ� �Ѿ˿��� ���� �ϳ� ��� ���
        for (Bullet* bullet : bullets)
        {
            if (!bullet->Active())
            {
                bullet->Fire(localPosition, direction);
                return;
            }
        }
    }
}
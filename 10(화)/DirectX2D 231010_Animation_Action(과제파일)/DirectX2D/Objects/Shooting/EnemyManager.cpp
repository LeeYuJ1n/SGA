#include "Framework.h"

EnemyManager::EnemyManager()
{
    enemies.resize(numberOfEnmemies);

    for (Enemy*& enemy : enemies)
    {
        enemy = new Enemy();
        enemy->Pos() = { Random(0.0f, (float)WIN_WIDTH),
                         Random(0.0f, (float)WIN_HEIGHT) };
    }
}

EnemyManager::~EnemyManager()
{
    for (Enemy* enemy : enemies)
        delete enemy;
}

void EnemyManager::Update()
{
    // �÷��̾� vs �Ѿ� �ڵ� ������ ���� �ܼ��� ���� :
    // -> �Ѿ��� ��������� ������ �ٷ� �浹�� ����

    //for (Bullet* bullet : BulletManager::Get()->GetEnemybullet())
    //{
    //    Vector2 overlap = { 0, 0 };
    //    if (bullet->GetCollider()->IsRectCollision((RectCollider*)target->GetCollider(), &overlap))
    //    {
    //        //���� �� �� : �÷��̾�κ��� �طο� ���� ������ �Լ��� ȣ��
    //        //            -> �÷��̾ �װų� �طο����� �Լ��� �ۿ� ������Ѿ� �Ѵٴ� �浵 �ȴ�
    //        //            -> �������� ���⿡ ���󼭴� �׷� ����� ��ȣ���� ���� ���� �ִ�
    //
    //        // �׷��ٸ�? -> �׳� �� �ڵ带 �÷��̾����� �����ص� ���� ������?
    //
    //        //���� �� �� : �Ѿ� ��������
    //        bullet->Active() = false;
    //        bullet->GetCollider()->Active() = false;
    //    }
    //}


    for (Enemy* enemy : enemies)
    {
        //������Ʈ�� �ϱ� ���� �浹 �˻�� ��� �Ѵ�
        for (Bullet* bullet : BulletManager::Get()->GetBullets())
        {
            //�浹������
            if (enemy->Collision( (RectCollider*)bullet->GetCollider() ))
            {
                //���� �� �� �װ� �ٸ� ������ ��Ȱ
                enemy->Respawn(); //�Լ� ȣ��� ����

                //�Ѿ� ��Ȱ��ȭ
                bullet->Active() = false;
                bullet->GetCollider()->Active() = false; // �ӽ� óġ�� �ݶ��̴��� �Ҹ� Ȱ��ȭ ���� ����ȭ
            }
        }
        
        // ���⼭ �÷��̾�� �浹���� �� �ڵ带 �����ص� �ȴ�
        if (target != nullptr &&
            enemy->Collision((RectCollider*)target->GetCollider()))
        {
            // �⺻ : �� �ڸ����� �÷��̾�� �طο� ����� ���ɴϴ�.

            // �׽�Ʈ�� : ���� �������մϴ�.
            enemy->Respawn();
        }


        // ��ݵ� ȣ��
        // ���� : '��� ����'��� �Լ��� �����, �� �Լ��� �θ���,
        //        �ٽ� �ű⼭ �÷��̾��� ǥ�� ������ �޾Ҿ��... �ϴµ�
        //        ���� �ڵ忡 ǥ���� ���� ������ �����Ƿ� �ٷ� �ᵵ �ǰڽ��ϴ�
        enemy->Fire(target->GlobalPos());

        //������� ���� �ε�ģ ���� �ִ� �簢���� �̹� ������ ������ �װ�
        // �浹�� �� �� ���鸸 ���� ��

        // �� ������ ������Ʈ
        enemy->Update();
    }
}

void EnemyManager::Render()
{
    for (Enemy* enemy : enemies)
        enemy->Render();
}
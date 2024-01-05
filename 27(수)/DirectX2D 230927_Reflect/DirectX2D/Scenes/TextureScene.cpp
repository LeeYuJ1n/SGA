#include "Framework.h"
#include "TextureScene.h"

// 27���� �ǽ� �� ����
// ���ݺ��� �ؼ�, �Ǹ� ���� �� �Ǹ� ������ ���ּŵ� �˴ϴ�.
// ���� ���ȿ� �ѹ� �����ð� �� ��ŭ ī�信 �÷��ּ���.

// 1. ���� : �浹���� ��, �Ѿ��� ���ݴ�� ���ư����� �غ��ô�.

// 2. �ﰢ�Լ� ���� : WINAPI���� ��� ������ ���� �ݻ縦 �ٽ� �� �� �Ế�ô�.
//                   XMConvertToDegrees : ���̷�Ʈx ���� �Լ�, �Ű������� ȣ���� ������ ������ ���ɴϴ�.
//                   XMConvertToRadians : ���� ��������, �Ű������� ������ ������ ȣ���� ���ɴϴ�.
//                   �� �� �Լ��� Ȱ���ϸ� ���� ������ ����� ���� �ʾƵ� ������ ȣ�� ����� �� �� �ֽ��ϴ�.

// 3. �Ѿ��� ��� ª�� �ð��� �ʹ� ���� ���� �Լ��� ȣ��Ǹ� Ȱ��ȭ�� ������
//    (Timer�� �߰� int���� ���� Ȱ��)

// 27���� ��¥ ���� : ��Ʈ������ � �������� ���� Ȯ���� �ƴϰ� ��ȹ��...
//                   ...�� ����, ���ް� ������ ��ǥ�ϱ� (�� ��ǥ�� �غ��ϱ�)
//                   �����̸� ������ � �������� �Ұ��ϰ�, �����̸� � ������ ������ ��ȹ�ϱ�


TextureScene::TextureScene()
{
    plane = new Plane();
    plane->Pos() = { CENTER_X,CENTER_Y }; //��� ��ġ����, �θ� ��� �۷ι�ó�� ��밡��

    //enemy = new Enemy();
    //EnemyManager::Get(); // �� �Ŵ��� ȣ�� (=�� ����)
    EnemyManager::Get()->SetTarget(plane); // ���� �ִ� ����⸦ ǥ������ ����

    sceneBullets.resize(30);

    for (Bullet*& bulletS : sceneBullets)
        bulletS = new Bullet(L"Textures/Shooting/triEnemy.png");

    BulletManager::Get()->RegisterSceneBullet(&sceneBullets);


    //�Ҹ��� ���
    Audio::Get()->Add("BGM", "Sounds/drumloop.wav", true); // ������� �ϼҸ��� ���
    Audio::Get()->Add("Bonk", "Sounds/Hit.wav"); //ȿ�������� ��ũ ��� (��ȯ ����)

    //��� �ٷ� ���
    Audio::Get()->Play("BGM", 0.8f); //"BGM"���� ����ߴ� �ϼҸ��� ���. �� ��° �Ű������� ����(����)
}

TextureScene::~TextureScene()
{
    delete plane;
    //delete enemy;
    EnemyManager::Delete();

    for (Bullet* bulletS : sceneBullets)
        delete bulletS;
}

void TextureScene::Update()
{   
    Audio::Get()->Update(); // �Ҹ� ������Ʈ

    plane->Update();
    //enemy->Update();
    EnemyManager::Get()->Update();
    BulletManager::Get()->Update();

    for (Bullet* bulletS : sceneBullets)
        bulletS->Update();
}

void TextureScene::Render()
{
    plane->Render();
    //enemy->Render();
    EnemyManager::Get()->Render();
    BulletManager::Get()->Render();

    for (Bullet* bulletS : sceneBullets)
        bulletS->Render();
}

//���̷�Ʈx���� ������ ������ �ɰ�� �� �Լ��� �δ��� ���̴� ����
//�� �Լ����� ����Ǵ� �Լ����� "ȭ�鿡 ���� ������ ���� ����" ������ ������ �͵��� ����
void TextureScene::PostRender()
{
    //�� : Ʈ������ ���� ���
    plane->RenderUI();
    //enemy->RenderUI();

}

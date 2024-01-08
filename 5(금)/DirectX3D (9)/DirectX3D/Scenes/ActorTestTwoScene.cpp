#include "Framework.h"
#include "ActorTestTwoScene.h"

ActorTestTwoScene::ActorTestTwoScene()
{
    BlockManager::Get()->CreateBlock(20, 20); // ȣ���� ���� ����

    player = new TestActor();
    player->UseBlockManager(true); // �ʿ�� �������� ���� �׽�Ʈ 1�� ���� ������ ���� �߰� �Լ�
                                   // ��� : ��� �Ŵ����� ����Ѵٰ� Ŭ������ �����ϱ�

    // ���� ī�޶� ���
    CAM->SetTarget(player);
    CAM->TargetOptionLoad("Follow");
}

ActorTestTwoScene::~ActorTestTwoScene()
{
    // �Ҹ��� : �� �����
    BlockManager::Delete(); // ��� �Ŵ����� ���⼭ �����
    delete player;
}

void ActorTestTwoScene::Update()
{
    BlockManager::Get()->Update();     // ��� ������Ʈ �θ���
    player->Update();                  // �÷��̾� ������Ʈ
    BlockManager::Get()->Push(player); // ���� �Լ��� �ǵ����� �ƴϾ����� ���� �����ߴ� ȣ��
                                       // Push : �� ��ü�� ( = �� �����)��ġ�ų� �������� �ε�ġ��
                                       //        ������ �ݴ�� �з������� �ϴ� �Լ�
                                       //        �׷��� �÷��̾ ��ü �浹ü�� �ֱ� ������ ���� ����
                                       //        = �÷��̾ ��Ͽ� �ε�ġ�� �з����� = �� ��ġ��
}

void ActorTestTwoScene::PreRender()
{

}

void ActorTestTwoScene::Render()
{
    BlockManager::Get()->Render();
    player->Render();
}

void ActorTestTwoScene::PostRender()
{
    player->PostRender();
}

void ActorTestTwoScene::GUIRender()
{
    player->GUIRender();
}
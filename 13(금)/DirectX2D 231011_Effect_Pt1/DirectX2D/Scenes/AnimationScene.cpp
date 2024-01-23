#include "Framework.h"
#include "AnimationScene.h"

// 11���� ���� : �������� C++ �ܼ� ��

// �ǽð� Ÿ�ڱ� (�����)

// 1. ���� Ÿ�ڸ� Ĩ�ϴ�.
// 2. ȭ�鿡 ���� ����� �������� ���ּ���
//    A. ù �ٿ��� ���� ���������� ģ Ÿ�� (���� Ȥ�� ���ڿ��� �մϴ�)
//    B. ���� �ٿ��� ���� ���ݱ��� ģ ��� Ÿ�ڰ� ���ʷ�

// (����)

// 1, b, 9, f�� ���� Ÿ�ڸ� �ƴٸ�

// ȭ�� ù�ٿ��� f��
// ���� �ٿ��� 1b9f��� ���ڰ� ���;� �մϴ�. (system("cls")�� �ݺ����� ���ּ���)
// * �Է��� cin getch ��� ���̵� �� �� �ֽ��ϴ�.
// * ����, ��, Ȥ�� ��Ʈ�� ��� ���̵� �����Ӱ� �Ἥ ����� ������ּ���.


AnimationScene::AnimationScene()
{
    CommandManager::Get();
    BulletManager::Get();

    ninja   = new Ninja();
    // testEff = new Effect(L"Textures/Effect/Fire.png", Vector2(3, 3), 1, false);

    // �Ŵ����� ���� ����Ʈ ���
    EffectManager::Get()->Add("explosion1", L"Textures/Effect/Explosion1.png", 4, 4);
    EffectManager::Get()->Add("explosion2", L"Textures/Effect/Explosion2.png", 4, 2);
    EffectManager::Get()->Add("fire", 10, L"Textures/Effect/Fire.png", 3, 3);

    // �ֵ�Ƽ���� a�� �ٿ��� �� �� �� ��� (�߰� ���� ü��)
    EffectManager::Get()->Add("explosion1a", L"Textures/Effect/Explosion1.png", 4, 4, 1, true);
    EffectManager::Get()->Add("explosion2a", L"Textures/Effect/Explosion2.png", 4, 2, 1, true);
    EffectManager::Get()->Add("fireA", 2, L"Textures/Effect/Fire.png", 3, 3, 1, true);

    EffectManager::Get()->SetColor("explosion1", 1, 0, 0);
    EffectManager::Get()->SetColor("explosion1a", 1, 0, 0);
}

AnimationScene::~AnimationScene()
{
    delete ninja;

    BulletManager::Delete();
}

void AnimationScene::Update()
{
    ninja->Update();

    // �Է����� ���
    if (KEY_DOWN('Q')) EffectManager::Get()->Play("explosion1", mousePos);
    if (KEY_DOWN('W')) EffectManager::Get()->Play("explosion2", mousePos);
    if (KEY_DOWN('E')) EffectManager::Get()->Play("fire", mousePos);

    if (KEY_DOWN('A')) EffectManager::Get()->Play("explosion1a", mousePos);
    if (KEY_DOWN('S')) EffectManager::Get()->Play("explosion2a", mousePos);
    if (KEY_DOWN('D')) EffectManager::Get()->Play("fireA", mousePos);

    CommandManager::Get()->Update();
    BulletManager::Get()->Update();
    EffectManager::Get()->Update();

    // //�׽�Ʈ �Է�
    // if (KEY_DOWN(VK_RETURN))
    // {
    //     testEff->Play(mousePos);
    // }
    // testEff->Update();
}

void AnimationScene::Render()
{
    ninja->Render();

    BulletManager::Get()->Render();
    EffectManager::Get()->Render();
    // testEff->Render();
}

void AnimationScene::PostRender()
{
}

void AnimationScene::Init()
{
}

void AnimationScene::Quit()
{
}
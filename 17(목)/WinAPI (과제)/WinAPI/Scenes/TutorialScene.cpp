#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    //�⺻ ����. ũ�⸦ �ָ� ȭ�鿡 ���´�
    rect = new Rect({ 0, 0 }, {200, 200});
    rect->Pos() = { (long)CENTER_X, (long)CENTER_Y };
    rect->Active() = true; //Ȱ��ȭ�� true�� ������ ���� �����ϸ� ���´�

    hBrush = CreateSolidBrush(RGB(0, 255, 0));


    //���� �غ���
    SpawnManager::Get()->spawnObjects.push_back(new SpawnObject()); //"������" �����
    SpawnManager::Get()->spawnObjects[0]->Spawn(); //������� �������� ���� ������ ����

    //1��
    SpawnManager::Get()->spawnObjects.push_back(new SpawnObject());
    SpawnManager::Get()->spawnObjects[1]->Spawn();

    //2��
    SpawnManager::Get()->spawnObjects.push_back(new SpawnObject());
    SpawnManager::Get()->spawnObjects[2]->Spawn();
}

TutorialScene::~TutorialScene()
{
    delete rect;

    DeleteObject(hBrush);
}

void TutorialScene::Update()
{
    int width = WIN_WIDTH;
    int height = WIN_HEIGHT;

    if (GetAsyncKeyState(VK_RIGHT)) // �⺻ Ű���� �Է� �ޱ� (�����Լ� ���)
    {
        rect->Pos().x += speed;

        if (rect->Pos().x > width - rect->GetSize().x / 2)
            rect->Pos().x = width - rect->GetSize().x / 2;
    }
    if (KEY_DOWN(VK_LEFT)) //Ű�� ������ �� �� ����
    {
        rect->Pos().x -= speed;
        if (rect->Pos().x < rect->GetSize().x / 2)
            rect->Pos().x = rect->GetSize().x / 2;
    }
    if (KEY_UP(VK_UP)) //Ű�� �����ٰ�, �� �� �� �� ����
    {
        rect->Pos().y -= speed;
        if (rect->Pos().y < rect->GetSize().y / 2)
            rect->Pos().y = rect->GetSize().y / 2;
    }
    if (KEY_PRESS(VK_DOWN)) //Ű�� ������ ���� ��� ���� (������ ����)
    {
        rect->Pos().y += speed;

        if (rect->Pos().y > height - rect->GetSize().y / 2)
            rect->Pos().y = height - rect->GetSize().y / 2;
    }

    // Ű�� ������ Ȱ��ȭ�� �ٲ��?
    if (GetAsyncKeyState('1'))
        rect->Active() = true;
    if (GetAsyncKeyState('2'))
        rect->Active() = false;

    if (KEY_DOWN(VK_LBUTTON)) // VK_LBUTTON : "���� ��ư" = ��Ŭ��
    {
        toggle = !toggle; //��� ����
        rect->Active() = toggle;
    }
}

void TutorialScene::Render(HDC hdc)
{
    SelectObject(hdc, hBrush);
    rect->Render(hdc);
    //���߿��� ���ο� ������ �׸��ٸ�
    //���� �׸� ���� ������... �׳� ���ӿ� ������Ʈ�� �����ͼ�
    //������Ʈ->Render() �̷��� �ص� �ȴٴ� ��

    //���� �����Ϳ� ���� ������ ��ü�� ����
    SpawnManager::Get()->spawnObjects[0]->Render(hdc);
    SpawnManager::Get()->spawnObjects[1]->Render(hdc);
    SpawnManager::Get()->spawnObjects[2]->Render(hdc);
}

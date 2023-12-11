#include "Framework.h"
#include "SpawnBrute.h"

SpawnBrute::SpawnBrute()
{
    srand(GetTickCount64());

    // �⺻ ����. ũ�⸦ �ָ� ȭ�鿡 ���´�
    rect = new Rect(Vector2(), Vector2(20, 20));
    rect->Pos() = { (long)CENTER_X, (long)CENTER_Y };
    rect->Active() = true; // Ȱ��ȭ�� true�� ������ ���� �����ϸ� ���´�

    hBrush = CreateSolidBrush(RGB(0, 255, 0));
}

SpawnBrute::~SpawnBrute()
{
    delete rect;

    DeleteObject(hBrush);
}

void SpawnBrute::Update()
{
    int width = WIN_WIDTH;
    int height = WIN_HEIGHT;

    // ���콺�� �� ���� �簢����(��Ʈ��) ����ٳ��!
    rect->Pos() = mousePos; // ���콺 ��ġ�� �簢�� ��ġ�� �ް�

    // ��Ŭ���� ���� ��
    if (KEY_DOWN(VK_LBUTTON)) // ���콺 ���� ��ư�� ������
        // * ��Ȯ�� ���ϸ� LBUTTON�� ��¥�� �ǹ��ϴ� ��
        //   = ���콺�� "�� ��ư" (���� ��ư, 0�� ��ư)
        //   = ���콺�� �� '��'(=0��) ��ư�� ���ʿ� �־ ���� ��ư�̶�� ����ϴ� ��
        //   = �׷�s�� ���콺�� "�������� ��ġ"�� ������ �� �ص� �ɱ��?
    {
        // ������� �����غ��ô�
        SpawnManager::Get()->spawnObjects.push_back(new SpawnObject()); // �� ��ü �߰�
        SpawnManager::Get()->spawnObjects[SpawnManager::Get()->spawnObjects.size() - 1]->Spawn();
    }
    // * ���콺 �� ��ư�� "���� ��ư"�̶�� ����ϴ� �Ϳ��� �� ���� �ǹ̰� �ֽ��ϴ�
    //   1. �Է� �ϵ��� �ٸ��ٰ� ������ ��(��ġ ��ũ��) ���� �Ȱ��� ��ȣ�� �� �� ������
    //      ���콺 ��Ŭ���� �Ȱ��� ������ �����ų �� �ֽ��ϴ�
    //   2. �޼����� ���α׷��Ӱ� �ڵ��� �ϴ���, �ڵ��� �������������� ������� �մϴ�

    for (int i = 0; i < SpawnManager::Get()->spawnObjects.size(); ++i)
    {
        if (SpawnManager::Get()->spawnObjects[i]->IsCollision(rect)) // �ε�ġ��
        {
            SpawnManager::Get()->spawnObjects[i]->Destroy(); // �ı�����
            // �� �Լ��� �θ��� ȭ�鿡�� ������ �簢���� �������ϴ�

            // ������ ���� �Ҵ�� ��ҵ� (�ڱ� ����)�� �޸𸮿��� ���������� �ʾƿ�

            // �׷��� �� ���� �Ҵ�� ��ұ��� ��� ����� ���ؼ� �߰� �ڵ�
            SpawnObject* toDelete = SpawnManager::Get()->spawnObjects[i]; // ������ ������Ʈ�� �ּ� �ޱ�
            SpawnManager::Get()->spawnObjects.erase(SpawnManager::Get()->spawnObjects.begin() + i); // ���Ϳ��� ��� ����
            delete toDelete; // �̸� �޾Ƶξ��� �ּҸ� ����(���� ������ ���·� ��ȯ)

            // �� �� �ٱ��� �����ϸ� �簢���� �����ϰ� �������ϴ�
        }
    }
}

void SpawnBrute::Render(HDC hdc)
{
    SpawnManager::Get()->Render(hdc);
    rect->Render(hdc);
}

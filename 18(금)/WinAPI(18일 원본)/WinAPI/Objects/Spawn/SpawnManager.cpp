#include "Framework.h"

SpawnManager::SpawnManager()
{
    spawnObjects.resize(POOL_SIZE);
    for (SpawnObject*& spawnObject : spawnObjects)
        // �� �ݺ����� for�� ���� ������ ���������� �ۿ��� �ٸ� �ݺ���
    {
        spawnObject = new SpawnObject();
    }

    // �� for each : for (A : B)��� �ϸ� "B�� �����ϴ� A����"��� ��
    //   �� �ݺ����� �迭 ���� �ڷᱸ���� ��Ȯ�� ������� �ϰ� 
    //     ���� �ڷᱸ�� �ȿ��� ��� ��ҵ���(���Ұ�) �Ȱ��� �Ӽ��� �Ȱ��� ������ ���� ��
    //     �׷� �� �Ẽ �� �ִ� ����

    // �� ���� ����� �������� ���µ�, ��Ȯ�� ������ ������� �ٷ����� �ʴ� ����
    //   �� �� �ݺ����� ������ ��Ȯ�� ����� ������ �Ǿ�� �ϰ�
    //     �ȿ� �ִ� ���ҵ� ������ ��Ȯ�ؾ� �ϰ�
    //     ���������� ������

    // �� �׷����� �ұ��ϰ� �� ������? �� �����ϴ���?
    //   �� ������ ������ �ڵ尡 ���������ϱ�
    //   �� ������ ���� �´� ��Ȳ������ �����ؼ��� ������ �� ���ϱ�
}

SpawnManager::~SpawnManager()
{
    for (SpawnObject* spawnObject : spawnObjects)
        delete spawnObject;
}

// ���� �Ŵ����� �ϴ� ��
// 1. ��� ���� �簢���� ���⼭�� ������ �����
// 2. �׷��� ����� �������� ����� �ƴϱ�?
//    �� "�Ҵ� �� ���"(control after allocation)�� ���

// �Ҵ� �� ���� ��� : ��������� �� ���� �̸����� ���س��´�
//                  : �׸��� �� �ȿ����� ������ �����Ѵ�

// �� ����� �� �� �迭�� ��������� �׳� �װɷ� ��(��ǻ� �����迭)
// ���� ����������� �ʰ�, ���������� �ʴ´�

void SpawnManager::Update()
{
    // ���� �Լ��� �־��� : ��Ŭ�� �� �Ͼ ��
    if(KEY_DOWN(VK_LBUTTON))
    {
        // ���� �� ��� �簢������ 
        for (SpawnObject* spawnObjecct : spawnObjects)
        {
            // Ȱ��ȭ�� �ƴϾ��ٸ�
            if (!spawnObjecct->Active())
            {
                // �����϶�(+Ȱ��ȭ�϶�?)
                spawnObjecct->Spawn();
                playTime = 0.0f;
                break;

                // �� �ڵ�� ������ ���ϸ� �簢�� "����"�� �ƴմϴ�
                // �̹� ������� �簢���� ���� ���̰� ���ִ� �� ��
            }
        }
    }
    
    // ��� ������Ʈ�� ������Ʈ�϶�
    for (SpawnObject* spawnObjecct : spawnObjects)
    {
        // �ڱ� ������ �ڱⰡ �˾Ƽ� �϶�
        spawnObjecct->Update();
    }
}

void SpawnManager::Render(HDC hdc)
{
    for (SpawnObject* spawnObjecct : spawnObjects)
    {
        spawnObjecct->Render(hdc);
    }

    wstring scoreText = L"Score : " + to_wstring(score);
    TextOut(hdc, (int)CENTER_X, 0, scoreText.c_str(),
        (int)scoreText.size());
}

void SpawnManager::DestoryObject(Vector2 point)
{
    for (SpawnObject* spawnObject : spawnObjects)
    {
        if (spawnObject->IsCollision(point))
        {
            spawnObject->Destroy();
            score++;
            return;
        }
    }
}

void SpawnManager::DestoryObject(Rect* rect)
{
    for (SpawnObject* spawnObject : spawnObjects)
    {
        if (spawnObject->IsCollision(rect))
        {
            spawnObject->Destroy();
            score++;
            return;
        }
    }
}

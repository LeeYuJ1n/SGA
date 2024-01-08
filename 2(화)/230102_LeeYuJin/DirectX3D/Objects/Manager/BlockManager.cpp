#include "Framework.h"

BlockManager::~BlockManager()
{
    for (Cube* block : blocks)
        delete block; // ��� ��ġ �����

    blocks.clear(); // ��� ����Ʈ �����
}

void BlockManager::Update()
{
    for (Cube* block : blocks)
        block->Update();
}

void BlockManager::Render()
{
    for (Cube* block : blocks)
        block->Render();
}

void BlockManager::CreateBlock(UINT width, UINT height)
{
    vector<wstring> textures; //����� ����, Ȥ�� �����ϱ� ���� ����(=�ؽ�ó)�� ����
    textures.resize(5); // �ؽ�ó ������ ũ�� ���ϱ� (���ڴ� ���� �ٶ�� ��� ����)

    //���� ���Ϳ� �ؽ�ó ������ ��� (�ؽ�ó �� ��ü�� �ƴ�)
    for (int i = 0; i < textures.size(); ++i)
    {
        textures[i] = L"Textures/Block/block" + to_wstring(i) + L".png";
    }

    //������� �ؽ�ó ����(���� �̸�)�� �̿��ؼ� ť�� �����
    for (int z = 0; z < height; ++z)
    {
        for (int x = 0; x < width; ++x)
        {
            Vector3 pos = { (float)x, 0, (float)z };
            wstring file = textures[Random(0, textures.size())];

            Cube* block = new Cube(); // ť�� ����
            block->GetMaterial()->SetDiffuseMap(file); //������ ã�� �ؽ�ó ���ϸ� ����
            block->Pos() = pos; // ������ ���� ��ġ�� ����
            block->Update(); //������Ʈ 1ȸ

            blocks.push_back(block); // ��� ����Ʈ�� ���� ���� ť�� �߰�
        }
    }
}

bool BlockManager::BuildBlock(Cube* block)
{
    // ����
    Ray ray = CAM->ScreenPointToRay(Vector3(CENTER_X, CENTER_Y));

    // �浹 ����
    float minDistance = FLT_MAX;
    Contact contact;
    Vector3 hit;

    // �ݺ��ڿ� �浹��� �ʱ�ȭ
    list<Cube*>::iterator it = blocks.begin();
    Cube* collidBlock = nullptr;

    for (it; it != blocks.end(); ++it)
    {
        if ((*it)->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance)
            {
                minDistance = contact.distance;
                hit = contact.hit;
                collidBlock = *it;
            }
        }
    }

    // �浹�� ����� ������ �����ϰ� false ��ȯ
    if (collidBlock == nullptr) return false;

    // ������� ���� �浹�� ����� �־���

    // �ش� ����� ���� �߰� ���� ����

    // ���⵵�� (�浹�� ������� ���� ����)
    Vector3 dir = hit - collidBlock->GlobalPos();

    int maxIndex = 0;
    float maxValue = 0;

    for (int i = 0; i < 3; ++i)
    {
        //�� �� ������ �ٸ� �� ���⺸�� �� ũ��
        if (abs(dir[i] > maxValue))
        {
            maxIndex = i;
            maxValue = abs(dir[i]); // �ش� �� ����
        }
    }

    //���� ���� �� ������ �������� �ٽ� ����ġ��
    switch (maxIndex)
    {
    case 0:
        dir.x = dir.x > 0 ? 1 : -1;
        dir.y = 0;
        dir.z = 0;
        break;

    case 1:
        dir.x = 0;
        dir.y = dir.y > 0 ? 1 : -1;
        dir.z = 0;
        break;

    case 2:
        dir.x = 0;
        dir.y = 0;
        dir.z = dir.z > 0 ? 1 : -1;
        break;
    }

    // ������� ���� ���� ���⿡ ���߾ "����, �¿�, ����" �� �ϳ��� ������ ���´�
    // �� ���⿡ �߰��� ����� ������ְų�(����) �ٸ� �繰�� �ٿ��ָ� �ȴ�

    // ���� : ����� ��Ȱ��ȭ�Ǿ��ٰ� ġ��, Ȱ��ȭ�� ��(��Ÿ�� ��) ����Ʈ�� �߰��Ǵ� �ڵ带 �ۼ�
    // TODO : ��ȣ�ۿ��� �ٸ��� ��������ų� ����Ǹ� �Ʒ����� ����, �ۼ�
    // Ȥ�� : �ٷ� �Ʒ� Push�� ���⼭ ���� �͵� ��¼�� ����

    block->SetActive(true); // ��򰡿��� ��Ȱ��ȭ�� ����� �ִٰ� ġ�� ���⼭ "�����"
    block->Pos() = collidBlock->GlobalPos() + dir; // ���� ��ȣ�ۿ��� "��ġ" ��Ͽ��� ������ ���� dir��ŭ �񲸳��� ��ġ
    block->Update();

    blocks.push_back(block); // "��" ��� �߰�

    return true;
}

void BlockManager::Push(Collider* collider)
{
    // ��ȣ�ۿ��ϸ� �о ���⿡ ���� ����� XYZ �⺻ �������� ����� �����̰� �غ���

    Cube* collidBlock = nullptr;

    for (Cube* block : blocks)
    {
        //�� ��ϳ��� �ε�ģ�ٸ�
        if (block->GetCollider()->IsCollision(collider))
        {
            collidBlock = block;

            Vector3 dir = collider->GlobalPos() - collidBlock->GlobalPos();

            int maxIndex = 0;
            float maxValue = 0;

            for (int i = 0; i < 3; ++i)
            {
                if (abs(dir[i] > maxValue))
                {
                    maxIndex = i;
                    maxValue = abs(dir[i]);
                }
            }

            switch (maxIndex)
            {
            case 0:
                dir.x = dir.x > 0 ? 1 : -1;
                dir.y = 0;
                dir.z = 0;
                break;

            case 1:
                dir.x = 0;
                dir.y = dir.y > 0 ? 1 : -1;
                dir.z = 0;
                break;

            case 2:
                dir.x = 0;
                dir.y = 0;
                dir.z = dir.z > 0 ? 1 : -1;
                break;
            }

            if (NearlyEqual(dir.y, 1)) continue; // ���� ���δ� ���� �ʰ� = �ھƳ����� �ʰ�

            collider->GetParent()->Pos() += dir * 50.0f * DELTA; //  �ε�ģ ��� ť�갡 �ش� �������� �з�����
        }
    }
}

Cube* BlockManager::GetCollisionBlock()
{
    // ȭ�� �߾ӿ��� ������ ���� ���� (�� 1��Ī�̳� �ʱ� 3��Īó�� �÷��̾� ���忡�� ��ȣ�ۿ�)
    Ray ray = CAM->ScreenPointToRay(Vector3(CENTER_X, CENTER_Y));
    // �ı� 3��Ī ����ó�� ������ ������ �ʿ��ϸ� ���� �� ������ ������ ������ �����ϸ� �ȴ�

    float minDistance = FLT_MAX; // �ּҰŸ� �ʱ�ȭ
    Contact contact;

    list<Cube*>::iterator it = blocks.begin();        // �����鼭 �˻��� ����
    list<Cube*>::iterator collidBlock = blocks.end(); // �ּҰŸ�ó�� �������� �ݺ��� �Ѱ�

    for (/*���� ���� ����, ���� ���� �ݺ��� ���*/;
        it != blocks.end();
        ++it)
    {
        if ((*it)->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance) // �浹�� �Ͼ�µ� �ּҰŸ��� �����Ѵٸ�
            {
                minDistance = contact.distance; // ���� �� �ݿ�
                collidBlock = it; // �浹�� ����� it�� ����
            }
        }
    }

    if (collidBlock != blocks.end()) // ���ŵ� "�浹 ���"�� ���� �ʱ�ȭ�ߴ� ����(�Ѱ�) ���̶��
    {
        //�ش� ����� �ݿ�, ���
        Cube* block = *collidBlock;

        //TODO : ���� �� ��Ͽ� ��ȣ�ۿ��� �ʿ��ϸ� ���⼭ �߰� �ۼ�

        return block; // �ش� ����� ��ǻ�Ϳ��� ��ȯ
    }
    else
    {
        //������� ������ collidBlock�� ��� ����Ʈ�� �� = �Ѱ� �� = �浹�� ť�� ������
        return nullptr;
    }
}

float BlockManager::GetHeight(Vector3& pos)
{
    // ���� �ٴ��� �� ����� ����

    Ray ray(pos, Vector3::Down());

    Contact contact; // ������ ��ü�� �浹 ����� ������ ��

    float maxHeight = 0; // �ͷ����� �ּҳ��̸� ����� "�ٴ�" ������ ���� �ʱ�ȭ

    for (Cube* block : blocks)
    {
        if (block->GetCollider()->IsRayCollision(ray, &contact))
        {
            //�� ������ ������ ������ �ٴڿ� �ε��ƴ� = ������ �߽��� �Ǵ� � ���� �ٴ��� "��"�� �ִ�

            if (contact.hit.y > maxHeight) // �浹�� ���� �� ���̰� ���� ���� �ٴں��� ������
            {
                maxHeight = contact.hit.y; // �� ����
            }
        }
    }

    // ������� ���� �ٴ� ���� ���� ��� �ٴ��� ���̰�
    // �׷��� ������ �ʱ�ȭ�� ������ 0�� ���´�

    //��ȯ
    return maxHeight;
}
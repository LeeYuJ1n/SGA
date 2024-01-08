#include "Framework.h"

ActorUI::ActorUI()
{
    //���� 3��
    crosshair = new Quad(L"Textures/UI/cursor.png");
    crosshair->Pos() = { CENTER_X, CENTER_Y, 0 };
    crosshair->UpdateWorld();

    quickSlot = new Quad(L"Textures/UI/QuickSlot.png");
    quickSlot->SetTag("QuickSlot"); // Ʈ�������� �̸��� ���ϱ�
    quickSlot->Load();              // 2D �� �ʷ��� ���� �ҷ��� ��ó��, ���̳ʸ� ���� Ŭ������ ����Ͽ�,
                                    // ��ġ, ȸ��, ũ�� ������ ������ ���Ͽ��� �о���δ�
    quickSlot->UpdateWorld();       // ������Ʈ

    iconFrame = new Quad(L"Textures/UI/IconFrame.png"); // �������� "������" = �׸��� �ҷ��� �� �ڸ��� �Ǿ��ְų�
                                                        // �κ��丮 ���� �����̶�� "Ŀ��"�� ������ �ϰų�
                                                        // -> �ٸ� �׸��� ���� ���̰ų�, ������ �ޱ� ���� ���ҽ���
                                                        // ���� ���������� ��ġ�� ������ �ʿ�� ����
    //iconFrame->Scale() = { 0.7f, 0.7f, 0.7f }; // ���� ũ�� ����
    iconFrame->Scale() *= 0.7f;                  // ��� ũ�� ���� (ó�� ũ�⿡�� 70%)
    iconFrame->SetActive(false);                 // ���� ���������� �� �ʿ䰡 �����ϱ� (�ٸ� �׸��� ���� ���ų�, ���� �޴� Ŀ���� ���ų�)

    // ����� �����ܵ� ���� �����
    // (���ӿ� �������� ���´ٸ� �������� �����ܵ� �̷� ������)

    for (int i = 0; i < 5; ++i) // �ݺ�Ƚ�� 5 = ����� ����
    {
        wstring file = L"Textures/Block/BlockIcon" + to_wstring(i) + L".png"; // ��� �������� ���� ������ ��Ʈ������ �����
        Quad* blockIcon = new Quad(file);
        blockIcon->Scale() *= 0.1f; // ���� ũ�⿡�� 10%
        blockIcon->SetParent(quickSlot); // �κ��丮 ���ٸ� �θ� Ʈ����������
        blockIcon->SetTag("Icon " + to_string(i));

        blockIcons.push_back(blockIcon); // ���� ��� ������ �ֱ�

        //blockIcon->SetActive(false); // ���۽� ������ ǥ�� �� ��
    }
}

ActorUI::~ActorUI()
{
    delete crosshair;
    delete quickSlot;
    delete iconFrame;

    for (Quad* blockIcon : blockIcons)
        delete blockIcon;
}

void ActorUI::Update()
{
    if (KEY_DOWN('1')) // 1�� ������
    {
        if (iconData[0].second > 0) // ����� �����Ͱ� ���� �ִٸ�
            selectIconIndex = 0; // �ش� ��� �����ϱ�
    }

    if (KEY_DOWN('2'))
    {
        if (iconData[1].second > 0)
            selectIconIndex = 1;
    }

    if (KEY_DOWN('3'))
    {
        if (iconData[2].second > 0)
            selectIconIndex = 2;
    }

    if (KEY_DOWN('4'))
    {
        if (iconData[3].second > 0)
            selectIconIndex = 3;
    }

    if (KEY_DOWN('5'))
    {
        if (iconData[4].second > 0)
            selectIconIndex = 4;
    }
}

void ActorUI::Render()
{
    // ������ ������Ʈ���� ���� -> ���߿� �ʿ��ϸ� ���� �߰��ϱ�
}

void ActorUI::PostRender()
{
    // * ���� ���ۿ� ���� �켱���� �����
    //   �̹����� ���� ���� �׷����� ���� �ش� �̹����� ��İ����� ��� �������� ��Ȥ
    //   �ڵ�� ���� �׷��� ���� "�ؿ�" �� ���� �ٽ� �ڿ� �׷����� ���� ���׷����鼭
    //   ���� �̹����� ���� ���� ������ �� �ְ� �ȴ�

    // * �� ������� ������ ���������� ����ȴ� (2D �̹������� ������ �� � �׸��� ���� ���°�?)

    // UI�μ� ���� ��� (UI���� ���)

    crosshair->Render(); // ������ ���⼭ ȣ��
    // quickSlot->Render(); // ���ٵ� ���� ȣ��

    for (int i = 0; i < 5; ++i)
    {
        Vector3 pos;
        pos.x = -80 + (20 * i);

        if (iconData[i].second) //���� �ݺ������� ���� �ִ� �������� ������...�� �ش��ϴ� ��¥ ��� �����͸� ���� ��
        {
            Quad* icon = blockIcons[iconData[i].first]; // �����ϴ� ������ ã��
            icon->Pos() = pos; // �� ������ ��ġ�� ���� ���� ���
            icon->UpdateWorld(); // ������Ʈ�� ���⼭ ���� (�����ܳ��� ��ġ�� �ٲ�ų� ǥ�� ���ΰ� �ٲ�� ��� ���)
            icon->Render(); // �׸��� ���� (* ������ ���� ������ ���� �׷��� �� �ְ� ��)

            string str = to_string(iconData[i].second); // ����� �����͸� ���ڿ���

            Vector3 tmp = icon->GlobalPos();

            Font::Get()->RenderText(str, {tmp.x, tmp.y}); // ������ ���� �������� ��ġ��, ����� �����͸� ���ڷ� ǥ��

            if (i == selectIconIndex) // �ݺ����� ���� ���� �������� �����͸� ���� �ִٸ� (="�� ��� ���� ��")
            {
                // �׸��� �����ǵ�, Ŀ���� ������, �ش� "�ڸ�"�� ǥ���ϱ� ����....
                // ������ ���带 ����� ����

                iconFrame->SetActive(true); // Ȱ��ȭ
                iconFrame->Pos() = icon->GlobalPos(); // ��ġ = ������ �������� ��ġ
                iconFrame->UpdateWorld(); //������Ʈ
                iconFrame->Render(); //����
            }
            else
            {
                iconFrame->SetActive(false); // ��Ȱ��ȭ
            }
        }
    }
}

void ActorUI::GUIRender()
{
    // �������� ������ ��ġ ��Ÿ����
    iconFrame->RenderUI();
}

void ActorUI::Pick()
{
    //��� ����

    Cube* block = BlockManager::Get()->GetCollisionBlock(); // ������ ���� �浹�� = ���õ� ���

    if (block == nullptr) return; // ����� �� ������ �׳� ����

    //������ �������� ����

    // �ؽ�ó ���� �̸� �޾ƿ���
    wstring file = block->GetMaterial()->GetDiffuseMap()->GetFile();

    int tmp = file.find_last_of('.'); // ���� ���ڿ��� �߸� ������ �������� ������ ������ ��������
    file = file.substr(tmp - 1, 1);   // ������ ������ �����͸� �������� �ؼ� �� ���� = ������ ����
    int index = stoi(file);

    if (inventory[index].size() == 0) // �κ��丮�� ��� ���� ������ 0�̶�� = �κ��丮�� ����� ��������
    {
        for (int i = 0; i < 5; ++i)
        {
            if (iconData[i].second == 0) // ��� ������ ��������
            {
                //ó������ �ֱ�
                iconData[i].first = index; //�� ����� �����ܿ� ����
                iconData[i].second++; // ���� +1
                break; //�ݺ�����
            }
        }
    }
    else // �κ��丮�� ���빰�� �ִ� ��Ȳ�̸�
    {
        //�ݺ��� ������ ��ġ�ϴ� ��Ͽ� +1
        for (auto& data : iconData)
            // auto : �ƶ��� ���� �ڵ忡�� ������ �ڷ����� �ڵ����� �������ִ� ���
            //        ��Ȯ�� �ڷ����� ��ȣ�ϴ� C++ Ư���� �����ϸ� ������ ����...
            //        ����ó�� �ڷ����� �ʹ� �� �� (��, ��� ���� ���� ��, Ŭ���� ���谡 ������ ��)
            //        ���������� ���� ����� ���ϴ�
        {
            if (data.second.first == index) // ����� ������ ������
            {
                data.second.second++; // ����� ���� + 1
                break;
            }
        }
    }

    // ������� ���鼭 �ʿ� ����� ���� ���� (� ������ �� �� ������)�� �����ߴ�
    // �׷��Ƿ� ���� ��� = �����ͷ� ���� block�� �κ��丮�� ����

    inventory[index].push_back(block);

    // �̰ɷ� ���� ���� �Ϸ�(��) + ��ü�� ���Ϳ� ���� �Ϸ�(����)
    // -> �Ⱦ� ����

}

void ActorUI::Build()
{
    //���� ���� ������(���)���� ������ �ܺο� ����
    if (selectIconIndex < 0) return; // <- �ʱ�ȭ ������ "����"(=-1)���� �Է��� �� �ߴ� = �� ����� ������

    //�� ����� ������ �ϴ� �ϳ� ���� (������ ������ ����� ������ ���� ������ ��ü)
    Cube* block = inventory[iconData[selectIconIndex].first].back();

    if (BlockManager::Get()->BuildBlock(block))
        // ��� �Ŵ����� ȣ���ؼ�, "�� ����� �Ἥ ����"�� �ߴµ� ����� true = ������ �ƴٸ�
        // -> ���ʿ� ����� �����ų�, ȣ���� ������ ������ ���� ��ϰ� �浹�� �� �� ������ �������� false
    {
        // ���Ϳ��� ��� ���� (����� �����Ƿ� �κ��丮���� ���� Ÿ�̹�)
        inventory[iconData[selectIconIndex].first].pop_back();

        iconData[selectIconIndex].second--; // ��� �������� -1

        if (iconData[selectIconIndex].second == 0) // ��� ������ 0�� �ٴٸ���
        {
            selectIconIndex = -1; // ���� ����ϱ�
        }
    }
}
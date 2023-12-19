#include "Framework.h"
#include "TileScene.h"

TileScene::TileScene()
{
    //���� ����� ȣ��
    CreateSamples();

    editor = new EditTileMap(10, 10); // ������ ����
    editor->Pos() = { 80, 80 };

    //���� ���õ� ������ �⺻ ����("������ �� �Ǿ��� ���� ����")
    // -> �������¸� �̸� �ְ� ���߿� �ؽ�ó��簡 �ٸ� ������ �ٲٸ� �� �����ϱ�
    // -> (Ŭ���� �� �׶��׶� �ν��Ͻ��� ����ٴ� ���õ� ������ �ϴٴ� ��)

    selected = new Quad(sampleSize); // �׸��� �ƴ� ũ��� ���� �ϴ� �����

    char path[128];
    GetCurrentDirectoryA(sizeof(path), path);
    fullPath = path;
}

TileScene::~TileScene()
{
    delete selected;
    for (Button* button : samples)
        delete button;

    delete editor;
}

void TileScene::Update()
{
    // ����� ������ ��ɵ��� ���⼭ ����´�

    // 1. Ÿ���� Ŭ������ �� �Ͼ ��
    if (KEY_PRESS(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
    {
        if (selected->GetTexture())
        {
            editor->ClickTile(selected, selectedType);
        }
    }

    if (KEY_DOWN(VK_RBUTTON) && !ImGui::GetIO().WantCaptureMouse)
    {
        editor->DeleteObjTile();
    }

    // 2. (�ɼ�) ����Ʈ������ ���� ���� �� �� �� �ִ� Ű �Է��� ���� ȣ��
    if (KEY_DOWN(VK_F5))
        editor->Save("TextData/Test.map");

    if (KEY_DOWN(VK_F9))
        editor->Load("TextData/Test.map");

    //��ư�� Ÿ��(������) ������Ʈ

    for (Button* button : samples)
        button->Update();

    editor->Update();

    //���� ���õ� ������ �ִٸ�......

    if (selected->GetTexture() != nullptr)
    {
        // ���콺 �� �Է��� �� �� �� ��� Ȯ�� ������ ������ Ű�Է½�
        if (KEY_DOWN('Q'))
        {
            selected->Rot().z += XM_PIDIV2; //�������� ������ ���� 2�� ������? -> 90��!

            //������ 360�� ������ ������ �ǵ���
            if (selected->Rot().z > XM_2PI)
                //selected->Rot().z -= XM_2PI; // 360�� ���� (��ȯ)
                selected->Rot().z = XM_2PI; //360���� ���߱� (�ִ밪 ����)
        }

        if (KEY_DOWN('E'))
        {
            selected->Rot().z -= XM_PIDIV2;

            if (selected->Rot().z < 0)
                //selected->Rot().z += XM_2PI; // 360�� ���ϱ� (��ȯ)
                selected->Rot().z = 0.0f; //0���� ���߱� (�ּҰ� ����)
        }

        //���콺 �� �Է¿� ����.....
        if (mouseWheel > 0.0f)
        {
            // ���õ� ������ ȸ��!

            selected->Rot().z += XM_PIDIV2; //�������� ������ ���� 2�� ������? -> 90��!

            //������ 360�� ������ ������ �ǵ���
            if (selected->Rot().z > XM_2PI)
                //selected->Rot().z -= XM_2PI; // 360�� ���� (��ȯ)
                selected->Rot().z = XM_2PI; //360���� ���߱� (�ִ밪 ����)
        }
        else if (mouseWheel < 0.0f)
        {
            selected->Rot().z -= XM_PIDIV2;

            if (selected->Rot().z < 0)
                //selected->Rot().z += XM_2PI; // 360�� ���ϱ� (��ȯ)
                selected->Rot().z = 0.0f; //0���� ���߱� (�ּҰ� ����)
        }

        selected->Pos() = mousePos;
        selected->UpdateWorld();
    }
}

void TileScene::Render()
{
    for (Button* button : samples)
        button->Render();

    editor->Render();

    if (selected->GetTexture() != nullptr)
        selected->Render();
}

void TileScene::PostRender()
{
    const char* list[] = { "BG", "OBJ" };
    ImGui::ListBox("Type", (int*)&selectedType, list, 2);

    Save();
    Load();
}

void TileScene::ClickSample(void* sample)
{
    Button* button = (Button*)sample; // �Ű������� ��ư���� �ٽ� ����ȯ
    
    //���� ���õ� ��ư(�̶�� �̸��� ����) ������ Ŭ���� ��ư �������� �ٲٱ�
    selected->SetTexture(button->GetTexture()); //�ؽ�ó ��ü
}

void TileScene::CreateSamples()
{
    // ���� �ڵ鷯 �ӽ÷� ����� (ī�� ���� ��ó��)

    WIN32_FIND_DATA findData;
    HANDLE handle = FindFirstFile(L"Textures/Tile/*.png", &findData);

    bool result = true; // �� ���� �̸� true�� �ۼ�
    wstring filename;   // ���� �̸�

    UINT width = 10;
    Vector2 size(sampleSize); // ���� ũ�⵵ �����
    Vector2 startPos(WIN_WIDTH - size.x, WIN_HEIGHT - size.y); //���ظ�ŭ ������ �ְ� ����� (���� ����)

    while (result) // ������ ���� ������ ���� ����
    {
        filename = L"Textures/Tile/";
        filename += findData.cFileName;

        // ���� ������ �ִ°�? (������ ���, ������ bool �� false)
        result = FindNextFile(handle, &findData);

        //���� �̸� ����� ���� ���� ���� Ȯ��
        // -> ���⼭���ʹ� ����� ���� �̸����� ���� ã�� �ݿ��ϱ�

        //������ ���� �� ������� ����
        UINT index = samples.size(); // ���� ���� ���� ũ�� = ���� �� ����
                                     // �׻� ������ �������� ������

        //������ ���� �� ��ġ (�������� ��Ģ�� ��ġ)
        Vector2 pos(index % width, index / width); // 1�� ���͸� ���� ���η� ��Ÿ�� �� ���� ���� ���

        Button* button = new Button(size); //ũ��� ��ư �����
        button->SetTexture(filename); //ũ����� ����� ũ�⿡ �ؽ�ó ���߱�
        button->Pos() = startPos - (pos * size); // ���� ���� ���� - (������ ���� �� ��ǥ * ����ũ��)
        button->SetParamEvent(bind(&TileScene::ClickSample, this, placeholders::_1)); //�Ű����� �ִ� �Լ��� Ŭ�� �Լ� �Ҵ�
        button->SetObject(button); //���� ��� �ڱ� �ڽ� ���

        samples.push_back(button); //���Ϳ� ���� ��ư �߰��ϱ�
    }

    // ������� ���� ���Ϳ� ������ �� ���� ��
}

void TileScene::Save()
{
    if (ImGui::Button("Save"))
        ImGuiFileDialog::Instance()->OpenDialog("Save", "SaveFile", ".map", ".");

    if (ImGuiFileDialog::Instance()->Display("Save"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string file = ImGuiFileDialog::Instance()->GetFilePathName();
            file = file.substr(fullPath.length() + 1);

            editor->Save(file);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void TileScene::Load()
{
    if (ImGui::Button("Load"))
        ImGuiFileDialog::Instance()->OpenDialog("Load", "LoadFile", ".map", ".");

    if (ImGuiFileDialog::Instance()->Display("Load"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string file = ImGuiFileDialog::Instance()->GetFilePathName();
            file = file.substr(fullPath.length() + 1);

            editor->Load(file);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}
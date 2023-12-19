#pragma once

class TileScene : public Scene
{
public:

    TileScene();
    ~TileScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override; // ImGUI ��� ����

    //�߰��� �Լ� : �� ���̺� �ε�
    void Save();
    void Load();

private:

    EditTileMap* editor; // ������ Ŭ����
    vector<Button*> samples; // �����Ϳ��� �ҷ� ���� ���� �����ڷ��
    Quad* selected = nullptr; //���� ������ ���

    Vector2 sampleSize = { 50.0f, 50.0f };

    void ClickSample(void* sample); // ������ Ŭ������ ��
    void CreateSamples(); // ���� ó�� �����


    //ImGUI���� ���� ���� �͵�

    //Ÿ������(�� �ҷ�����)
    Tile::Type selectedType = Tile::BG;

    //��ü��θ�(�� �����ϱ� ���� ����)
    string fullPath;
};


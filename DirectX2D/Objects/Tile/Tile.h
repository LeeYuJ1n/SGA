#pragma once

class Tile : public Button
{
    // Ÿ�� : �ݺ������� ��Ƽ� ����̳� �ð��� ����� ����� ���� ���� ���

    // Ÿ���� ���� : ��� ������ ���� Ÿ���� �ϳ��ϳ� ������ �׷��� ����
    //              Ȥ��, �ڸ��� ������ �ְ�, �� �ڸ��� �Ӽ� ��Ҹ� ���������ν� �ǹ̸� ����

    // ��ư�� ��ӹ����鼭 �׸� ���, Ŭ���� ���� ��ȣ�ۿ��� ����޾Ҵ�

public:

    enum Type //�� Ÿ���� ���� �Ӽ�
    {
        BG, //=Background
        OBJ, //=Object
    };

    struct Data //�� Ÿ���� ���� ����
    {
        wstring textureFile;
        Vector2 pos;
        float angle = 0.0f; //������ ������ Ÿ�� �ϳ��� �ּ� �� �̻��� �ٸ� ����� �� ���� �־
        Type type = BG;     //�⺻ ������ ������� (�׼��̳� RPG ���� ����� OBJ�� �� ������ ����)
    };

    Tile(Data data); //���� �� �̹� �⺻ ������ �ʿ��� ��ŭ ����...
    ~Tile();

    void SetTexture(wstring file);
    void SetAngle(float angle);

    Data GetData() { return data; }

private:

    Data data;
};


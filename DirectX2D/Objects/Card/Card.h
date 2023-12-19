#pragma once

class Card : public Button
{
    // ��ư ����� Ȯ�� : Ŭ���� ��ȣ�ۿ� ������ 2D �繰 (���� ī�� ����)
    //                   ������ ī������ Ŭ���� �̸��� �ٲ�� "����" "������"���ε� ��� ����

public:
    Card(wstring textureFile);
    ~Card();

    void Update();
    void Render();

    //ī�忡 ����� ���� �ٸ� �Լ��� ������ �ۼ�
    
    //��ġ(��ǥ) ����, ����
    POINT GetCoord() { return coord; }
    void SetCoord(POINT coord) { this->coord = coord; }
    void SetCoord(int x, int y) { this->coord = { x, y }; }

    //���� ���� ���
    void Select(bool value) { isSelected = value; }

    //Ű �ޱ�
    wstring GetKey() { return key; }

private:
    void OnClick(); // Ŭ���ϸ� ������ �Լ� (�̺�Ʈ)

    //������ : ��ȣ �ۿ� ������, ���� ������, ��ư ����� ����, 2D ������Ʈ�� �ʿ��� �͵�

    //ī���� �̸�
    wstring key;

    //�� ī�带 ��ġ�� �Ϸ��Ƿ� ��ġ�� ���� ��ġ
    POINT coord; // coord : "�� ī��� ���簢������ ���� ī�峢�� ��ġ�� �Ű�, ����� ���¸� �� ���̴�"��� ����
                 // -> ī�带 ���ó�� ��ġ�� �� Ŭ���ϴ� ������ ���� ����

    IntValueBuffer* intBuffer;
    FloatValueBuffer* floatBuffer;
    ColorBuffer* colorBuffer;

    //�� ī�带 ���� ������ �߽��ϱ�?
    bool isSelected = false;
};


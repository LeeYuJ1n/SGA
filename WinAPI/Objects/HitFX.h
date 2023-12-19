#pragma once
class HitFX : public Rect
{
public:
    HitFX();
    HitFX(Vector2 pos, Vector2 size) :Rect(pos, size) {}
    HitFX(float left, float top, float right, float bottom)
        : Rect(left, top, right, bottom) {}

    //������ �Լ�
    void Start(Rect* source, bool isLeft)
    {
        //��ġ�� ���� (������� �����̺� �Լ��� �Ű������� �佺)
        SetPosition(source, isLeft);
        isActive = true;
    }

    //������Ʈ ȣ��� �Լ�
    void UpdateThis() //"������Ʈ"��� �̸��� ����, �ٸ� ������Ʈ�ʹ� �޶� "�����ƴ�"�� ���� ǥ��
    {
        if (isActive) currentTime += DELTA; //�����ð� ���ϱ�

        if (currentTime > timeSpan)
        {
            currentTime = 0; //�ð�����
            isActive = false;
        }
    }

private:

    float currentTime = 0; //���� �� FX�� ���� �ð�
    float timeSpan = 1;    //FX�� ���� "�ð��ֱ�" = �� span�� ���� �ð� ���� �����ϸ� ��ȭ�� �Ͼ��

    //active -> ��ӹ��� ���� �̿�

    //�Ȱ��� ��ġ ���������� �Ű������� ���� �ٸ�...
    void SetPosition(Rect* source, bool isLeft)
    {
        // ���� ��Ʈ�κ��� "���� ��ġ"�� �ް�,
        // �����̸� ���� ���� �Ÿ���, �������̸� ������ ���� �Ÿ��� ��ġ�� ��Ű��

        float originX = source->Pos().x;
        float originY = source->Pos().y;

        //�� ���� : ���������� �Ÿ� = ������
        float destX = isLeft ? originX - 100 : originX + 100;
        // 100 : �ӽ÷� ���� ��Ʈ�� ���������� �Ÿ�

        this->Pos().x = destX; //������ X ��ǥ
        this->Pos().y = originY; //����� ������ ���� ���̸� ���� �� �ֵ� �� �� ���Ƽ�

        // * ���� Ÿ��FX�� ������ Y ��ǥ�� �޶�� �Ѵٸ� �� ���꿡�� ������ �������� �� ��
    }

};


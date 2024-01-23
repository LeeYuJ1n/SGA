#include "Framework.h"

Card::Card(wstring textureFile)
    : Button(textureFile)
{
    key = textureFile; // ���� �̸��� �ٷ� ī�� �̸����� (�̴ϼȶ����� ����)
                       // -> �� ī�� �̸��� �ٸ� ������ ��¿� �� �� �ֵ��� �Ѵ�
                       //    + ���ӿ����� �� ī�� �̸��� ���� �� ������ ����

    SetPixelShader(L"Outline.hlsl");

    SetEvent(bind(&Card::OnClick, this));

    intBuffer = new IntValueBuffer();
    floatBuffer = new FloatValueBuffer();
    colorBuffer = new ColorBuffer();

    floatBuffer->Get()[0] = size.x;
    floatBuffer->Get()[1] = size.y;

    colorBuffer->Get() = { 1, 1, 0, 1 };
}

Card::~Card()
{
    delete intBuffer;
    delete floatBuffer;
    delete colorBuffer;
}

void Card::Update()
{
    //Button::Update();
    //������ �Ǿ��� �� ����� ī�� ��ü ��ȭ
    // -> ���̴��� ���� ���� �ణ ��ȭ
    if (isSelected) intBuffer->Get()[0] = 1;
    else intBuffer->Get()[0] = 0;

    Button::Update(); //���� �ڵ� �ݿ���
}

void Card::Render()
{
    //���̴� ����� �ٸ� �繰 �����ϵ���...

    if (!isActive) return;

    intBuffer->SetPS(1);
    floatBuffer->SetPS(2);
    colorBuffer->SetPS(3); // �ƿ����� ���̴��� 3

    Quad::Render();
}

void Card::OnClick()
{
    Observer::Get()->ExcuteParamEvent("SelectCard", this);
}
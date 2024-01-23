#include "Framework.h"

Button::Button(wstring file)
    : Quad(file)
{
    collider = new RectCollider(size); // ���⼭ size : �θ��� ��� ����, ������ ũ�� = �׸��� ũ��
    collider->SetParent(this);
}

Button::Button(Vector2 size)
    : Quad(size)
{
    collider = new RectCollider(size); // ���⼭ size : ���� �Ű������� ���� Vector2 (�� �ڵ�� ö�ڰ� ���Ƶ� ȣȯ �Ұ�)
    collider->SetParent(this);
}

Button::~Button()
{
    delete collider;
}

void Button::Update()
{
    if (!isActive) return;

    if (collider->IsPointCollision(mousePos))
    {
        //�� ������ �������� ���콺 Ŀ���� ��ư ���� ���� ��Ȳ

        //�������ͽ��� ��Ȯ�� ���̳� �ٿ��̳ĸ� ���� ���� (bool�� �̿�)
        if (KEY_DOWN(VK_LBUTTON))
            isDownCheck = true;

        // ��ư�� ���´� �� �� �ϳ�. 1. ������+������ ����(Ŭ��) 2.���콺����
        if (KEY_PRESS(VK_LBUTTON)) state = DOWN;
        else state = OVER;

        //�������ͽ��� ��Ȯ�� ���̳� �ٿ��̳ĸ� ����
        //enum�� �� ��� �Ʒ��� ���ǹ��� Ȱ�� (�� if�� �ȿ� ������ �� Ȯ��)
        //if (KEY_DOWN(VK_LBUTTON)) state = DOWN;
        //else if (KEY_UP(VK_LBUTTON)) state = UP;

        //enum�̵�, bool�� ���, �� �ڵ带 ���ؼ� �Ʒ� ������ �Ǻ� ����
        // "���콺�� ��ư ���� �ö󰬰�, �ű⼭ ��Ŭ���� �ߴ�-> �׷��Ƿ� ��ư�� ������"

        // ��ư�� ������ �����ϴ� ���
        // 1. ����ó�� �浹�� ������ �ܺο����� Ȯ���� �ؼ�, �ش� ��쿡 ������ ���� (Ű����� ����� ���)
        // 2. �ݴ��, �� ��ư�� � ������ �̸� �����ص״ٰ� ���� �� ������ ������ ���� (�ݹ�� ����� ���)
        // -> ���⼭�� 2�� ������� �õ�

        //��ư�� ������ ������ ����Ǵ� ������ ��� �����ڰ� ���ϱ� ����
        // (��ư �����ڸ��� ����, ���� �ð� ������ ����)
        // -> ���⼭�� ��ư�� �����ٰ� (ũ�Ⱑ �ִ� �ͱ��� ���� ����) ���� �����ϴ� �ɷ�
        if (isDownCheck && KEY_UP(VK_LBUTTON))
        {
            // ��ư �ô�!

            if (event != nullptr) event(); //����� �̺�Ʈ�� ������ (�Լ� �����Ϳ� �Ҵ�� ���� ������) ����
            if (paramEvent != nullptr) paramEvent(object); //����� "�Ű�����" �̺�Ʈ�� ������ ����

            //�׸��� ���� ���� ��, ��ư ������ ����
            isDownCheck = false;
        }
    }
    else
    {
        //����� �������� ���콺 Ŀ���� ��ư ������ ���� ��Ȳ
        state = NONE;

        //bool�� ����üũ�� �ߴٸ� ���⼭�� ���� �ڵ带 �־�� �Ѵ�
        if (KEY_UP(VK_LBUTTON))
            isDownCheck = false;
    }

    //������ ���� ���¿� ���� ��ư�� �ð��� �ǵ���� �ش�
    // -> ���� �ٲ� ����, ����Ʈ�� ��ư�̳� Ŀ���� �� ����....
    // -> ������ Ʈ�������� �̿��ؼ� �� �� �ִ� �ǵ���� �ش� : ũ�� ����
    switch(state)
    {
    case Button::NONE:
        localScale = { 1, 1 };
        break;
    case Button::DOWN:
        localScale = { 0.75f, 0.75 };
        break;
    case Button::OVER:
        localScale = { 1.1f, 1.1f };
        break;
    }

    //�ڱ� ������Ʈ (�׸� ��� ���ԵǸ� ���� ������Ʈ, �ƴϸ� Ʈ�������� ������Ʈ)
    Quad::Update();
    //Transform::UpdateWorld();

    //�׸��� �浹ü�� ������Ʈ
    collider->Update();
    //collider->UpdateWorld();
}

void Button::Render()
{
    if (!isActive) return;

    Quad::Render(); //�θ� ���� ó�� = �ڱ� ���
    collider->Render(); //�ݶ��̴��� ���
}
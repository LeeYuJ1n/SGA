#include "Framework.h"
#include "SpawnUsingManager.h"
#include <string.h>

SpawnUsingManager::SpawnUsingManager()
{
    //�⺻ ����. ũ�⸦ �ָ� ȭ�鿡 ���´�
    rect = new Rect(Vector2(), Vector2(20, 20));
    rect->Pos() = { (long)CENTER_X, (long)CENTER_Y };
    rect->Active() = true; //Ȱ��ȭ�� true�� ������ ���� �����ϸ� ���´�

    hBrush = CreateSolidBrush(RGB(0, 255, 0));

    //������ ���ÿ� ���� �Ŵ����� ����
    SpawnManager::Get(); //ȣ�⸸ �ϰ� �� ���� ������ �������ϴ�.
                         // ���� �� ������ �ƴ϶�, "���� ���� ����� ��" ��ü�� �����̴ϱ�
}

SpawnUsingManager::~SpawnUsingManager()
{
    delete rect;

    DeleteObject(hBrush);
}

void SpawnUsingManager::Update()
{
    int width = WIN_WIDTH;
    int height = WIN_HEIGHT;

    // ���콺�� �� ���� �簢����(��Ʈ��) ����ٳ��!
    rect->Pos() = mousePos; //���콺 ��ġ�� �簢�� ��ġ�� �ް�

    //�� ��Ʈ�� �����Ŵ��� �������� �ε�ġ�� ��������� ����
    SpawnManager::Get()->DestoryObject(rect);
    //�Լ� �̸��� �ٸ��� ��¥�� �� ����� �Լ��� �ƴϰ�
    //�Ŵ��� �� �簢���� �Ǻ��ؼ� ������ ������ �����ϴ� ������ �մϴ�.

    //�����Ŵ����� ����
    SpawnManager::Get()->Update();
}

void SpawnUsingManager::Render(HDC hdc)
{
    SelectObject(hdc, hBrush);
    rect->Render(hdc);

    //�����Ŵ��� ����
    SpawnManager::Get()->Render(hdc);
}
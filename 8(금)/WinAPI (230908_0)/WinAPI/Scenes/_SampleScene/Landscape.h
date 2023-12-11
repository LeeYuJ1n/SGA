#pragma once

class Landscape
{
public:
    Landscape(wstring file, bool autoPlay);
    ~Landscape();

    void Update();
    void Render(HDC hdc);

    void SetSpeed(float speed) { bgSpeed = speed; }

    float GetPixelHeight(Vector2& pos); // �ؽ�ó ���� ������ ������ ���
    float GetPixelHeight(Vector2& pos, COLORREF exColor); // ���� (���ܰ�) ���� �Է�

    HDC GetMemDC(Vector2& pos);

    float OffsetX() { return offsetX / offsetGl; }
    float OffsetY() { return 0; } // �ӽ�

private:
    vector<ImageRect*> bgs;

    float bgSpeed = 0;
    bool autoScroll = false;

    void InitSpeed();

    // ������ ��ũ������ ��� ��ǥ�� ���߱� ���� ���� ����
    float offsetX = 0;  // x��ǥ (y�� ������ y�� ����ô�)
    float offsetGl = 2; // �׸��� �����ų� ũ�ų�... �ؼ� 1:1 ������ �� ���� �� ���߱� ���� 
};
#pragma once

class Rect;

class Texture
{
private:
    Texture(wstring file, COLORREF transColor, UINT frameX, UINT frameY);
    ~Texture();

public:
    static Texture* Add(wstring file, UINT frameX = 1, UINT frameY = 1, COLORREF transColor = MAGENTA);
    static void Delete();

    void Render(HDC hdc, Rect* rect, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, Rect* rect, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, Rect* rect, bool isLeft, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);

    Vector2 GetSize() { return Vector2(cutSize); }
    POINT GetFrame() { return imageFrame; }

    static void SetDebug() { isDebugMode = !isDebugMode; }

    // �׸����� ȭ�� ������ �Ǻ��� ���� ���ϱ�
    float GetPixelHeight(Vector2& pos); // �ؽ�ó ���� ������ ������ ���
    float GetPixelHeight(Vector2& pos, COLORREF exColor); // ���� (���ܰ�) ���� �Է�

    HDC GetMemDC() { return memDC; }

private:

    //�ؽ�ó (�� �ִϸ��̼�) ��� Ŭ����

    //DC 3�� (�޸� ����, ��Ʈ��ġ, ���� ����)
    HDC memDC;
    HDC stretchDC;
    HDC alphaMemDC;

    //DC�� �׸� ���� ����� �ְ�ޱ� ���� ���� ��Ʈ�� 3�� (�޸� ����, ��Ʈ��ġ, ���� ����)
    HBITMAP hBitmap;
    HBITMAP hStretchBitmap;
    HBITMAP hAlphaBitmap;

    //���� ���� ���꿡 ����� ��Ʈ�� ���� ����
    BLENDFUNCTION blendFunc;

    //�������� �� �� (�ν��Ͻ� Ȥ�� �̹��� �ε� �ÿ� �� ���� �������ָ� �� ���� ����������)
    COLORREF transfColor;

    //�̹��� ������ (ũ��, �������� ���� ��� ��� ���� ���ΰ�, �߸� ������ ũ��)
    POINT imageSize;
    POINT imageFrame;
    POINT cutSize;

    //�ؽ�ó�� ������ ��� (�ִϸ��̼� ������ ���� �׸��� �� ���� ���� ���) ������ ��� ���� ��
    static unordered_map<wstring, Texture*> textures;
    static bool isDebugMode;
};
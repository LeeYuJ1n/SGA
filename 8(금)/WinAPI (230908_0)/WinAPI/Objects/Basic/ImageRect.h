#pragma once

class ImageRect : public Rect
{
public:
    ImageRect(wstring file, UINT frameX = 1, UINT frameY = 1,
        COLORREF transColor = MAGENTA);
    ImageRect(Texture* texture);
    ~ImageRect() = default;

    void Render(HDC hdc, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, bool isLeft, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);

    float GetPixelHeight(Vector2& pos); // 텍스처 내에 투명값이 지정된 경우
    float GetPixelHeight(Vector2& pos, COLORREF exColor); // 투명값 (제외값) 수동 입력

    HDC GetMemDC() { return texture->GetMemDC(); }

protected:
    Texture* texture;
};
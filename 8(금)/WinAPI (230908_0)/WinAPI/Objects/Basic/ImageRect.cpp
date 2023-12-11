#include "Framework.h"

ImageRect::ImageRect(wstring file, UINT frameX, UINT frameY, COLORREF transColor)
{
    texture = Texture::Add(file, frameX, frameY, transColor);
    size = texture->GetSize();
}

ImageRect::ImageRect(Texture* texture) : texture(texture)
{
    size = texture->GetSize();
}

void ImageRect::Render(HDC hdc, POINT curFrame, bool isTrans)
{
    if (!isActive) return;

    texture->Render(hdc, this, curFrame, isTrans);
}

void ImageRect::Render(HDC hdc, int alpha, POINT curFrame, bool isTrans)
{
    if (!isActive) return;

    texture->Render(hdc, this, alpha, curFrame, isTrans);
}

void ImageRect::Render(HDC hdc, bool isLeft, int alpha, POINT curFrame, bool isTrans)
{
    if (!isActive) return;

    texture->Render(hdc, this, isLeft, alpha, curFrame, isTrans);
}

float ImageRect::GetPixelHeight(Vector2& pos)
{
    return texture->GetPixelHeight(pos);
}

float ImageRect::GetPixelHeight(Vector2& pos, COLORREF exColor)
{
    return texture->GetPixelHeight(pos, exColor);
}
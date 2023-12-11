#include "Framework.h"
#include "Tast_BitmapScene.h"

Tast_BitmapScene::Tast_BitmapScene()
{
	HDC _hdc = GetDC(_hWnd);
	memDC = CreateCompatibleDC(_hdc);
	ReleaseDC(_hWnd, _hdc);

	charArtist = (HBITMAP)LoadImage(hInst,
		L"Textures_230822/CharArtist.bmp",
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE);

	humanJump = (HBITMAP)LoadImage(hInst,
		L"Textures_230822/humanJump.bmp",
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE);
}

Tast_BitmapScene::~Tast_BitmapScene()
{
	DeleteDC(memDC);
	
	DeleteObject(charArtist);
	DeleteObject(humanJump);
}

void Tast_BitmapScene::Update()
{
	if (KEY_PRESS(VK_LBUTTON) && motion <= 256)
	{
		motion += 256;
		Sleep(100);
	}

	else if (KEY_PRESS(VK_LBUTTON) && motion >= 256)
	{
		motion -= 256;
		Sleep(100);
	}
}

void Tast_BitmapScene::Render(HDC hdc)
{
	SelectObject(memDC, charArtist);

	BitBlt(hdc,
		0, 0,
		WIN_WIDTH, WIN_HEIGHT,
		memDC,
		0, 0,
		SRCCOPY);

	SelectObject(memDC, humanJump);

	GdiTransparentBlt(hdc,
		200, 200,
		256, 256,
		memDC,
		motion, 0,
		128, 128,
		RGB(255, 255, 255));
}


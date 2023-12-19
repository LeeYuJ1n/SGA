#include "Framework.h"
#include "Construction.h"

Construction::Construction()
{
	HDC _hdc = GetDC(_hWnd);
	memDC = CreateCompatibleDC(_hdc);
	stretchDC = CreateCompatibleDC(_hdc);

	ReleaseDC(_hWnd, _hdc);

	// character1
	background = (HBITMAP)LoadImage(hInst, L"Textures2/Construct/Background.bmp",
	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	Road2 = (HBITMAP)LoadImage(hInst, L"Textures2/Construct/Construction_Road_2.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// HBITMAP → Road
	Road = (HBITMAP)LoadImage(hInst, L"Textures2/Construct/Construction_Road_1.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

Construction::~Construction()
{

}

void Construction::Update()
{

}

void Construction::Render(HDC hdc)
{
	// HBITMAP → Background
	SelectObject(memDC, background);

	StretchBlt(hdc,                 // 출력의 목적지를 중간의 스트레치 DC로
		0, 0,				        // 출력 시작 위치
		WIN_WIDTH, WIN_HEIGHT,      // 출력 크기
		memDC,				        // 원본 화면
		WIN_WIDTH, 0,		        // 참조를 시작할 곳
		-WIN_WIDTH, WIN_HEIGHT,     // 참조의 크기와 방향
		SRCCOPY);

	// HBITMAP → Construct → Road
	SelectObject(memDC, Road);

	int startX1 = 0;
	int startY1 = 300;
	int imageSize1 = 128;
	int numImages1 = 10;  // 이미지의 개수

	// 윗 길
	for (int i = 0; i < numImages1; ++i)
	{
		GdiTransparentBlt(hdc,                   // 출력할 화면(모니터)
			startX1 + i * imageSize1, startY1,   // 출력을 시작할 위치
			imageSize1, imageSize1,				 // 출력을 할 크기인데... "수동으로 정할 수도 있다"
			memDC, 0, 0, imageSize1, imageSize1, // 어디에서 화면을 가져올 것인가
			RGB(255, 0, 255));					 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
	}											 // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
												 // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻
	int startX2 = 0;
	int startY2 = 600;
	int imageSize2 = 128;
	int numImages2 = 10;  // 이미지의 개수

	// 아래 길
	for (int i = 0; i < numImages2; ++i)
	{
		GdiTransparentBlt(hdc,
			startX2 + i * imageSize2, startY2,
			imageSize2, imageSize2,
			memDC, 0, 0, imageSize2, imageSize2,
			RGB(255, 0, 255));
	}

	// 왼쪽 사이드 길
	GdiTransparentBlt(hdc,       // 출력할 화면(모니터)
		340, 430,			     // 출력을 시작할 위치
		128, 170,	             // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,					 // 어디에서 화면을 가져올 것인가
		0, 0,		        	 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
		128, 128,	             // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 0, 255));	     // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻

	// 오른쪽 사이드 길
	GdiTransparentBlt(hdc,       // 출력할 화면(모니터)
		800, 430,			     // 출력을 시작할 위치
		128, 170,	             // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,					 // 어디에서 화면을 가져올 것인가
		0, 0,		        	 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
		128, 128,	             // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 0, 255));	     // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻
}
#include "Framework.h"
#include "Construction_Building.h"

Construction_Building::Construction_Building()
{
	HDC _hdc = GetDC(_hWnd);
	memDC = CreateCompatibleDC(_hdc);

	ReleaseDC(_hWnd, _hdc);

	// HBITMAP → Construct
	// Construct : Building1
	Building1 = (HBITMAP)LoadImage(hInst, L"Textures2/Construct/Construction_Building_1.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

Construction_Building::~Construction_Building()
{
	DeleteDC(memDC);
}

void Construction_Building::Update()
{

}

void Construction_Building::Render(HDC hdc)
{
	// HBITMAP → Construct → Building1 (Buildong Setting)
	SelectObject(memDC, Building1);

	GdiTransparentBlt(hdc,       // 출력할 화면(모니터)
		50, 330,			     // 출력을 시작할 위치
		256, 256,	             // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,					 // 어디에서 화면을 가져올 것인가
		0, 0,		        	 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
		128, 128,	             // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 0, 255));	     // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻

	GdiTransparentBlt(hdc,       // 출력할 화면(모니터)
		500, 330,				 // 출력을 시작할 위치
		256, 256,				 // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,					 // 어디에서 화면을 가져올 것인가
		0, 0,					 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
		128, 128,				 // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 0, 255));		 // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻

	GdiTransparentBlt(hdc,       // 출력할 화면(모니터)
		950, 330,				 // 출력을 시작할 위치
		256, 256,				 // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,					 // 어디에서 화면을 가져올 것인가
		0, 0,					 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
		128, 128,				 // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 0, 255));		 // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻

	GdiTransparentBlt(hdc,       // 출력할 화면(모니터)
		50, 10,			     	 // 출력을 시작할 위치
		256, 256,				 // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,					 // 어디에서 화면을 가져올 것인가
		0, 0,					 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
		128, 128,				 // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 0, 255));		 // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻

	GdiTransparentBlt(hdc,       // 출력할 화면(모니터)
		500, 10,				 // 출력을 시작할 위치
		256, 256,				 // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,					 // 어디에서 화면을 가져올 것인가
		0, 0,					 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
		128, 128,				 // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 0, 255));		 // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻

	GdiTransparentBlt(hdc,       // 출력할 화면(모니터)
		950, 10,				 // 출력을 시작할 위치
		256, 256,				 // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,					 // 어디에서 화면을 가져올 것인가
		0, 0,					 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
		128, 128,				 // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 0, 255));		 // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻
}
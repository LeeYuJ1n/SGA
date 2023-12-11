#include "Framework.h"
#include "BitmapScene.h"

BitmapScene::BitmapScene()
{
	// memDC부터 값을 할당 (새로운 영역 생성)
	HDC _hdc = GetDC(_hWnd); // 실제 모니터 정보를 받아와서
	memDC = CreateCompatibleDC(_hdc); 
	// 해당 모니터 정보와 같은 정보를 가진, 가상의 출력 장소를 만든다
	ReleaseDC(_hWnd, _hdc); // 이 데이터의 등록을 해제(메모리를 쓰기 가능하게)
	                        // 생성된 모니터 정보가 메모리를 차지하지 않게

	// 출력 장소를 만든 후, 그림 데이터 불러오기
	artist = (HBITMAP)LoadImage(hInst, L"Textures/char.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// (HBITMAP) : 형변환, 비트맵으로 아래 결과를 바꾸기
	// LoadImage : 그림 파일을 비트 데이터로 읽기
	// 매개변수 - hInst : 이 앱
	//           L"Textures/char.bmp" : 파일의 전체 경로. 솔루션 폴더 기준, 폴더 기호는 /
	//           IMAGE_BITMAP : 대상의 형식
	//           0, 0 : 읽기를 시작할 위치 (=처음부터)
	//           LR_LOADFROMFILE : "파일로부터 열기" 방식으로 읽기

	// 위 함수로, 디스크에 있던 그림 데이터를 RAM에 올린다
	// 더 세련된 함수나 기능을 통해서 효율적으로 (혹은 위치를 VRAM 등으로) 데이터를 올릴 수도 있다
	// 기본적으로 앱에서 그림을 다룰 때는 대체로 이런 "메모리에 그림 올리기" 방식을 쓴다는 건 같다
	// → 그래서 고성능 그래픽 카드일수록 VRAM이 많고, RAM이 많을수록 게임이 잘 돌아간다

	human = (HBITMAP)LoadImage(hInst, L"Textures/Idle.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 그림 파일 이름은 각자가 올린 그림 파일 명을 따를 것

	human2 = (HBITMAP)LoadImage(hInst, L"Textures/Idle_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

BitmapScene::~BitmapScene()
{
	// 이 씬이 끝날 때
	DeleteDC(memDC); // 이 데이터 전체를 메모리에서 없애기

	// 비트맵도 펜이나 브러시처럼 출력 도구라, 지워야 될 때 지우면 좋다
	DeleteObject(artist);
	DeleteObject(human);
}

void BitmapScene::Update()
{

}

void BitmapScene::Render(HDC hdc)
{
	// (펜이나 브러시처럼) 그림도 선택
	SelectObject(memDC, artist); // 도화가 출력

	BitBlt(hdc, 
		0, 0,  // 출력을 시작할 위치
		WIN_WIDTH, WIN_HEIGHT, // 출력을 할 크기
		memDC, // 어디서부터 출력할 데이터를 (화면 정보를) 가져오라는가
		0, 0, // 어디서부터 가져오려는가 (x, y 좌표)
		SRCCOPY); // "소스를 복사 형태로출력한다 (원본을 굳이 지우지는 않는다)"

	// 펜이나 브러시 교체처럼 그림도 똑같이 교체

	SelectObject(memDC, human);
	
	GdiTransparentBlt(hdc,    // 출력할 화면(모니터)
		0, 0,                 // 출력을 시작할 위치
		128, 128,             // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,                // 어디에서 화면을 가져올 것인가
		0, 0,                 // 어디서 가져오려는가
		128, 128,             // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 255, 255));  // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻

	// 따라서 이 함수를 쓰면?
	// 1. 큰 그림을 잘라서 쓸 수 있다 (원하는 부분만 볼 수 있다)
	// 2. 그림에 있는 배경을 투명하게 만들어서 알맹이만 볼 수 있다
	//    → "작은 그림" 혹은 게임 속 캐릭터" UI" 같은 것들을 표현하기에 유용

	SelectObject(memDC, human2);

	GdiTransparentBlt(hdc,    // 출력할 화면(모니터)
		200, 200,                 // 출력을 시작할 위치
		128, 128,             // 출력을 할 크기인데... "수동으로 정할 수도 있다"
		memDC,                // 어디에서 화면을 가져올 것인가
		0, 0,                 // 어디서 가져오려는가
		128, 128,             // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
		RGB(255, 255, 255));  // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻

	// 위 human2 그림에서 쓰인 짙은 보라색 (양홍색) : 2D 게임 등에서 가장 많이 쓰이는 배경색
	// 일부러 그림 파일에서 배경을 저 색으로 칠하고(그림판 등으로) → 이 색을 투명하게 만들면
	// 색 손실 없이 가장 효율적으로 그림을 표현해낼 가능성이 높다

	// * 양홍색은 RGB로 255, 0, 255
	// winAPI에서는 MAGENTA 라고도 한다 (관련 기능을 불러오거나, #define으로 지정하면 편리)
	// #define MAGENTA RGB(255, 0, 255) ← 대략 이렇게
}
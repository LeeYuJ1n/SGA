#include "Framework.h"
#include "Task_230828.h"

Task_230828::Task_230828()
{
	HDC _hdc = GetDC(_hWnd);
	memDC = CreateCompatibleDC(_hdc);
	stretchDC = CreateCompatibleDC(_hdc);

	CTR = new Construction;
	CTB = new Construction_Building;
	EMap1 = new EventMap_1;

	// background = (HBITMAP)LoadImage(hInst, L"Textures/background.bmp",
	// 	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// HBITMAP → background
	background = (HBITMAP)LoadImage(hInst, L"Textures2/Construct/Background.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	// HBITMAP → character1
	// character1 : standing Motion
	character1 = (HBITMAP)LoadImage(hInst, L"Textures2/Character/Idle.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// character1 : Walk Motion 
	character1WALK = (HBITMAP)LoadImage(hInst, L"Textures2/Character/Idle_Walk.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// character1 : Attack Motion
	character1ATK = (HBITMAP)LoadImage(hInst, L"Textures2/Character/Idle_Attack_1.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// HBITMAP → Construct
	// Construct : Building1
	Building1 = (HBITMAP)LoadImage(hInst, L"Textures2/Construct/Construction_Building_1.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// HBITMAP → Road
	Long_Road = (HBITMAP)LoadImage(hInst, L"Textures2/Construct/Construction_Long_Road_1.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// interactionArea Box
	platform[0] = new Rect(Vector2(180, 230), Vector2(64, 64));
	platform[1] = new Rect(Vector2(630, 230), Vector2(64, 64));
	platform[2] = new Rect(Vector2(1080, 230), Vector2(64, 64));
	platform[3] = new Rect(Vector2(180, 570), Vector2(128, 128));
	platform[4] = new Rect(Vector2(630, 570), Vector2(128, 128));
	platform[5] = new Rect(Vector2(1080, 570), Vector2(128, 128));

	actCode = 0;

	actIndex1 = 0; // 애니메이션 순번을 0으로 초기화
	actIndex1Walk = 0;
	actIndex1Atk = 0;

	isReversIndex1 = false;
	isReversIndex1Walk = false;
	isReversIndex1Run = false;

	animationSpeed = 10;
	interval = 1;

	characterPosition = { 0, 0 };
	characterArea = new Rect(Vector2(128, 300), Vector2(128, 128));

	float sizeX = 150;
	float sizeY = 150;
	float posX = 128;
	float posY = 512 - sizeY / 2;

	ReleaseDC(_hWnd, _hdc);
}

Task_230828::~Task_230828()
{
	DeleteDC(memDC);
	DeleteDC(stretchDC);

	delete characterArea;
}

void Task_230828::Update()
{
	EMap1->Update();
	currentTimeElapsed += DELTA * animationSpeed;

	if (currentTimeElapsed >= interval)
	{
		currentTimeElapsed -= interval;

		if (actCode == 0 && !isReversIndex1) actIndex1++;
		else if (actCode == 0 && isReversIndex1) actIndex1--;
		else if (actCode == 1 && !isReversIndex1Walk) actIndex1Walk++;
		else if (actCode == 1 && isReversIndex1Walk) actIndex1Walk--;

		if (actIndex1 > lastIndex1)
		{
			actIndex1 = lastIndex1;
			isReversIndex1 = true;
		}

		if (actIndex1 < 0)
		{
			actIndex1 = 0;
			isReversIndex1 = false;
		}

		if (actIndex1Walk > lastIndex1Walk)
		{
			actIndex1Walk = lastIndex1Walk;
			isReversIndex1Walk = true;
		}

		if (actIndex1Walk < 0)
		{
			actIndex1Walk = 0;
			isReversIndex1Walk = false;
		}

		if (actIndex1Run > lastIndex1Run)
		{
			actIndex1Run = lastIndex1Run;
			isReversIndex1Run = true;
		}

		if (actIndex1Run < 0)
		{
			actIndex1Run = 0;
			actIndex1Run = false;
		}
	}
	// 캐릭터 컨트롤
	if (KEY_DOWN(VK_LEFT))
	{
		actCode = 1;
		isLeft = true;

		actIndex1Walk = 0;
		isReversIndex1Walk = false;
		
	}

	if (KEY_DOWN(VK_RIGHT))
	{
		actCode = 1;
		isLeft = false;

		actIndex1Walk = 0;
		isReversIndex1Walk = false;
	}

	if (KEY_UP(VK_LEFT))
	{
		actCode = 0;

		actIndex1 = 0;
		isReversIndex1 = false;
	}

	if (KEY_UP(VK_RIGHT))
	{
		actCode = 0;

		actIndex1 = 0;
		isReversIndex1 = false;
	}

	if (KEY_PRESS(VK_LEFT))
	{
		if (actCode != 1) actCode = 1;

		characterArea->Pos().x -= moveSpeed;
	}

	if (KEY_PRESS(VK_RIGHT))
	{
		if (actCode != 1) actCode = 1;

		characterArea->Pos().x += moveSpeed;
	}

	if (KEY_DOWN(VK_UP))
	{
		actCode = 1;
		
		actIndex1Walk = 0;
		isReversIndex1Walk = false;

		if (actCode != 1) actCode = 1;

		if (isLeft == true) isLeft = true;
		else if (isLeft != true) isLeft = false;
	}

	if (KEY_PRESS(VK_UP)) // 캐릭터가 위로 이동
	{
		characterArea->Pos().y -= moveSpeed;
	}

	if (KEY_UP(VK_UP))
	{
		actCode = 0;
		actIndex1 = 0;
		isReversIndex1 = false;
	}

	if (KEY_DOWN(VK_DOWN))
	{
		actCode = 1;

		actIndex1Walk = 0;
		isReversIndex1Walk = false;

		if (actCode != 1) actCode = 1;

		if (isLeft == true) isLeft = true;
		else if (isLeft != true) isLeft = false;
	}

	if (KEY_PRESS(VK_DOWN)) // 캐릭터가 아래로 이동
	{
		characterArea->Pos().y += moveSpeed;
	}

	if (KEY_UP(VK_DOWN))
	{
		actCode = 0;
		actIndex1 = 0;
		isReversIndex1 = false;
	}

	if (KEY_PRESS(VK_SHIFT) && KEY_PRESS(VK_LEFT))
	{
		if (actCode != 1) actCode = 1;

		characterArea->Pos().x -= moveSpeed;
	}

	if (KEY_PRESS(VK_SHIFT) && KEY_PRESS(VK_RIGHT))
	{
		if (actCode != 1) actCode = 1;

		characterArea->Pos().x += moveSpeed;
	}

	// ********************************************************************

	if (characterArea->IsCollision(platform[0]))
	{
		singleDir = GetCollisionDirection(characterArea, platform[0]);

		if (singleDir == ABOVE)
		{
			// 조건2: 아래 방향으로 충돌했을 때, characterArea의 아래쪽을 EventMap1Area의 아래쪽에 위치시킵니다.
			characterArea->Pos().y = platform[0]->Top();

			Collision = true;
		}
	}

	// ********************************************************************
}

void Task_230828::Render(HDC hdc)
{
	CTR->Render(hdc); // 구조물 출력
	CTB->Render(hdc);

	HBITMAP stretched = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	// characterArea->Render(hdc); 

	if (Collision)
	{
		EMap1->Render(hdc);
		return;
	}

	int refSize_X = 128;
	int leftPlus = 0;

	int atkPlus = 0;
	
	if (isLeft)
	{
		refSize_X = -128;
		leftPlus = 1;
	}

	if (isAtk)
	{
		atkPlus = 1;
	}

	if (actCode == 0)
	{
		// HBITMAP → character1 → Standing Motion

		SelectObject(memDC, character1);
		SelectObject(stretchDC, stretched);

		StretchBlt(stretchDC,							// 출력의 목적지를 중간의 스트레치 DC로
			0, 0,                                       // 출력 시작 위치
			128, 128,									// 출력 크기
			memDC,										// 원본 화면
			128 * (actIndex1 + leftPlus) - leftPlus, 0,	// 참조를 시작할 곳
			refSize_X, 128,								// 참조의 크기와 방향
			SRCCOPY);									

		GdiTransparentBlt(hdc,                           // 출력할 화면(모니터)
			characterArea->Left(), characterArea->Top(), // 출력을 시작할 위치
			128, 128,									 // 출력을 할 크기인데... "수동으로 정할 수도 있다"
			stretchDC,									 // 어디에서 화면을 가져올 것인가
			0, 0,										 // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가)
			128, 128,									 // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
			RGB(255, 0, 255));							 // 그림을 가져올 떄, ← 여기 지정된 색깔은 투명하게 만들라는 뜻
	}
	else if (actCode == 1)
	{
		// HBITMAP → character1 → Walk Motion

		SelectObject(memDC, character1WALK);
		SelectObject(stretchDC, stretched);
		
		StretchBlt(stretchDC,
			0, 0,
			128, 128,
			memDC,
			128 * (actIndex1Walk + leftPlus), 0,
			refSize_X, 128,
			SRCCOPY);


		GdiTransparentBlt(hdc,
			characterArea->Left(), characterArea->Top(),
			128, 128,
			stretchDC,
			0, 0,
			128, 128,
			RGB(255, 0, 255));
	}
	else if (actCode == 2)
	{
		// HBITMAP → character1 → Attack Motion

		SelectObject(memDC, character1ATK);
		SelectObject(stretchDC, stretched);

		StretchBlt(stretchDC,
			0, 0,
			128, 128,
			memDC,
			128 * (actIndex1Atk + atkPlus) - atkPlus, 0,
			refSize_X, 0,
			SRCCOPY);

		GdiTransparentBlt(hdc,
			characterArea->Left(), characterArea->Top(),
			128, 128,
			stretchDC,
			0, 0,
			128, 128,
			RGB(255, 0, 255));
	}

	// platform[0]->Render(hdc);   // 상호작용을 위한 사각형 출력
	// platform[1]->Render(hdc);   // 상호작용을 위한 사각형 출력
	// platform[2]->Render(hdc);   // 상호작용을 위한 사각형 출력
	// platform[3]->Render(hdc);   // 상호작용을 위한 사각형 출력
	// platform[4]->Render(hdc);   // 상호작용을 위한 사각형 출력
	// platform[5]->Render(hdc);   // 상호작용을 위한 사각형 출력

	DeleteObject(stretched);
}
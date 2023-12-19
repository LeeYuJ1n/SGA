#include "Framework.h"
#include "EventMap_1.h"

EventMap_1::EventMap_1()
{
	HDC _hdc = GetDC(_hWnd);
	memDC = CreateCompatibleDC(_hdc);
	stretchDC = CreateCompatibleDC(_hdc);

	ReleaseDC(_hWnd, _hdc);

	EventMap1 = (HBITMAP)LoadImage(hInst, L"Textures2/Construct/EventMap1.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// HBITMAP �� character1
	// character1 : standing Motion
	character1 = (HBITMAP)LoadImage(hInst, L"Textures2/Character/Idle.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// character1 : Walk Motion 
	character1WALK = (HBITMAP)LoadImage(hInst, L"Textures2/Character/Idle_Walk.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// character1 : Attack Motion
	character1ATK = (HBITMAP)LoadImage(hInst, L"Textures2/Character/Idle_Attack_1.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	EventMap1Area = new Rect(Vector2(675, 300), Vector2(650, 350)); // �� ��Ż ����
	
	// interactionArea Box
	platform = new Rect(Vector2(456, 410), Vector2(128, 128));

	actCode = 0;

	actIndex1 = 0; // �ִϸ��̼� ������ 0���� �ʱ�ȭ
	actIndex1Walk = 0;
	actIndex1Atk = 0;

	isReversIndex1 = false;
	isReversIndex1Walk = false;
	isReversIndex1Run = false;

	animationSpeed = 10;
	interval = 1;

	characterPosition = { 0, 0 };
	characterArea = new Rect(Vector2(450, 400), Vector2(128, 128)); // ĳ���� ���� ��ġ

	float sizeX = 150;
	float sizeY = 150;
	float posX = 128;
	float posY = 512 - sizeY / 2;

	ReleaseDC(_hWnd, _hdc);
}

EventMap_1::~EventMap_1()
{
	DeleteDC(memDC);
	DeleteDC(stretchDC);

	delete characterArea;
	delete EventMap1Area;
}

void EventMap_1::Update()
{
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
	// ĳ���� ��Ʈ��
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

	if (KEY_PRESS(VK_UP)) // ĳ���Ͱ� ���� �̵�
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

	if (KEY_PRESS(VK_DOWN)) // ĳ���Ͱ� �Ʒ��� �̵�
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

	if (characterArea->IsCollision(EventMap1Area))
	{
		singleDir = GetCollisionDirection(characterArea, EventMap1Area);

		if (singleDir == ABOVE)
		{
			// ����1: �� �������� �浹���� ��, characterArea�� ������ EventMap1Area�� ���ʿ� ��ġ��ŵ�ϴ�.
			characterArea->Pos().y = EventMap1Area->Top() + characterArea->GetSize().y / 2;
		}
		else if (singleDir == BENEATH)
		{
			// ����2: �Ʒ� �������� �浹���� ��, characterArea�� �Ʒ����� EventMap1Area�� �Ʒ��ʿ� ��ġ��ŵ�ϴ�.
			characterArea->Pos().y = EventMap1Area->Bottom() - characterArea->GetSize().y / 2;
		}
		else if (singleDir == LEFT)
		{
			// ����3: characterArea�� ������ EventMap1Area�� ���ʰ� �浹���� ��, �������� �̵����� ���ϰ� �մϴ�.
			characterArea->Pos().x = EventMap1Area->Left() - characterArea->GetSize().x / 2;
		}
		else if (singleDir == RIGHT)
		{
			// ����4: ������ �������� �浹���� ��, characterArea�� �������� EventMap1Area�� �����ʿ� ��ġ��ŵ�ϴ�.
			characterArea->Pos().x = EventMap1Area->Right() + characterArea->GetSize().x / 2;
		}
	}

	// ********************************************************************

	if (characterArea->IsCollision(platform))
	{
		singleDir = GetCollisionDirection(characterArea, platform);

		if (singleDir == BENEATH)
		{
			// ����2: �Ʒ� �������� �浹���� ��, characterArea�� �Ʒ����� EventMap1Area�� �Ʒ��ʿ� ��ġ��ŵ�ϴ�.
			characterArea->Pos().y = platform->Bottom() - characterArea->GetSize().y / 2;

			Collision = true;
		}
	}

	// ********************************************************************



	// if (characterArea->IsCollision(EventMap1Area))
	// {
	// 	singleDir = GetCollisionDirection(characterArea, EventMap1Area);
	// 
	// 	if (singleDir == ABOVE)
	// 	{
	// 		// �� �������� �浹���� ��, characterArea�� ������ EventMap1Area�� ���ʿ� ��ġ��ŵ�ϴ�.
	// 		characterArea->Pos().y = EventMap1Area->() - characterArea->GetSize().y / 2;
	// 	}
	// 	else if (singleDir == BENEATH)
	// 	{
	// 		characterArea->Pos().y = EventMap1Area->Bottom() - characterArea->GetSize().y / 2;
	// 	}
	// 	else if (singleDir == LEFT)
	// 	{
	// 		characterArea->Pos().x = EventMap1Area->Left() - characterArea->GetSize().y / 2;
	// 	}
	// 	else if (singleDir == RIGHT)
	// 	{
	// 		characterArea->Pos().x = EventMap1Area->Right() + characterArea->GetSize().y / 2;
	// 	}
	// }
}

void EventMap_1::Render(HDC hdc)
{
	HBITMAP stretched = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);

	SelectObject(memDC, EventMap1);

	BitBlt(hdc,
		0, 0,
		1920, 1080,
		memDC,
		0, 0,
		SRCCOPY);

	if (Collision)
	{
		
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
	
	// characterArea->Render(hdc);
	// platform->Render(hdc);

	if (actCode == 0)
	{
		// EventMap1Area->Render(hdc);
		// HBITMAP �� character1 �� Standing Motion

		SelectObject(memDC, character1);
		SelectObject(stretchDC, stretched);

		StretchBlt(stretchDC,							// ����� �������� �߰��� ��Ʈ��ġ DC��
			0, 0,                                       // ��� ���� ��ġ
			128, 128,									// ��� ũ��
			memDC,										// ���� ȭ��
			128 * (actIndex1 + leftPlus) - leftPlus, 0,	// ������ ������ ��
			refSize_X, 128,								// ������ ũ��� ����
			SRCCOPY);

		GdiTransparentBlt(hdc,                           // ����� ȭ��(�����)
			characterArea->Left(), characterArea->Top(), // ����� ������ ��ġ
			128, 128,									 // ����� �� ũ���ε�... "�������� ���� ���� �ִ�"
			stretchDC,									 // ��𿡼� ȭ���� ������ ���ΰ�
			0, 0,										 // ��� ���������°� (128 �ȼ� �������� ǥ�� ��ü�� ������ �Դ°�)
			128, 128,									 // ������ �׸��� ��� ���� ũ��� ������ ���ΰ� (�ش� �ȵǸ� �ڸ���)
			RGB(255, 0, 255));							 // �׸��� ������ ��, �� ���� ������ ������ �����ϰ� ������ ��
	}
	else if (actCode == 1)
	{
		// HBITMAP �� character1 �� Walk Motion

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
		// HBITMAP �� character1 �� Attack Motion

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

	DeleteObject(stretched);
}
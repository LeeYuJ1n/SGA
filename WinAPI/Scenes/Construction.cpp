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

	// HBITMAP �� Road
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
	// HBITMAP �� Background
	SelectObject(memDC, background);

	StretchBlt(hdc,                 // ����� �������� �߰��� ��Ʈ��ġ DC��
		0, 0,				        // ��� ���� ��ġ
		WIN_WIDTH, WIN_HEIGHT,      // ��� ũ��
		memDC,				        // ���� ȭ��
		WIN_WIDTH, 0,		        // ������ ������ ��
		-WIN_WIDTH, WIN_HEIGHT,     // ������ ũ��� ����
		SRCCOPY);

	// HBITMAP �� Construct �� Road
	SelectObject(memDC, Road);

	int startX1 = 0;
	int startY1 = 300;
	int imageSize1 = 128;
	int numImages1 = 10;  // �̹����� ����

	// �� ��
	for (int i = 0; i < numImages1; ++i)
	{
		GdiTransparentBlt(hdc,                   // ����� ȭ��(�����)
			startX1 + i * imageSize1, startY1,   // ����� ������ ��ġ
			imageSize1, imageSize1,				 // ����� �� ũ���ε�... "�������� ���� ���� �ִ�"
			memDC, 0, 0, imageSize1, imageSize1, // ��𿡼� ȭ���� ������ ���ΰ�
			RGB(255, 0, 255));					 // ��� ���������°� (128 �ȼ� �������� ǥ�� ��ü�� ������ �Դ°�)
	}											 // ������ �׸��� ��� ���� ũ��� ������ ���ΰ� (�ش� �ȵǸ� �ڸ���)
												 // �׸��� ������ ��, �� ���� ������ ������ �����ϰ� ������ ��
	int startX2 = 0;
	int startY2 = 600;
	int imageSize2 = 128;
	int numImages2 = 10;  // �̹����� ����

	// �Ʒ� ��
	for (int i = 0; i < numImages2; ++i)
	{
		GdiTransparentBlt(hdc,
			startX2 + i * imageSize2, startY2,
			imageSize2, imageSize2,
			memDC, 0, 0, imageSize2, imageSize2,
			RGB(255, 0, 255));
	}

	// ���� ���̵� ��
	GdiTransparentBlt(hdc,       // ����� ȭ��(�����)
		340, 430,			     // ����� ������ ��ġ
		128, 170,	             // ����� �� ũ���ε�... "�������� ���� ���� �ִ�"
		memDC,					 // ��𿡼� ȭ���� ������ ���ΰ�
		0, 0,		        	 // ��� ���������°� (128 �ȼ� �������� ǥ�� ��ü�� ������ �Դ°�)
		128, 128,	             // ������ �׸��� ��� ���� ũ��� ������ ���ΰ� (�ش� �ȵǸ� �ڸ���)
		RGB(255, 0, 255));	     // �׸��� ������ ��, �� ���� ������ ������ �����ϰ� ������ ��

	// ������ ���̵� ��
	GdiTransparentBlt(hdc,       // ����� ȭ��(�����)
		800, 430,			     // ����� ������ ��ġ
		128, 170,	             // ����� �� ũ���ε�... "�������� ���� ���� �ִ�"
		memDC,					 // ��𿡼� ȭ���� ������ ���ΰ�
		0, 0,		        	 // ��� ���������°� (128 �ȼ� �������� ǥ�� ��ü�� ������ �Դ°�)
		128, 128,	             // ������ �׸��� ��� ���� ũ��� ������ ���ΰ� (�ش� �ȵǸ� �ڸ���)
		RGB(255, 0, 255));	     // �׸��� ������ ��, �� ���� ������ ������ �����ϰ� ������ ��
}
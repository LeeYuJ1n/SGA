#pragma once

class Construction : public Scene
{
public:
	Construction();
	~Construction();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// HBITMAP �� �÷��̾� ĳ����
	HBITMAP character1;       // �÷��̾� ���ĵ� ���
	HBITMAP character1WALK;   // �÷��̾� �ȱ� ���
	HBITMAP character1ATK; // �÷��̾� ���� ���
	HBITMAP character1DEAD;   // �÷��̾� �״� ���

	// HBITMAP �� ������
	HBITMAP background;      // ���� ���
	HBITMAP Building1;       // �ǹ�1
	HBITMAP Building2;       // �ǹ�2
	HBITMAP BuildingTile;    // �ǹ� �ٴ�
	HBITMAP BuildingWall;    // �ǹ� ��
	HBITMAP Road;            // ��
	HBITMAP Road2;           // ���Ա� ��

	// HDC
	HDC memDC;
	HDC stretchDC;

	// character1 controller
};


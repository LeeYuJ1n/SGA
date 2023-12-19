#pragma once

class Construction : public Scene
{
public:
	Construction();
	~Construction();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// HBITMAP → 플레이어 캐릭터
	HBITMAP character1;       // 플레이어 스탠딩 모션
	HBITMAP character1WALK;   // 플레이어 걷기 모션
	HBITMAP character1ATK; // 플레이어 공격 모션
	HBITMAP character1DEAD;   // 플레이어 죽는 모션

	// HBITMAP → 구조물
	HBITMAP background;      // 게임 배경
	HBITMAP Building1;       // 건물1
	HBITMAP Building2;       // 건물2
	HBITMAP BuildingTile;    // 건물 바닥
	HBITMAP BuildingWall;    // 건물 벽
	HBITMAP Road;            // 길
	HBITMAP Road2;           // 출입구 길

	// HDC
	HDC memDC;
	HDC stretchDC;

	// character1 controller
};


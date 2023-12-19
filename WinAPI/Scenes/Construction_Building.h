#pragma once

class Construction_Building : public Scene
{
public:
	Construction_Building();
	~Construction_Building();

	void Update () override;
	virtual void Render(HDC hdc) override;

	// HBITMAP
	HBITMAP Building1;

	// HDC
	HDC memDC;

	// 상호작용을 위한 사각형
	Rect* platform[6];
};


#pragma once

class Tast_BitmapScene : public Scene
{
public:
	Tast_BitmapScene();
	~Tast_BitmapScene();

	int motion = 0;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	HBITMAP charArtist;
	HBITMAP humanJump;

	HDC memDC;
};


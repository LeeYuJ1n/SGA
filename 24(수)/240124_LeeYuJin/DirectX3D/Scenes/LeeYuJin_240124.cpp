#include "Framework.h"
#include "LeeYuJin_240124.h"

LeeYuJin_240124::LeeYuJin_240124()
{
	level = new Terrain();
	
	image = new Quad(L"Textures/Image/i14587772636.png");
	image->Scale() *= 0.1f;
	image->Pos() = { 0, 0, 0 };
}

LeeYuJin_240124::~LeeYuJin_240124()
{
	delete level;
	delete image;
}

void LeeYuJin_240124::Update()
{
	image->Rot() = CAM->Rot();

	image->UpdateWorld();
}

void LeeYuJin_240124::PreRender()
{
}

void LeeYuJin_240124::Render()
{
	level->Render();
	image->Render();
}

void LeeYuJin_240124::PostRender()
{
}

void LeeYuJin_240124::GUIRender()
{
}

#include "Framework.h"
#include "LeeYuJin_240123.h"

LeeYuJin_240123::LeeYuJin_240123()
{
	level = new Terrain();
}

LeeYuJin_240123::~LeeYuJin_240123()
{
	delete level;
}

void LeeYuJin_240123::Update()
{
}

void LeeYuJin_240123::PreRender()
{
}

void LeeYuJin_240123::Render()
{
	level->Render();
}

void LeeYuJin_240123::PostRender()
{
}

void LeeYuJin_240123::GUIRender()
{
}

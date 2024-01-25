#include "Framework.h"

TestLight::TestLight()
{
	light = Environment::Get()->AddLight();
	light->color = { 1, 0, 0, 1 }; // »¡°­»ö
}

TestLight::~TestLight()
{
}

void TestLight::Update()
{
}

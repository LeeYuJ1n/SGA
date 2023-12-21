#include "Framework.h"
#include "PickerScene.h"

PickerScene::PickerScene()
{
	picker = new TerrainPicker();
	picker->GetMaterial()->SetShader(L"Light/Light.hlsl");
	picker->GetMaterial()->SetDiffuseMap(L"Textures/Selfie_20230920_LeeYuJin_029.jpg");
}

PickerScene::~PickerScene()
{
	delete picker;
}

void PickerScene::Update()
{
	picker->Update();

	if (KEY_DOWN(VK_LBUTTON))
	{
		colliders.push_back(new BoxCollider());
		colliders[colliders.size() - 1]->Pos() = picker->Pick();
	}

	if (colliders.size() > 3)
	{
		colliders.erase(colliders.begin());
	}

	for (Collider* collider : colliders)
		collider->UpdateWorld();
}

void PickerScene::PreRender()
{

}

void PickerScene::Render()
{
	picker->Render();

	for (Collider* collider : colliders)
		collider->Render();
}

void PickerScene::PostRender()
{

}

void PickerScene::GUIRender()
{
	picker->RenderUI();
}

#include "Framework.h"

EsterEgg::EsterEgg()
{
	// image = new Quad(L"Textures/DHouseTexure/Artist.png");
	// image->Pos() = { CENTER_X, CENTER_Y };
	// image->UpdateWorld();

	image2 = new Quad(L"Textures/DHouseTexure/Artist2.png");
	image2->Pos() = { CENTER_X, CENTER_Y };
	image2->UpdateWorld();
}

EsterEgg::~EsterEgg()
{
	// delete image;
	delete image2;
}

void EsterEgg::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Audio::Get()->Stop("LostArk");
		Audio::Get()->Play("FirstBGM");

		SceneManager::Get()->ChangeScene("Dhouse");

		//if (!active) //���ǹ���
		//�߰� ��Ʈ : ������ �θ��ų� �� ���� ���� ������ ������ �������� �����ִ� �͵� �ʿ��մϴ�
		//�� ���� �� ������� ������ �����ؼ� "NewPlay" - ���� ���� ���߰� ���� ���� ���� �� ����� �͵�....
	}
}

void EsterEgg::Render()
{
	image2->Render();
}



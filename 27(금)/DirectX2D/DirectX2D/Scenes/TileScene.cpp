#include "Framework.h"
#include "TileScene.h"

TileScene::TileScene()
{
	// ���� ����� ȣ��
	CreateSamples();
	editor = new EditTileMap(10, 10); // ������ �����ϱ�
	editor->Pos() = { 100, 100 };

	// ���� ���õ� ������ �⺻ ����("������ �� �Ǿ��� ���� ����")
	// -> ���� ���¸� �̸� �ְ� ���߿� �ؽ�ó��簡 �ٸ� ������ �ٲٸ� �� �����ϱ�
	// -> (Ŭ���� �� �׶��׋� �ν��Ͻ��� ����ٴ� ���õ� ������ �ϴٴ� ��)

	selected = new Quad(sampleSize); // �׸��� �ƴ� ũ��� ���� �ϴ� �����
}

TileScene::~TileScene()
{
	delete selected;

	for (Button* button : samples)
	{
		delete button;
	}

	delete editor;
}

void TileScene::Update()
{
	// ����� ������ ��ɵ��� ���⼭ ����´�

	// 1. Ÿ���� Ŭ������ �� �Ͼ ��
	if (KEY_PRESS(VK_LBUTTON))
	{
		if (selected->GetTexture() != nullptr)
		{
			editor->ClickTile(selected, Tile::BG);
		}
	}

	// 2. (�ɼ�) ����Ʈ������ ���� ���� �� �� �� �ִ� Ű �Է��� ���� ȣ��
	if (KEY_DOWN(VK_F5))
	{
		editor->Save("TextData/Test.map");
	}

	if (KEY_DOWN(VK_F9))
	{
		editor->Load("TextData/Test.map");
	}

	// ��ư�� Ÿ��(������) ������Ʈ

	for (Button* button : samples)
	{
		button->Update();
	}

	editor->Update();

	// ���� ���õ� ������ �ִٸ�

	if (selected->GetTexture() != nullptr)
	{
		// ���콺 �� �Է��� �� �� �� ��� Ȯ�� ������ ������ Ű �Է½�
		if (KEY_DOWN('Q'))
		{
			// ���õ� ������ ȸ��!

			selected->Rot().z += XM_PIDIV2; // �������� ������ ���� 2�� ������? -> 90��!

			// ������ 360�� ������ ������ �ǵ���
			if (selected->Rot().z > XM_2PI)
			{
				selected->Rot().z -= XM_2PI; // 360�� ���� (��ȯ)
				// selected->Rot().z = XM_2PI; // 360���� ���߱� (�ִ밪 ����)
			}
		}

		if (KEY_DOWN('E'))
		{
			selected->Rot().z -= XM_PIDIV2;

			// ������ 360�� ������ ������ �ǵ���
			if (selected->Rot().z > XM_2PI)
			{
				selected->Rot().z -= XM_2PI; // 360�� ���� (��ȯ)
				// selected->Rot().z = 0.0f; // 0���� ���߱� (�ּҰ� ����)
			}
		}

		// ���콺 �� �Է¿� ����
		if (mouseWheel > 0.0f)
		{
			// ���õ� ������ ȸ��!

			selected->Rot().z += XM_PIDIV2; // �������� ������ ���� 2�� ������? -> 90��!

			// ������ 360�� ������ ������ �ǵ���
			if (selected->Rot().z > XM_2PI)
			{
				selected->Rot().z += XM_2PI; // 360�� ���� (��ȯ)
				// selected->Rot().z = XM_2PI; // 360���� ���߱� (�ִ밪 ����)
			}
		}
		else if (mouseWheel < 0.0f)
		{
			selected->Rot().z -= XM_PIDIV2;

			// ������ 360�� ������ ������ �ǵ���
			if (selected->Rot().z > XM_2PI)
			{
				// selected->Rot().z -= XM_2PI; // 360�� ���� (��ȯ)
				selected->Rot().z = 0.0f; // 0���� ���߱� (�ּҰ� ����)
			}
		}

		selected->Pos() = mousePos;
		selected->UpdateWorld();
	}
}

void TileScene::Render()
{
	for (Button* button : samples)
	{
		button->Render();
	}

	editor->Render();

	if (selected->GetTexture() != nullptr)
	{
		selected->Render();
	}
}

void TileScene::PostRender()
{
	// ImGUI�� �̿��� ��� ������ �ΰ� ��� �����
	const char* list[] = { "BG", "OBJ" };
	ImGui::ListBox("Type", (int*)&selectedType, list, 2);

	// ���� ������Ʈ�� ���õ� �� �ִ� ����� ���߿� �Ἥ �� �� Ȯ��

	// * ������ �츮�� �غ� �� �ִ� �� (�ؾ� �Ǵ� ��)

	// Ÿ�� �����Ϳ� ������Ʈ(��ֹ��� �� �� �ִ� ��ü) ä��� ���� �ֱ�
	
	// ���̺� �ε带 ImGUI���� �� ������ -> �ð��� Ȯ���ؼ� ����
}

void TileScene::ClickSample(void* sample)
{
	Button* button = (Button*)sample; // �Ű������� ��ư���� �ٽ� ����ȯ

	// ���� ���õ� ��ư(�̶�� �̸��� ����) ������ Ŭ���� ��ư �������� �ٲٱ�
	selected->SetTexture(button->GetTexture()); // �ؽ�ó ��ü
}

void TileScene::CreateSamples()
{
	// ���� �ڵ鷯 �ӽ÷� ����� (ī�� ���� ��ó��)
	WIN32_FIND_DATA findData;
	HANDLE          handle = FindFirstFile(L"Textures/Tile/*.png", &findData);

	bool result = true; // �� ���� �̸� true�� �ۼ�

	wstring filename;                                          // ���� �̸�
	UINT    width = 10;	                                      
	Vector2 size(sampleSize);                                  // ���� ũ�⵵ �����
	Vector2 startPos(WIN_WIDTH - size.x, WIN_HEIGHT - size.y); // ���� ��ŭ ������ �ְ� �����(���� ����)

	while (result) // ������ ���� ������ ���� ����
	{
		filename  = L"Textures/Tile/";
		filename += findData.cFileName;

		// ���� ������ �ִ°�? (������ ���, ������ bool ��false)
		result = FindNextFile(handle, &findData);

		// ���� �̸� ����� ���� ���� ���� Ȯ��
		// -> ���⼭���ʹ� ����� ���� �̸����� ���� ã�� �ݿ��ϱ�
		
		// ������ ���� �� ������� ����
		UINT index = samples.size(); // ���� ���� ���� ũ�� = ���� �� ����
		                             // �׻� ������ �������� ������

		// ������ ���� �� ��ġ (�������� ��Ģ�� ��ġ)
		Vector2 pos(index % width, index / width); // 1�� ���͸� ���� ���η� ��Ÿ�� �� ���� ���� ���

		Button* button = new Button(size); // ũ��� ��ư �����

		button->SetTexture(filename);            // ũ����� ����� ũ�⿡ �ؽ�ó ���߱�
		button->Pos() = startPos - (pos * size); // ���� ���� ���� - (������ ���� �� ��ǥ * ���� ũ��)
		button->SetParamEvent(bind(&TileScene::ClickSample, this, placeholders::_1)); 
		                                         // �Ű����� �ִ� �Լ��� Ŭ�� �Լ� �Ҵ�
		button->SetObject(button);               // ���� ��� �ڱ� �ڽ� ���

		samples.push_back(button); // ���Ϳ� ���� ��ư �߰��ϱ�
	}

	// ������� ���� ���Ϳ� ������ �� ���� ��
}

#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
	trees.reserve(COUNT);

	FOR(COUNT)
	{
		Vector2 size;
		size.x = Random(3.0f, 10.0f);
		size.y = Random(3.0f, 10.0f);

		Quad* tree = new Quad(size);
		tree->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Tree.png");
		tree->Pos().x = Random(0.0f, 10.0f);
		tree->Pos().z = Random(0.0f, 10.0f);
		tree->Pos().y = 0;

		trees.push_back(tree);
	}
}

BillboardScene::~BillboardScene()
{
}

void BillboardScene::Update()
{
	// �����尡 ī�޶� ���� ��
	// (��Ģ��, Ȥ�� ���� ����)

	for (Quad* tree : trees)
	{
		Vector3 dir = tree->Pos() - CAM->Pos(); // ī�޶� ������ ���� ����
		tree->Rot().y = atan2(dir.x, dir.y); // ������ ������ (��) ź��Ʈ�� �ֱ�
		tree->UpdateWorld(); // ������Ʈ

		// �� �ڵ�� ���⿡ ���� �ø��� ������ �ִٴ� ����� Ȯ�� ����
		// -> �� ������ �ذ��Ϸ��� ��� �ϸ� �ɱ�?

		// -> [ ��Ʈ 1 ] ī�޶��� ������ ���캸��?
		// -> [ ��Ʈ 2 ] ��µǴ� ������Ʈ�� ���캸��?
	}
}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
	for (Quad* tree : trees)
	{
		tree->Render();
	}
}

void BillboardScene::PostRender()
{
}

void BillboardScene::GUIRender()
{
}

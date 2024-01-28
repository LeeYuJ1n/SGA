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
	// 빌보드가 카메라를 보는 법
	// (원칙적, 혹은 직접 제어)

	for (Quad* tree : trees)
	{
		Vector3 dir = tree->Pos() - CAM->Pos(); // 카메라가 나무를 보는 방향
		tree->Rot().y = atan2(dir.x, dir.y); // 나무의 방향을 (역) 탄젠트로 주기
		tree->UpdateWorld(); // 업데이트

		// 위 코드는 방향에 따른 컬링의 문제가 있다는 사실을 확인 가능
		// -> 위 문제를 해결하려면 어떻게 하면 될까?

		// -> [ 힌트 1 ] 카메라의 각도를 살펴보면?
		// -> [ 힌트 2 ] 출력되는 스테이트를 살펴보면?
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

#include "Framework.h"
#include "DijkstraScene.h"

DijkstraScene::DijkstraScene()
{
	Init();
}

DijkstraScene::~DijkstraScene()
{
	delete tank;
	delete dijkstra;
}

void DijkstraScene::Update()
{
	if (KEY_DOWN(VK_SPACE))
	{
		// 시작 지점은 탱크에서 제일 가까운 곳으로 설정
		int start = dijkstra->FineCloseNode(tank->Pos());

		// 목적지는 스페이스 누를 때 마우스 커서에서 제일 가까운 곳으로
		int end = dijkstra->FineCloseNode(mousePos);

		// 시작지에서 목적지로 가능 경로를 설정해서 탱크에 반영 (웨이포인트 지정)
		// -> 비슷하게 웨이포인트가 있(었)다면 비행기나 닌자도 길찾기에 활용 가능
		tank->SetPath(dijkstra->GetPath(start, end));
	}

	dijkstra->Update(); // 계산 업데이트
	tank    ->Update(); // 탱크 정보 업데이트
}

void DijkstraScene::Render()
{
	dijkstra->Render();
	tank    ->Render();
}

void DijkstraScene::Init()
{
	dijkstra = new Dijkstra();
	tank     = new Tank();

	// 위치 재지정이 필요하면 작성
}

void DijkstraScene::PostRender()
{
	// ImGUI가 필요하면 작성
}


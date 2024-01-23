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
		// ���� ������ ��ũ���� ���� ����� ������ ����
		int start = dijkstra->FineCloseNode(tank->Pos());

		// �������� �����̽� ���� �� ���콺 Ŀ������ ���� ����� ������
		int end = dijkstra->FineCloseNode(mousePos);

		// ���������� �������� ���� ��θ� �����ؼ� ��ũ�� �ݿ� (��������Ʈ ����)
		// -> ����ϰ� ��������Ʈ�� ��(��)�ٸ� ����⳪ ���ڵ� ��ã�⿡ Ȱ�� ����
		tank->SetPath(dijkstra->GetPath(start, end));
	}

	dijkstra->Update(); // ��� ������Ʈ
	tank    ->Update(); // ��ũ ���� ������Ʈ
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

	// ��ġ �������� �ʿ��ϸ� �ۼ�
}

void DijkstraScene::PostRender()
{
	// ImGUI�� �ʿ��ϸ� �ۼ�
}


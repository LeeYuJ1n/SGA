#include "Framework.h"

AStar::AStar(GameTileMap* map)
{
    map->GetNodes(nodes); //맵에서 노드 정보 받아오기
    SetEdge(map->GetWidth()); //맵이 정해져 있으므로 해당 맵에 의한 경로 정보도 미리 다 받아오기

    heap = new Heap();
}

AStar::~AStar()
{
    for (Node* node : nodes)
        delete node;
    delete heap;
}

void AStar::Update()
{

}

void AStar::Render()
{
    for (Node* node : nodes)
        node->Render();
}

void AStar::GetPath(IN int start, IN int end, OUT vector<Vector2>& path)
{

}

// "입력이나 호출에 따라 가장 적절한 좌표(=바로 주변 좌표)" 반환
int AStar::FindCloseNode(Vector2 pos)
{
    // 최초 지정 거리 : 무한대
    float minDist = FLT_MAX;
    int result = -1; // 결과 없음

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        float distance = Distance(pos, nodes[i]->pos);
        if (distance < minDist) // 가까운 정도가 갱신된다면
        {
            //결과 반영
            minDist = distance;
            result = i;
        }
    }

    //결과 반환
    return result;
}

void AStar::SetEdge(UINT width)
{
    //모든 노드에 대해서 반복문 돌리기
    for (UINT i = 0; i < nodes.size(); ++i)
    {
        // 
        if (i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + 1]);
            nodes[i + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width)
        {
            nodes[i]->AddEdge(nodes[i + width]);
            nodes[i + width]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + width + 1]);
            nodes[i + width + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != 0)
        {
            nodes[i]->AddEdge(nodes[i + width - 1]);
            nodes[i + width - 1]->AddEdge(nodes[i]);
        }
    }
}

int AStar::GetMinNode()
{

}

void AStar::Extend(int center, int end)
{

}

void AStar::Reset()
{

}

float AStar::GetManhattanDistance(int start, int end)
{

}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{

}
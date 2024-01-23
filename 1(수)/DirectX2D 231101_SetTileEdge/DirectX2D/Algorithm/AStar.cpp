#include "Framework.h"

AStar::AStar(GameTileMap* map)
{
    map->GetNodes(nodes); //�ʿ��� ��� ���� �޾ƿ���
    SetEdge(map->GetWidth()); //���� ������ �����Ƿ� �ش� �ʿ� ���� ��� ������ �̸� �� �޾ƿ���

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

// "�Է��̳� ȣ�⿡ ���� ���� ������ ��ǥ(=�ٷ� �ֺ� ��ǥ)" ��ȯ
int AStar::FindCloseNode(Vector2 pos)
{
    // ���� ���� �Ÿ� : ���Ѵ�
    float minDist = FLT_MAX;
    int result = -1; // ��� ����

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        float distance = Distance(pos, nodes[i]->pos);
        if (distance < minDist) // ����� ������ ���ŵȴٸ�
        {
            //��� �ݿ�
            minDist = distance;
            result = i;
        }
    }

    //��� ��ȯ
    return result;
}

void AStar::SetEdge(UINT width)
{
    //��� ��忡 ���ؼ� �ݺ��� ������
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
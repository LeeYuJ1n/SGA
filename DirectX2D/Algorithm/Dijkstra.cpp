#include "Framework.h"

Dijkstra::Dijkstra()
{
    // ��带 ���⼭ ����ٸ� ���⼭ �����ڸ� �ۼ��� �� �ٵ�
    // -> ��尡 �� ������ ���������? Ȥ�� ������ �����?
    // -> ���⼭ �� ���� ���� : ������ �ڵ�� ���� ����
}

Dijkstra::~Dijkstra()
{
    for (DNode* node : nodes)
        delete node;
    //'���� ���� ���'�� ������ ������ ���� �������� ��
}

void Dijkstra::Update()
{
    // �� ������ ��� ����� : �Է��� ������ �� �ڸ��� ��带 ����
    if (KEY_DOWN(VK_LBUTTON))
    {
        CreateNode(mousePos); // ��Ŭ�� �� Ŀ�� ��ġ�� ��� ����
    }

    // �� �� ���� �߰� : ���콺 ��Ŭ�� �巡�� �� ��� ����
    if (KEY_DOWN(VK_RBUTTON))
    {
        for (DNode* node : nodes)
        {
            if (node->collider->IsPointCollision(mousePos))
            {
                selectNode = node;
                break;
            }
        }
    }

    if (KEY_UP(VK_RBUTTON))
    {
        //���õ� ��尡 ������ �״�� ����
        if (selectNode == nullptr) return;

        for (DNode* node : nodes)
        {
            // �������� �������� ���Ƶ� ���� (�� ���۹̽�/��� ��ħ ���� �����ؼ� return ��� �ݺ��� ���� �����)
            if (node == selectNode) continue;

            // ������� ���� ���۹̽�/��� �ߺ� ���� �巡���� ��ġ���� ���� ����
            if (node->collider->IsPointCollision(mousePos)) //�׸��� �� ��尡 Ŀ�� ��ġ�� ��ġ��
            {
                node->AddEdge(selectNode); // �巡�� ���� ��忡 �����ߴ� ��带 ��η� �߰�
                selectNode->AddEdge(node); // �ݴ뵵 ��������
                // selectNode = nullptr; // �ɼ� : ������ ������ �����ϰ� ���� ���
                break;
            }
        }
    }

    // ���� ã�ư��� ��ɵ� �ʿ��ѵ�,
    // ��ã�� Ŭ���� �������� "���� ���� ã�ư� ���ΰ�?"�� ���� �����Ƿ� ����
    // -> ������ �ش� ����� ȣ���ϰ� �� ����...
}

void Dijkstra::Render()
{
    for (DNode* node : nodes)
        node->Render(); //��� (�� �ݶ��̴���) ����
}

int Dijkstra::FindCloseNode(Vector2 pos)
{
    float minDist = FLT_MAX; // �˻��� �� ���� ���� �ּ� �˻� �Ÿ� : �⺻���� �����찡 �ƴ� �ִ�ġ

    int result = -1; //��� �⺻�� : "����"�� -1

    for (int i = 0; i < nodes.size(); ++i)
    {
        float distance = Distance(pos, nodes[i]->pos);

        if (distance < minDist) // ���غ��� �Ÿ��� ����� ��尡 ������
        {
            minDist = distance; //������ �������ְ�
            result = i; //��� �ݿ�
        }

        //�� �ݺ����� ������ ������ ��ġ���� ���� ����� "�ֺ�" ��� �˻� �Ϸ�
    }

    return result;
}

int Dijkstra::FindMinCostNode()
{
    //�� �Լ��� ������ ����, �� ��� �Ÿ��� �ƴ� "���"

    float minCost = FLT_MAX;

    int result = -1;

    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->isClosed) continue;

        if (nodes[i]->cost < minCost)
        {
            minCost = nodes[i]->cost;
            result = i;
        }
    }

    return result;
}

void Dijkstra::SetEdgeInfo(int index)
{
    if (index == -1) return; // �ε����� "������" �ٷ� ����

    float cost = nodes[index]->cost; // ���� ����� ����� �ݿ��ؼ� ��� �ӽ� ����

    for (DNode::Edge* edge : nodes[index]->edges)
    {
        if (edge->node->cost > cost + edge->cost)
        {
            // ������ ��ϵ� �����(���� : �� ����� �Ÿ���) �� ����� ���(�⺻�� = �ִ�)���� ���ٸ�

            // �ش� ������ �ݿ�
            edge->node->cost = cost + edge->cost;
            // * ����� ��� �⺻���� �ִ�����, �� �Լ��� ȣ��� ��, �������� ����� 0�� �Ǿ��� ������ 0���� ����� ������ų �� �ִ�

            edge->node->via = index; // ����� �������� �Ű������� ���� �ε����� ��� (�� �������� ��� ������ �� ���δ�)
        }

    }

    nodes[index]->isClosed = true; // ��� ����� ���� ��, ��� �ݱ� (="�����׼� �����׷�" ���� ��� ����)
}

void Dijkstra::ResetNodes()
{
    // ��� ���� ���� : ��� �˻� �߿� �ٲ� ���� ��� ����ġ��
    // -> �⺻�� �ٽ� �Է�
    for (DNode* node : nodes)
    {
        node->isClosed = false; // "�� �� ����"
        node->via = -1;         // "������ ����"
        node->cost = FLT_MAX;   // "���, �׳� �� ���� �� ����"
    }
}

vector<Vector2> Dijkstra::GetPath(int start, int end)
{
    if (start == -1 || end == -1) return vector<Vector2>(); // �����̳� ���� ���� ��� (= ��� ������ �� �Ǹ�) �� �� ���� �ֱ� (=�׳� ����)

    //���� ������ �־����� �������� �ϰ� ����
    ResetNodes();

    // ���� �� ��� ���� �ʱ�ȭ
    int curIndex = start;
    nodes[curIndex]->cost = 0; // �� ���������� ����� 0
    nodes[curIndex]->via = start; //��� ��ĥ �ų�? -> �ϴ� �ڱ� �ڽ�

    for (DNode* node : nodes)
    {
        //����� ���� �����ϱ� (���� ���� ����)
        SetEdgeInfo(curIndex);

        // ���� ���� �Ŀ�, �� �� �ִ� ��� �߿��� �ּҺ�� ��θ� ���� ��� ����
        curIndex = FindMinCostNode();
    }
    // ������� ���� 1���� ��� ���� ���θ� �Ǵ� ����
    // 2���δ� ���� �������� �� ����� ���� �ִٸ� �ش� ��带 �ݾƼ� ó�� ����

    // �� ���������� �̷������� ��� ������ �õ��� �� ������, �� Ȯ���ϰ� �Ϸ��� ������ ���� ����

    // �˻�(Recal) / ������(Backtrack) : �ڿ��� �� �ѹ� ����
    curIndex = end;

    vector<Vector2> path; // ���� ����� ���� ���� ����

    while (curIndex != start) // ���� �ε����� ������ �� ������
    {
        path.push_back(nodes[curIndex]->pos);
        curIndex = nodes[curIndex]->via; // <- ���� ���� ���� ��򰡿��� via�� �� ��忡 �缳���Ǿ�� �Ѵٴ� ��
        
        //����� ���� �ڿ������� �� ����� ��ġ�� �������� ���ʷ� ���Ϳ� curIndex�� ���

        //����
        if (curIndex == -1) break;
    }

    //���������� ���Ϳ� ���� ��带 ����
    path.push_back(nodes[start]->pos);

    // * �� �˻��� ���� �ϴ°�? �� �ڿ������� �� �����ϴ°�?
    //   -> ��� �߿� ���̴� �κ� ������ ���� �հ谡 ����� �ٸ� ���� �־
    //      (�Ÿ��� �� ���� 1���� ª�� ���� ���� ���� ���Ѵٵ簡....)
    //      -> �˻��� ������ ���ο� �дٸ� ���� �ڵ嵵 1000% ������� �ʴ�
    //         (����� �������� �Ÿ��� �� ����̱� ������ �˻��ص� ������ ª���� ������ -> 2�� ����� ������ ����)

    //   �׷��� ���ͽ�Ʈ�� �˰����� ���ɺ��ٴ� ������ ������ ������, �����δ� ������ ������ ����

    return path;
}

void Dijkstra::CreateNode(Vector2 pos)
{
    DNode* node = new DNode(pos);
    node->index = nodes.size(); // ���� ������ ũ��(=������ ����)�� ������� ����� �ε����� ������

    nodes.push_back(node); //���� ������� ��带 ���Ϳ� �߰�
}

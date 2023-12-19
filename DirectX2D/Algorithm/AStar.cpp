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
    //��� ���� �ʱ�ȭ�� �� �߿��� ��쿡�� �Լ� �������� ���� �ʱ�ȭ���� �� ���� �ִ�
    //Reset();
    //path.clear();
    
    //��� Ž���� �Ұ����� ������ ������
    if (start == -1 || end == -1) return;

    //��ü �ʱ�ȭ
    Reset();
    path.clear();

    // ���� ���� ����
    float _g = 0;
    float _h = GetDiagonalManhattanDistance(start, end);

    nodes[start]->f = _g + _h;
    nodes[start]->g = _g;
    nodes[start]->h = _h;
    nodes[start]->via = start;
    nodes[start]->state = Node::OPEN; // ���� : �ʱ�ȭ �� NONE�̴ϱ�

    heap->Insert(nodes[start]); // �ڷῡ ù ��� �ֱ�

    while (nodes[end]->state != Node::CLOSED) // ������ ��ΰ� ��� �˻��� ������ ��尡 ������ ������
    {
        // ������ ��츦 (������ ��������) ��� �� ������

        if (heap->Empty()) //�ڷᰡ �� �������
            //break; //�ݺ����� ���� �߰� ������ ����
            return;  //�ƿ� ��� ������ ���� (�ڷᱸ���� ������� �� �� �͵� ���)

        // �ڷᰡ ���� ���� �ִٸ�....

        // ��� �߿��� ���� ���� ��� ����� ���� ��� ã��
        int curIndex = GetMinNode();

        // ã�Ƴ� �ּҺ�� ���� �ֺ� ��α��� Ž���� �ϸ鼭 �ش� ������ �ݿ��ϱ�
        Extend(curIndex, end); // ã�� �ּҺ�� ��带 �߽����� ���� Ȯ��, �� �������� ��� ���� ���ű���
        //�� �Լ� ȣ���� ������ ����� �� Ž���� ���� �� = �� ��忡���� �ٽ� ��� �� �ص� ��
        nodes[curIndex]->state = Node::CLOSED; // ��� �ݱ� (����� ������ ���� �ٽ� ���� ����)
    }

    // ������� ������ ���������� �������� ���鼭 �ּҺ�� ������ ��� �Է��� ��
    // �׸��� ����������, �� ����� ���� ���� �Էµ� �ּҺ�� ����� �������� ����(��Ʈ��ŷ)

    int curIndex = end; //���� while{} �Ȱ��� �� �ٸ� ���� ����

    while (curIndex != start) // ���ο� �ε����� �������� �� ������
    {
        nodes[curIndex]->state = Node::USING; // ��η� �̿� �� (���� �ڵ忡���� "���õǾ���!"�� ���ϱ⵵)
        path.push_back(nodes[curIndex]->pos); // ��� ���Ϳ� ���� ��ǥ�� ���� ��ġ �߰�
        curIndex = nodes[curIndex]->via;      // ���� �������� ���� �ε��� ���Ҵ�
    }

    //������� ���� ���������� ���������� ���� ��� ��� ������ path ���Ϳ� ���� �Ϸ�
    path.push_back(nodes[start]->pos); // ���������� �������� ��ġ �ֱ�
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
        // �ڱ� �ֺ� ��, �Ʒ�, �Ʒ��� �� �� ��ǥ ������ ��η� �ձ�
        // �̴�� �ݺ����� ����Ǹ� ��� ��ǥ�� 8�������� ����ǵ��� �� �� �ִ�
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
    // ��ΰ� ���� ���� ��ǥ ���ϱ�

    // ��Ģ������ �ϴ� ���
    // 1. ��� ��带 ���������� �����ϴ�
    // 2. �� ��忡�� �ڱ� �ֺ� ��η� ���� ���� �ּ� ����� �����մϴ�
    // 3. �ּҰ��� ��� ������ ��(for �ݺ���), ���� ����� ��ȯ�޽��ϴ�.
    // (���� �ڷᱸ���� �ʿ���� ���ͽ�Ʈ�� �˰����̾��ٸ� ���⼭ �ڵ带 �� ����� ���� ��)

    // �� ��꿡�� "Ư���� ��ġ�� ���� �� ����, ���� ������ ���Ѵ�"��� ������ �߰��ϸ�?
    // "�ش� ��ġ�� ���� ������� ��� ������ ��� ������ �������� �����Ѵ�" �� �Ͱ� ����� �̾߱�

    // = '��' Ŭ������ ���� Ʈ������ ���� ���� �ִ� ��尡 ���� ���ŵ� �ּ� ��� ����!

    // ���� Ʈ���� �ֻ�� ��带 �����, �ش� ��带 ���� ���� �� ����� �ε����� ��ǻ�Ϳ��� �� �ش�
    return heap->DeleteRoot()->index;

    // * Ŭ������ �� ������ ���� �ʿ����� ������� ����� ȣ�⸸ �� �ص� �ȴ�
}

//...�׸��� �� �Լ����� �ּ� ��θ� �� ���Ϸ��� �� �ȿ����� ��� ���� �־��� �� �� �־���� �Ѵ�

void AStar::Extend(int center, int end)
{
    for (Node::Edge* edge : nodes[center]->edges) //�Ű������� ���� �������� ��� ���� ������
    {
        int index = edge->index;

        //�� ���� �� ����
        if (nodes[index]->state == Node::CLOSED) continue; // �˻� �����ų� � �����ε� ���ܵ����� ����
        if (nodes[index]->state == Node::OBSTACLE) continue; //���� �ƴϾ ����

        float _g = nodes[center]->g + edge->cost; //��ǥ�� ������ 'g'�� ����� ����� ��ģ ��
        float _h = GetDiagonalManhattanDistance(index, end); // ���� ��ǥ���� ������������ "������ �Ÿ�" : �Ǵ��� �������� �ȴ�
        // ������ �밢���� ������ �ý� �Ÿ��� ��꿡 �ְ� ������, ���⿡ �׳� �ý� �Ÿ��� �� ���, �� �� ������ �񱳸� ������ �� �ִ�
        // _g�� ���� ����� ����� å��������, �������� ������ �ʹ� ũ�� �޴´�
        // _h�� ���� ����� ����� �ƴ�����, ���� �Ÿ��� å�����ָ鼭 _g�� �ʹ� ��ȸ�ϴ� ����� ���� �ʰ� �ϴ� �Ǵ� ������ �ȴ�

        float _f = _g + _h; // �� ���� ��ġ�� �񱳸� ���� ���� ����� �޾Ƴ� �� �ִ�

        //���⼭ �츮�� ����� ��� ��� ���� f, g, h�� �̸��� �����غ� �� �ִ� (*����� ���ι�������...)
        // f : Final, ���� ���
        // g : Geometric, ���� ���� ������ (��� ���)
        // h : Heuristic, "�޸���ƽ" ������ (������ ����ȭ, ���� ������ ����ġ�� ���ؼ� �Ǵ� ������ ����)

        // ���� ã�Ƴ� f ���� Ȱ��

        //�ϴ��� ��尡 "�� �� �ִ� ��"�̶�� ĥ ��
        if (nodes[index]->state == Node::OPEN)
        {
            // ��� ���� ����
            if (_f < nodes[index]->f)
            {
                nodes[index]->g = _g;
                nodes[index]->f = _f;
                // nodes[index]->h = _h; // <- ������ Ÿ���� ������ �� �ƴϴϱ� 1ȸ ��길���ε� ���. �ʿ��ϸ� ���߿� �� ����ϸ� �׸�
                nodes[index]->via = center; // ����� �������� ������ �������� �ǵ���
            }
        }
        //(�ɼ�) �����Ϳ� ���� �������� ���� �ʵ忡 �߰��Ǵ� ������ �ִٸ� (�ִٰ� �����ϰ� �ۼ�)
        else if (nodes[index]->state == Node::NONE)
        {
            //��忡 ��� ���� �� ����ֱ�
            nodes[index]->g = _g;
            nodes[index]->h = _h; // ���� ��� ���� ä���ֱ�
            nodes[index]->f = _f;
            nodes[index]->via = center;
            nodes[index]->state = Node::OPEN; // �� �� �ִ� ��� ǥ��

            heap->Insert(nodes[index]); // ��� ������ ���ο� ��� �ֱ�
        }
    }
}

void AStar::Reset()
{
    // ����� ó�� Ȥ�� ���� ������ ��� ���� ��ü �ʱ�ȭ

    for (Node* node : nodes)
    {
        if (node->state != Node::OBSTACLE)
            //node->state = Node::OPEN; //�� "�� �� ����"���� �����ϱ�
            node->state = Node::NONE; // �� Extend �Լ��� (���� �ۼ� ����) ���� �� ���, ��������� �� ������ ����� ������ ���� ����
    }

    //��尡 Open�� ���, �� ����� ������ �ϰ�/�����ؼ� heap�� �ָ� �ȴ�

    //���� �ۼ� ������ ���, �׳� heap�� ����� �ȴ� (�߰��� extend���� �� ���ִϱ�)
    heap->Clear();

    //�̷��� NONE ���µ� �� ����ϸ� ���� ���꿡 ������ �ȴ� (+������ Ȯ�强���� ������ �ȴ�)
    // -> ��� �� ��忡 ���� �κ� ������ ���� ���� �ִ� (�κ� ������ �ʿ��� ���� �ᱹ Open ��带 ���� �����ڰ� �����ؾ�)
}

// �� ����� ��� ���ϱ� (����� ����� ������ �˰��򿡼� ���ϱ� ����������,
// ���⼭�� �������� �Ÿ��� �� ����̶�� �����Ѵ�)

float AStar::GetManhattanDistance(int start, int end)
{
    // �ý� �Ÿ� : X���� �Ÿ��� Y���� �Ÿ��� �ܼ��� ���ϱ⸸ �ϸ� �ȴ� (�⺻)

    Vector2 startPos = nodes[start]->pos; //(�������� ������) ���� ��ǥ�� ���� ��ġ
    Vector2 endPos = nodes[end]->pos;     // �������� ��ġ

    Vector2 distance = endPos - startPos; //���ͷμ��� ��

    // �Լ��� ��� : x ���� �Ÿ��� y ���� �Ÿ��� �״�� ��ġ��
    return abs(distance.x) + abs(distance.y);
}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{
    // "�밢��" �ý� �Ÿ� ���ϱ� : �ϴ��� �밢���� ���Եǰ�, x, y ��ǥ���� ��꿡 �ִ� �Ÿ� ����
    // ��ü�����δ� ������ ����
    // 1. �������� ������ ���̿� ���簢�� ����� �ִٰ� ġ��, �ش� ���簢���� �밢�� ���̸� ����Ѵ�
    // 2. ���簢���� ���Ե��� �ʴ� ���� ���簢�� ������ "���� �ý� �Ÿ�"�� ����Ѵ�
    // 3. 1�� 2�� ��ģ��

    Vector2 startPos = nodes[start]->pos; //(�������� ������) ���� ��ǥ�� ���� ��ġ
    Vector2 endPos = nodes[end]->pos;     // �������� ��ġ

    Vector2 distance = endPos - startPos; //���ͷμ��� ��

    //��� ������ ������ ���밪����
    float x = abs(distance.x);
    float y = abs(distance.y);

    //�ִ� �ּ� ���ϱ�
    float maxDist = max(x, y);
    float minDist = min(x, y);

    //���� �Ÿ��� ���簢���� �밢�� ���̸� ���ļ� ���� ����� ���ϴ� ��
    return (maxDist - minDist) + sqrt(minDist * minDist * 2);

    // * ü���� ��� �����Ͻô� ���� ����Ʈ, ��, ���� �ึ�� ���÷�������. �װ� �밢�� �ý� �Ÿ��� �������� �����Դϴ�.
}
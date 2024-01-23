#include "Framework.h"

DNode::DNode(Vector2 pos)
{
    // �ڱ� ��ġ �Ű��������� �޾Ƽ� �����ϱ�
    this->pos = pos;

    //�ݶ��̴� ���� (*�˰��򺸴ٴ� ��ã�� ����/������ �� �� �ʿ��� �κ�)
    collider = new CircleCollider(30); //������ 30¥�� �� �׸���
    collider->Pos() = pos;
    collider->UpdateWorld(); // �����, �ݶ��̴��� �����, 1ȸ ������Ʈ (������ġ �ݿ��� ���ֱ�)
}

DNode::~DNode()
{
    delete collider;

    for (Edge* edge : edges)
        delete edge;
}

void DNode::Render()
{
    collider->Render();

    for (Edge* edge : edges)
        edge->line->Render();

    //collider->Render();
}

void DNode::AddEdge(DNode* node)
{
    //��忡 �̾����� �ٸ� ��尡 ���� ���, �ش� ��� ������ �߰�
    Edge* edge = new Edge(node->pos, pos); //Ÿ ���� �� ��ġ�� ���� ����
    edge->node = node; // "�̾����� ���"�� �Ű������� ���� ���� �ֱ�
    
    //�Ʒ� �ڵ��� �ʼ�, ���� ����� �ɼ�
    edge->cost = Distance(node->pos, pos);
    // D �˰��򿡼��� ��ΰ� ������ �� ��ο��� ����� �ʼ��� ���� �Ѵ�
    // ��, ���⼭�� �ش� ����� "�� ��� ������ �Ÿ�"�� �����Ѵ�
    // (�ٸ� ��� ���� ����� �ִٸ�, �ش� �������� ��ü)

    // Ÿ ���� �̾����� ��� ����, ��� å���� ������ ���Ϳ� �ֱ�
    edges.push_back(edge);
}
#pragma once

class Dijkstra
{
    // ���ͽ�Ʈ�� �˰��� ��� Ŭ���� : �� ��κ� ��� �� �� ������� ��θ� ����

public:
    //�⺻ 4�� ��Ʈ
    Dijkstra();
    ~Dijkstra();

    void Update();
    void Render();

    //���ͽ�Ʈ�� �˰����� ���� ��� ��ɵ�
    int FindCloseNode(Vector2 pos); // "�������� �������� ������ �ִ� ���� �˻�" : �ֺ��� ���� �ִ°�?
    int FindMinCostNode();          // �ּҺ�� ��� �˻�
    void SetEdgeInfo(int index); //������� ����
    
    void ResetNodes(); // ��� (����) ����

    vector<Vector2> GetPath(int start, int end); //���(����� ��) ������ (��⺸�� �ʿ䰡 ��� �Լ��θ�)

    // ������ ��� �߰��� �ʿ��� ���, �߰� �Լ� �ۼ� �� CreateNode �Լ��� �佺�ϵ��� ��ȣ��
    void CallCreateNode(Vector2 pos) { CreateNode(pos); }

private:

    //��� ���� (��)����
    void CreateNode(Vector2 pos);

    vector<DNode*> nodes; // ��ġ���� ������ ��� ���� �־�� �ϹǷ� ������ �ۼ�

    DNode* selectNode = nullptr; // ���� ���� ���� ���

};


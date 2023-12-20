#pragma once

class TerrainPicker : GameObject
{
    // Ŭ���� ���� : ���콺�� �ͷ����� ������ �ͷ����� ��ǥ�� �� �� �ֵ��� �ϱ� ����
    //              Ŭ�� �׽�Ʈ�� ����

private:
    typedef VertexUVNormalTangent VertexType; //�� Ŭ������ ���� Ÿ���� Z�� ����� ������ �����Դϴ�.
    //�� �������� �� ���� �ʿ��Ѱ�?
    //���߿� VetrexType�̶�� ���� �������̽��� �����ϸ鼭 �ٸ� Ŭ���������� ����� �ڵ��� �����ؼ�
    const float MAX_HEIGHT = 20.0f; // �ִ� ���� �̸� ���س��� (�ͷ���ó��)

public:
    TerrainPicker();
    ~TerrainPicker();

    void Update();
    void Render();
    void RenderUI();

    Vector3 Pick(); // ��� �ൿ

private:
    //�⺻ �޽� Ȥ�� ���� �ʿ��� ��ü���� ���� �����
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();

    //�ͷ����̴ϱ� ����, ����
    UINT width;
    UINT height;

    //Mesh<VertexUVNormalTangent>* mesh;
    //�� �ڵ� ���, �������� ���� Ÿ���� ������ ���� ��������
    Mesh<VertexType>* mesh;

    //�ͷ����̴ϱ� ���̸� �̸� ���� (���� ���� ���� �Ƹ� �� ��������)
    Texture* heightMap;

    Vector3 pickingPos; // ��� �ִ� ��ǥ
};


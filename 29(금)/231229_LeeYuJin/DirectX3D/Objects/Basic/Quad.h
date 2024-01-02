#pragma once

class Quad : public GameObject
{
    // 3D������ �ٽ� ���� 2D �簢�� (����) Ŭ����
    // 3D�� ������ �ֿ� ���� : �޽ø� ���� ���� ���ΰ� �ƴѰ�
    //                        ������ ������ ��� �Ǵ°�
    //                        + �ؽ�ó ���� �����Ͱ� ���� ��Ƽ����=�θ�� �Űܰ�

private:
    //������ ������ ������
    typedef VertexUV VertexType;

public:
    Quad(Vector2 size);
    Quad(wstring file); //UV ���� ���� �θ𿡼� ����
    ~Quad();

    void Render();

private:
    void MakeMesh(); // 3D�� ���߾� �Լ� ��Ī ����

protected:
    Vector2 size; // ũ�� ���� ���� ���� (�θ� �����̳� �ڱ� ũ�� ���� �ʿ��� ��� ���)

    Mesh<VertexType>* mesh;
};
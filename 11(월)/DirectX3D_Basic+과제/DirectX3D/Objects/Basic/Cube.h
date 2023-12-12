#pragma once

// ť�� : ���忡 �����ϴ� 3D�� �⺻ ��� ����. ���� ����ü

class Cube : public GameObject
{
public:
    Cube(Vector3 size = Vector3(1, 1, 1));
    ~Cube();

    void Render();

private:
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    vector<VertexColor> vertices;
    vector<UINT> indices;
};
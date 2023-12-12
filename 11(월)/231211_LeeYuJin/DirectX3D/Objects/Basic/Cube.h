#pragma once

// ť�� : ���忡 �����ϴ� 3D�� �⺻ ��� ����

class Cube : public GameObject
{
public:
    Cube(Vector3 size = Vector3(1, 1, 1));
    ~Cube();

    void FreeMode();
    void Render();

private:
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    vector<VertexColor> vertices;
    vector<UINT> indices;

    float moveSpeed = 50.0f;
    float rotSpeed = 10.0f;
};
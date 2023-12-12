#include "Framework.h"

Cube::Cube(Vector3 size)    
{
    tag = "Cube";

    // 2������ �Ѿ 3������ ���� +, - �ݿ� ��ǥ�� �߰�
    // ����ü�� ��ĥ�� ǥ���ϸ� �� �簢��, �� �簢��, �� ���� �̾��ִ� (�� ����) ���� ����
    // -> ���� �ϴ� ������ ������ �簢��(4��) + �簢��(4��) = 8��

    vertices.emplace_back(-size.x, -size.y, -size.z, 1, 0, 0);
    vertices.emplace_back(-size.x, +size.y, -size.z, 0, 1, 0);
    vertices.emplace_back(+size.x, -size.y, -size.z, 0, 0, 1);
    vertices.emplace_back(+size.x, +size.y, -size.z, 1, 1, 0);
    vertices.emplace_back(-size.x, -size.y, +size.z, 1, 0, 1);
    vertices.emplace_back(-size.x, +size.y, +size.z, 0, 1, 1);
    vertices.emplace_back(+size.x, -size.y, +size.z, 0, 0, 0);
    vertices.emplace_back(+size.x, +size.y, +size.z, 1, 1, 1);

    indices = {
        //Front
        0, 1, 2, 2, 1, 3,
        //Up
        1, 5, 3, 3, 5, 7,
        //Right
        2, 3, 6, 6, 3, 7,
        //Back
        4, 6, 5, 5, 6, 7,
        //Down
        0, 4, 1, 1, 4, 5,
        //Left
        0, 2, 4, 4, 2, 6
    };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), vertices.size());
    indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

Cube::~Cube()
{
    delete vertexBuffer;
    delete indexBuffer;
}

void Cube::FreeMode()
{
    // ���� �ʱ�ȭ
    if (KEY_PRESS('F'))
    {
        Scale() = Vector3(1, 1, 1); // ũ�� �ʱ�ȭ
        Pos()   = 0;                // ��ġ �ʱ�ȭ
        Rot() = 0;
    }

    // ��ġ�̵�
    if (KEY_PRESS('W'))
    {
        Pos().z += moveSpeed * DELTA;
    }
    
    if (KEY_PRESS('S'))
    {
        Pos().z -= moveSpeed * DELTA;
    }

    if (KEY_PRESS('A'))
    {
        Pos().x -= moveSpeed * DELTA;
    }

    if (KEY_PRESS('D'))
    {
        Pos().x += moveSpeed * DELTA;
    }

    if (KEY_PRESS('E'))
    {
        Pos().y += moveSpeed * DELTA;
    }

    if (KEY_PRESS('Q'))
    {
        Pos().y -= moveSpeed * DELTA;
    }

    // ũ�� ��ȯ
    if (KEY_PRESS('Z'))
    {
        Scale().x -= moveSpeed * DELTA;
    }

    if (KEY_PRESS('X'))
    {
        Scale().x += moveSpeed * DELTA;
    }

    // ȸ��
    if (KEY_PRESS('C'))
    {
        Rot().x -= moveSpeed * DELTA;
    }

    if (KEY_PRESS('V'))
    {
        Rot().x += moveSpeed * DELTA;
    }

    if (KEY_PRESS('B'))
    {
        Rot().y -= moveSpeed * DELTA;
    }

    if (KEY_PRESS('N'))
    {
        Rot().y += moveSpeed * DELTA;
    }
}

void Cube::Render()
{
    if (!isActive) return;

    vertexBuffer->Set();
    indexBuffer->Set();

    SetRender();

    DC->DrawIndexed(indices.size(), 0, 0);
}

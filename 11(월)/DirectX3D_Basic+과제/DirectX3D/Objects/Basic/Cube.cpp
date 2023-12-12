#include "Framework.h"

Cube::Cube(Vector3 size)    
{
    tag = "Cube";

    // 2차원을 넘어서 3차원에 대한 +, - 반영 좌표를 추가
    // 육면체는 거칠게 표현하면 앞 사각형, 뒤 사각형, 이 둘을 이어주는 (네 개의) 면들로 구성
    // -> 찍어야 하는 정점의 개수는 사각형(4개) + 사각형(4개) = 8개

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

void Cube::Render()
{
    if (!isActive) return;

    vertexBuffer->Set();
    indexBuffer->Set();

    SetRender();

    DC->DrawIndexed(indices.size(), 0, 0);
}

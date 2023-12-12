#include "Framework.h"

Cube::Cube(Vector3 size)    
{
    tag = "Cube";

    mesh = new Mesh<VertexType>();
    vector<VertexType>& vertices = mesh->GetVertices();
    //Front
    vertices.emplace_back(-size.x, -size.y, -size.z, 0, 1); // B
    vertices.emplace_back(-size.x, +size.y, -size.z, 0, 0); // L
    vertices.emplace_back(+size.x, -size.y, -size.z, 1, 1); // R
    vertices.emplace_back(+size.x, +size.y, -size.z, 1, 0); // T

    //Up
    vertices.emplace_back(-size.x, +size.y, -size.z, 0, 1); // 2 0 | 4
    vertices.emplace_back(-size.x, +size.y, +size.z, 0, 0); // 0 1 | 5
    vertices.emplace_back(+size.x, +size.y, -size.z, 1, 1); // 3 2 | 6
    vertices.emplace_back(+size.x, +size.y, +size.z, 1, 0); //   3 | 7

    //Left
    vertices.emplace_back(+size.x, +size.y, -size.z, 0, 1);
    vertices.emplace_back(+size.x, +size.y, +size.z, 0, 0);
    vertices.emplace_back(+size.x, -size.y, -size.z, 1, 1);
    vertices.emplace_back(+size.x, -size.y, +size.z, 1, 0);

    //Right
    vertices.emplace_back(-size.x, +size.y, -size.z, 0, 1);
    vertices.emplace_back(-size.x, -size.y, -size.z, 0, 0);
    vertices.emplace_back(-size.x, +size.y, +size.z, 1, 1);
    vertices.emplace_back(-size.x, -size.y, +size.z, 1, 0);

    //Back
    vertices.emplace_back(-size.x, +size.y, +size.z, 0, 1);
    vertices.emplace_back(-size.x, -size.y, +size.z, 0, 0);
    vertices.emplace_back(+size.x, +size.y, +size.z, 1, 1);
    vertices.emplace_back(+size.x, -size.y, +size.z, 1, 0);

    //Down
    vertices.emplace_back(-size.x, -size.y, -size.z, 0, 1); // 2 3
    vertices.emplace_back(+size.x, -size.y, -size.z, 0, 0); //   3 
    vertices.emplace_back(-size.x, -size.y, +size.z, 1, 1); // 0 1
    vertices.emplace_back(+size.x, -size.y, +size.z, 1, 0); // 2 2

    vector<UINT>& indices = mesh->GetIndices();
    indices = {
        //Front
        0, 1, 2, 2, 1, 3, // L -> B -> T -> T -> B -> R

        //Up
        4, 5, 6, 6, 5, 7,


        //Right
        8, 9, 10, 10, 9, 11,

        //Left
        12, 13, 14, 14, 13, 15,

        //Back
        16, 17, 18, 18, 17, 19,

        //Down
        20, 21, 22, 22, 21, 23
        //20, 21, 22
    };

    mesh->CreateMesh();
}

Cube::~Cube()
{
    delete mesh;
}

void Cube::Render()
{
    if (!isActive) return;    

    SetRender();

    mesh->Draw();
}

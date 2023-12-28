#pragma once

class Cube : public GameObject
{
private:
    typedef VertexUV VertexType;

public:
    Cube(Vector3 size = Vector3(1, 1, 1));
    ~Cube();

    void Render();

private:
    Mesh<VertexType>* mesh;
};
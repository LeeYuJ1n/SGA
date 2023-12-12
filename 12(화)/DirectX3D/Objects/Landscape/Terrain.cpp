#include "Framework.h"

Terrain::Terrain() : width(10), height(10)
{    
    material->SetDiffuseMap(L"Textures/Landscape/Dirt.png");
        
    CreateMesh();    
}

Terrain::~Terrain()
{
    delete material;
    delete mesh;    
}

void Terrain::Render()
{
    GameObject::SetRender();
    mesh->Draw();
}

void Terrain::CreateMesh()
{
    mesh = new Mesh<VertexType>();

    //Vertices
    vector<VertexType>& vertices = mesh->GetVertices();

    vertices.reserve(width * height);
    for (UINT z = 0; z < height; z++)
    {
        for (UINT x = 0; x < width; x++)
        {
            VertexType vertex;
            vertex.pos = { (float)x, 0.0f, (float)z };
            vertex.uv.x = x / (float)(width - 1);
            vertex.uv.y = z / (float)(height - 1);

            vertices.push_back(vertex);
        }
    }

    //Indices
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve((width - 1) * (height - 1) * 6);

    for (UINT z = 0; z < height - 1; z++)
    {
        for (UINT x = 0; x < width - 1; x++)
        {
            indices.push_back(width * z + x);//0
            indices.push_back(width * (z + 1) + x);//1
            indices.push_back(width * z + x + 1);//2

            indices.push_back(width * z + x + 1);//2
            indices.push_back(width * (z + 1) + x);//1
            indices.push_back(width * (z + 1) + x + 1);//3
        }
    }

    mesh->CreateMesh();
}

#include "Framework.h"
#include "GridScene.h"

GridScene::GridScene()
    : width(MAX_VALUE), height(MAX_VALUE)
{
    material = new Material(L"Basic/Grid.hlsl");

    CreateMesh();

    worldBuffer = new MatrixBuffer();    
}

GridScene::~GridScene()
{
    delete material;
    delete mesh;
    delete worldBuffer;
}

void GridScene::Update()
{
}

void GridScene::PreRender()
{
}

void GridScene::Render()
{
    worldBuffer->SetVS(0);

    material->Set();
    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void GridScene::PostRender()
{
}

void GridScene::GUIRender()
{
    if (ImGui::TreeNode("GridOption"))
    {
        ImGui::DragInt("Width", (int*)&width, 0, MAX_VALUE);
        ImGui::DragInt("Height", (int*)&height, 0, MAX_VALUE);

        ImGui::TreePop();
    }
}

void GridScene::CreateMesh()
{
    mesh = new Mesh<VertexColor>();   

    vector<VertexColor>& vertices = mesh->GetVertices();

    //Axis X
    vertices.emplace_back(-MAX_VALUE, 0, 0, 1, 0, 0);
    vertices.emplace_back(+MAX_VALUE, 0, 0, 1, 0, 0);

    //Axis Y
    vertices.emplace_back(0, -MAX_VALUE, 0, 0, 1, 0);
    vertices.emplace_back(0, +MAX_VALUE, 0, 0, 1, 0);

    //Axis Z
    vertices.emplace_back(0, 0, -MAX_VALUE, 0, 0, 1);
    vertices.emplace_back(0, 0, +MAX_VALUE, 0, 0, 1);

    int halfW = width / 2;
    int halfH = height / 2;

    for (int x = -halfH; x <= halfH; x++)
    {
        if (x == 0) continue;

        vertices.emplace_back(x, 0, -halfH, 0.5f, 0.5f, 0.5f);
        vertices.emplace_back(x, 0, +halfH, 0.5f, 0.5f, 0.5f);
    }

    for (int z = -halfW; z <= halfW; z++)
    {
        if (z == 0) continue;

        vertices.emplace_back(-halfW, 0, z, 0.5f, 0.5f, 0.5f);
        vertices.emplace_back(+halfW, 0, z, 0.5f, 0.5f, 0.5f);
    }

    mesh->CreateMesh();
}

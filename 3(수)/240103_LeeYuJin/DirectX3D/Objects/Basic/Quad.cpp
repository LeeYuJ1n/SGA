#include "Framework.h"

Quad::Quad(Vector2 size)
    : GameObject(L"Basic/Texture.hlsl"), size(size)
{
    //�޽� �����
    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

Quad::Quad(wstring file)
    : GameObject(L"Basic/Texture.hlsl")
{
    Texture* texture = Texture::Add(file); // �ؽ�ó Ŭ������ ���ҽ� ��� ��
    material->SetDiffuseMap(file); //��ǻ�� ������ ���
    size = texture->GetSize();

    //�޽� �����
    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

Quad::~Quad()
{    
    delete mesh;
}

void Quad::Render()
{
    //3D ���� ȣ��
    SetRender();
    mesh->Draw();
}

void Quad::MakeMesh()
{
    // �׸��� �� �� �����ϱ� (2D�� 3D�� �⺻�� ����)
    float left = -size.x * 0.5f;
    float right = +size.x * 0.5f;
    float top = +size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    // �޽� �����Ϳ��� ���� �ҷ�����
    vector<VertexType>& vertices = mesh->GetVertices();

    //3D�� ������ �°� ���� ���� (�� ���� ����, �ٸ� ���� ����, ���θ� ����ϵ���)
    vertices.emplace_back(left, top, 0, 0, 0);
    vertices.emplace_back(right, top, 0, 1, 0);
    vertices.emplace_back(left, bottom, 0, 0, 1);
    vertices.emplace_back(right, bottom, 0, 1, 1);

    // �޽� �����Ϳ��� �ε��� ���� �ҷ�����
    vector<UINT>& indices = mesh->GetIndices();

    // �ش� ���� ������ �ٽ� �Ҵ� (2D ���� ���� = 2D�� ���ݰ� ���Ҵ�)
    indices = { 0, 1, 2, 2, 1, 3 };
}
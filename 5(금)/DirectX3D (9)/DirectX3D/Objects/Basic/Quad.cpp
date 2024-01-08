#include "Framework.h"

Quad::Quad(Vector2 size)
    : GameObject(L"Basic/Texture.hlsl"), size(size)
{
    //메시 만들기
    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

Quad::Quad(wstring file)
    : GameObject(L"Basic/Texture.hlsl")
{
    Texture* texture = Texture::Add(file); // 텍스처 클래스에 리소스 등록 후
    material->SetDiffuseMap(file); //디퓨즈 맵으로 등록
    size = texture->GetSize();

    //메시 만들기
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
    //3D 렌더 호출
    SetRender();
    mesh->Draw();
}

void Quad::MakeMesh()
{
    // 그림의 네 변 도출하기 (2D나 3D나 기본은 같다)
    float left = -size.x * 0.5f;
    float right = +size.x * 0.5f;
    float top = +size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    // 메시 데이터에서 정점 불러오기
    vector<VertexType>& vertices = mesh->GetVertices();

    //3D용 정점에 맞게 정보 수정 (한 축은 고정, 다른 축은 가로, 세로를 담당하도록)
    vertices.emplace_back(left, top, 0, 0, 0);
    vertices.emplace_back(right, top, 0, 1, 0);
    vertices.emplace_back(left, bottom, 0, 0, 1);
    vertices.emplace_back(right, bottom, 0, 1, 1);

    // 메시 데이터에서 인덱스 벡터 불러오기
    vector<UINT>& indices = mesh->GetIndices();

    // 해당 벡터 내용을 다시 할당 (2D 때와 같다 = 2D가 지금과 같았다)
    indices = { 0, 1, 2, 2, 1, 3 };
}
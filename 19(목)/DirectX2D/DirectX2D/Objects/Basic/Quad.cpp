#include "Framework.h"

Quad::Quad(Vector2 size, Vector2 pos)    
{
    CreateMesh(size, pos);
}

Quad::Quad(wstring file, Vector2 pos)
{
    SetTexture(file);             //그림 파일에서 텍스처를 받고
    size = texture->GetSize();    //파일의 정보에서 크기를 구하고
    CreateMesh(size, pos);        //텍스처에 맞게 메시를 역생성
}

Quad::Quad(bool useTrim, wstring file, Vector2 startUV, Vector2 endUV)
{
    SetTexture(file);
    size = (endUV - startUV) * texture->GetSize(); // 참조 크기(비율)만큼을 텍스처에 또 곱하기
    CreateMesh(size, startUV, endUV);

    colorBuffer = new ColorBuffer();
}

//텍스처 지정 (나중에 단색 메시에도 텍스처를 입힐 수 있도록 하려고)
void Quad::SetTexture(wstring file)
{
    texture = Texture::Add(file);
}

Quad::~Quad()
{

}

void Quad::Render()
{
    if (colorBuffer != nullptr)
    {
        colorBuffer->SetPS(0);
    }

    //텍스처도 픽셀 셰이더를 세팅
    texture->PSSet();

    //기본 : 게임오브젝트 출력
    // - 상속된 클래스는 기본적으로 부모와 같은 함수 구성을 가진다
    //   그런데 필요에 따라 부모의 함수를 오버라이드 했을 경우
    //   부모의 함수 기능을 유지하기 위해서, "부모 클래스의 함수"를
    //   정확히 지정해서 직접 호출할 수도 있다
    GameObject::Render(); // <-쿼드의 렌더 함수에서, 게임오브젝트의 렌더 함수를 직접 호출 실행
}

void Quad::CreateMesh(Vector2 size, Vector2 pos)
{
    //사각형이 사각형으로서 존재하기 위한 형태를 여기서 만든다
    // 처음 배웠을 때는 "버텍스 인덱스 만들기"였던 이 과정을
    // 다이렉트x 환경에서는 "메시 조형(만들기)"이라고 부르는 것

    float left   = pos.x - size.x * 0.5f;
    float right  = pos.x + size.x * 0.5f;
    float top    = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

    vertices.emplace_back(left, top, 0, 0);
    vertices.emplace_back(right, top, 1, 0);
    vertices.emplace_back(left, bottom, 0, 1);
    vertices.emplace_back(right, bottom, 1, 1);

    indices = { 0, 1, 2, 2, 1, 3 };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());
    indexBuffer  = new IndexBuffer(indices.data(), indices.size());
}

void Quad::CreateMesh(Vector2 size, Vector2 startUV, Vector2 endUV)
{
    float left   = -size.x * 0.5f;
    float right  = size.x * 0.5f;
    float top    = size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    vertices.emplace_back(left, top, startUV.x, startUV.y);
    vertices.emplace_back(right, top, endUV.x, startUV.y);
    vertices.emplace_back(left, bottom, startUV.x, endUV.y);
    vertices.emplace_back(right, bottom, endUV.x, endUV.y);

    indices = { 0, 1, 2, 2, 1, 3 };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());
    indexBuffer  = new IndexBuffer(indices.data(), indices.size());
}
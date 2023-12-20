#include "Framework.h"

TerrainPicker::TerrainPicker()
{
    width = 10;
    height = 10;

    mesh = new Mesh<VertexType>(); //부정형 기본 메쉬
    //형태 잡기
    MakeMesh();
    MakeNormal();
    MakeTangent();
    mesh->CreateMesh();
}

TerrainPicker::~TerrainPicker()
{
    delete mesh;
    // delete heightMap; //텍스처로 들어간 거니까 (지워질 땐 텍스처에서 지워짐)
}

void TerrainPicker::Update()
{

}

void TerrainPicker::Render()
{

}

void TerrainPicker::RenderUI()
{

}

void TerrainPicker::MakeMesh()
{
    //터레인 (혹은 관련 자료가 없다면 그냥 흰 종이라도) 만들기

    //화소의 벡터 만들기 (매개변수는 벡터의 크기, 그리고 기본값)
    vector<Float4> pixels(width * height, Float4(0, 0, 0 ,0));

    //높이 맵이 있으면 적용하기
    if (heightMap)
    {
        //가로 세로를 (그림 크기에 맞춰서) 다시 받아오기
        width = (UINT)heightMap->GetSize().x;
        height = (UINT)heightMap->GetSize().y;

        heightMap->ReadPixels(pixels); //텍스터에서 그림의 픽셀 정보 가져오기
    }

    //정점 찍기

    vector<VertexType>& vertices = mesh->GetVertices();

    vertices.reserve(width * height); //벡터 크기 예약

    for (UINT z = 0; z < height; ++z)
    {
        for (UINT x = 0; x < width; ++x)
        {
            VertexType vertex;
            vertex.pos = { (float)x, 0, (float)(height - z - 1) };
            //텍스처 위치도 정하기
            vertex.uv.x = x / (float)(width - 1);
            vertex.uv.y = z / (float)(height - 1);
            //위 코드에서 앞-뒤(z)를 텍스처 y에 배정하는 이유 : 그림을 눕힐 수 있으니까 (터레인답게)

            //정점 인덱스 미리 정해놓기 (나중에 인덱스 짜기)
            UINT index = (width * z) + x;
            //높이 맵에서 따온 높이 정하기 (높이 맵이 흰색이나 빨간색이라고 가정)
            vertex.pos.y = pixels[index].x * MAX_HEIGHT; //벡터 기본값 이용 (아까 넣은 벡터의 기본값이 무엇이냐에 영향)
            //vertex.pos.y = 0 * MAX_HEIGHT; // 평평하게

            //다 만든 정점 벡터에 넣읍시다
            vertices.push_back(vertex);
        }
    }

    //인덱스 넣기 (텍스처 출력 및 4각형 면 채우기용 : 터레인과 큐브 참고)
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve((width - 1) * (height - 1) * 6);

    for (UINT z = 0; z < height - 1; ++z)
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            //현재 순번이 돌아온 점과 옆 점들 ( 0 > 1 > 2 )
            indices.push_back(width * z + 1);
            indices.push_back(width * z + x + 1);
            indices.push_back(width * (z + 1) + x);

            //다시 옆 점들과 대각선 다음 점까지! ( 2 > 1 > 3 )
            indices.push_back(width * (z + 1) + x);
            indices.push_back(width * z + x + 1);
            indices.push_back(width * (z + 1) + x + 1);

            //이렇게 삼각형 두 번 돌리면 사각형 가능
        }
    }
}

void TerrainPicker::MakeNormal()
{

}

void TerrainPicker::MakeTangent()
{

}
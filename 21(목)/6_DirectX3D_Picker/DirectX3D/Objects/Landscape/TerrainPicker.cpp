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
    // Pick 함수 호출 : 그림을 클릭하면 좌표를 알 수 있도록
    if (KEY_PRESS(VK_LBUTTON))
    {
        pickingPos = Pick(); // 찍고 있는 좌표는 찌긱 함수의 결과다
    }
}

void TerrainPicker::Render()
{
    // 렌더는 만들어진 메시를 그대로 Draw 호출로 그려만 주면 된다

    // 렌더 세팅 ( 게임오브젝트에서 정해진 대로 )
    GameObject::SetRender();

    // 메시에서 그리기 호출
    mesh->Draw();
}

void TerrainPicker::RenderUI()
{
    ImGui::Text("Terrain Pick Position");
    ImGui::Text("X : %.1f, Y : %.1f, Z : %.1f", pickingPos.x, pickingPos.y, pickingPos.z);
    // 서식 문자를 사용해서 변수를 디버그 패널에 텍스트 출력
}

Vector3 TerrainPicker::Pick()
{
    // 고르기 : 호출되면 호출된 곳의 좌표를 반환하기
    // -> 마우스 커서에서 시작된 광선 ( 레이캐스트 ) 이 물체에 부딪쳐서 나온 내부의 좌표를
    //    컴퓨터에게 반환하기

    // 레이캐스트 필요 : 
    Ray ray = CAM->ScreenPointToRay(mousePos);

    // 만들어진 터레인의 가로 세로를 모두 검사해서 충돌이 일어났는지 검사 해야 하는데
    // 현재 터레인이 따로 충돌체는 없다 : 대신할 수 있는 "점 겹침"이라는 것을 호출 ( 임시 암기용 새 함수 등장 )

    for (UINT z = 0; z < height - 1; ++z)
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            UINT index[4]; // 영역 검사라서 점 4개 = 사각형의 꼭짓점 필요
            
            index[0] = width * z + x;
            index[1] = width * z + (x + 1);
            index[2] = width * (z + 1) + x;
            index[3] = width * (z + 1) + (x + 1);

            // 정점 받기
            vector<VertexType> vertices = mesh->GetVertices();

            // 정점과 인덱스 ( 가로 세로 좌표 ) 를 대조해서 살제 위치 받기
            Vector3 p[4];

            for (UINT i = 0; i < 4; ++i)
            {
                p[i] = vertices[index[i]].pos; // 위에서 만든 인덱스의 i번째의 벡터상 위치
            }

            float distance = 0; // 거리 변수 준비하고 초기화

            // TruangleTests : DX에서 주는 레이캐스트 및 폴리곤 ( 3차원 표현 단위 ) 간의 충돌을 시험하기 위한 디버그 기능 집합
            //                 ( DX는 레이캐스트도 지원하고 폴리곤도 지원하지만, 이들 간의 상호작용 지원은 기본적으로는 하지 않는다... 제한적으로 이렇게 사용은 가능 )
            //                 
            if (TriangleTests::Intersects(ray.pos, ray.dir, p[0], p[1], p[2], distance))
            {
                // 폴리고 및 선분 ( 레이캐스트 ) 접점이 생겼으면 해당 정보를 그대로 계산해서 벡터로 반환
                return ray.pos + ray.dir * distance; // 광원에서 접점까지 거리만큼, 광선 방향으로 가면 해당 벡터 나옴
                // return height - (ray.pos + ray.dir * distance); // 그림이 뒤집혔을 때
            }

            // 여기까지 오면 사각형을 이루는 0-1-2 삼각형과 레이 간 충돌 판별이 이루어진 것
            // 그러므로 남은 3-1-2 삼각형도 확인

            if (TriangleTests::Intersects(ray.pos, ray.dir, p[3], p[1], p[2], distance))
            {
                return ray.pos + ray.dir * distance;
                // return height - (ray.pos + ray.dir * distance);
            }
        }
    }

    // 여기까지 왔다면 그림을 돌리는 동안 광선과 그림에 접점이 없었다

    // 그러므로 아무거나 반환
    return Vector3(0, 0, 0); // 0, 0, 0 기본 결과만 반환
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

            // 지형 변경하기
            // if (x == 5 && z == 5) vertex.pos.y = 30.0f;

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
            indices.push_back(width * z + x);
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
    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
        // 3으로 나누는 이유 : 면 하나마다 새로운 법선 1개 만들기가 목적인데
        // 정점 3개가 모일 때 조각으로 된 면 하나가 나오니까
    {
        // 이 반복문에서 i는 반복문의 수행 인덱스,
        // 코드에서 실제로 써야 할 인덱스는 i에서 다시 계산
        UINT index0 = indices[i * 3];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 v0 = vertices[index0].pos;
        Vector3 v1 = vertices[index1].pos;
        Vector3 v2 = vertices[index2].pos;

        // 정점에서 면을 이루는 두 벡터 (정점끼리의 격차) 가져오기
        // 삼각형의 두 변이라고 생각할 수도
        Vector3 e0 = v1 - v0;
        Vector3 e1 = v2 - v0;

        // 두 변에서 새로운 법선(반사면, 곡면) 도출하고 정규화
        Vector3 normal = Cross(e0, e1).GetNormalized(); // 정규화

        // 새로 만들어진 법선의 정보를 지금 쓰이는 정점에 포함된 법선 정보에 기입
        vertices[index0].normal = normal + vertices[index0].normal;
        vertices[index1].normal = normal + vertices[index1].normal;
        vertices[index2].normal = normal + vertices[index2].normal;
        // 원 정보에 계속 법선 정보를 누적시켜서, 해당 정점에 대한 곡면 정보를 완성

        // 여기까지 왔을 때, 지형의 1차 곡면을 만들 수 있다
        // = 정점의 모양 그 자체에서 도출된 실제적인 법선 정보
    }
}

void TerrainPicker::MakeTangent()
{
    // 위에 있는 법선 만들기와 기본 원리도 목적도 같다 : 기준만 다르다
    // 법선 만들기의 기준 : 정점 ( 진짜 모양 )
    // 이 함수의 기준 : 텍스처UV ( 그림의 구성 )
    // = 그림에 노멀맵 같은 것들이 적용되거나, 타일 등으로 구성이 달라지면
    //   거기서 나오는 정보도 곡면 표시에 반영을 하기 위함

    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
    {
        UINT index0 = indices[i * 3];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        // 똑같이 점을 가져오기 ( 엄밀히 말하면 정점은 아니므로 p포인트로 지칭 )
        Vector3 p0 = vertices[index0].pos;
        Vector3 p1 = vertices[index1].pos;
        Vector3 p2 = vertices[index2].pos;

        // 그림이 기준이 되려고 하니까 그림 = UV좌표도 가져오기
        Vector2 uv0 = vertices[index0].uv;
        Vector2 uv1 = vertices[index1].uv;
        Vector2 uv2 = vertices[index2].uv;

        // 위 함수와 같이 두 변 차이 구하기
        Vector3 e0 = p1 - p0;
        Vector3 e1 = p2 - p0;

        // 탄젠트 각도를 위한 UV 구성요소 ( UV간 차이 ) 구하기
        float u1 = uv1.x - uv0.x; // u : 텍스처의 x를 의미
        float v1 = uv1.y - uv0.y; // v : 텍스처의 y를 의미
        float u2 = uv2.x - uv0.x;
        float v2 = uv2.y - uv0.y;

        // 위 계산을 통해서 색조, 혹은 기타 UV정보가 바뀐다

        // 해당 UV의 차이를 실제로 계산에서 도출
        float d = 1.0f / (u1 * v2 - u2 * v1); // 색조 ( 방향 ) 공식
        
        // 여기 나온 d를 정점 정보와 합치기 ( 스칼라 연산 )
        Vector3 tangent = d * (e0 * v2 - e1 * v1);

        // 도출된 텍스처 보정 각도 ( 탄젠트 ) 를 정점이 가진 정보에 또 합산
        vertices[index0].tangent += tangent;
        vertices[index1].tangent += tangent;
        vertices[index2].tangent += tangent;
    }
}
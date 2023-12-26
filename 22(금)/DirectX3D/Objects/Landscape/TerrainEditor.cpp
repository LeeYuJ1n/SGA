#include "Framework.h"

TerrainEditor::TerrainEditor() 
    : GameObject(L"Landscape/TerrainEditor.hlsl"),
    width(MAX_SIZE), 
    height(MAX_SIZE)
{
    // 메시 만들기 ( 기본, 부정형 )
    mesh = new Mesh<VertexType>();

    // 메시 만들기 ( 성형 )
    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData(); // 생성된 결과로 생성 시점에서 먼저 만들기

    mesh->CreateMesh();

    // 연산 셰이더를 셰이더 사전 설정 파일에서 지정
    computeShader = Shader::AddCS(L"Compute/ComputePicking.hlsl");

    // 편집에 쓸 편집도구 초기화
    brushBuffer = new BrushBuffer();

    // 건축 과정에서 오가는 데이터를 보존 및 적용할 버퍼
    structuredBuffer = new StructuredBuffer(
        inputs.data(), sizeof(InputDesc), triangleSize,
                       sizeof(OutputDesc), triangleSize);

    // 스트럭처 버퍼 ( 건축 버퍼 ) 에 들어간 매개변수 : 
    // 입력에 들어갈 데이터 / 입력의 데이터 규모 / 입력에 규모
    //                     / 출력의 데이터 규모 / 출력의 규모

    rayBuffer = new RayBuffer();
}

TerrainEditor::~TerrainEditor()
{
    delete mesh;
    delete brushBuffer;
    delete rayBuffer;
    delete structuredBuffer;
}

void TerrainEditor::Update()
{
    if (KEY_PRESS(VK_LBUTTON))
    {
        brushBuffer->Get().pickingPos = ComputePick();
    }
}

void TerrainEditor::Render()
{
    // 만든 결과 확인
    brushBuffer->SetPS(10);

    SetRender();

    mesh->Draw();
}

void TerrainEditor::RenderUI()
{
    // 디버그 판에서 확인

    // 타이틀
    ImGui::Text("Terrain Editor ( Option )");

    if (ImGui::DragInt("Width", (int*)&width, 1.0f, 2, MAX_SIZE))
        Resize(); // 크기가 바뀌면 리사이즈

    if (ImGui::DragInt("Height", (int*)&height, 1.0f, 2, MAX_SIZE))
        Resize(); // 크기가 바뀌면 리사이즈

    // 나중에 쓸 부분 미리
    ImGui::DragFloat("Range", &brushBuffer->Get().range, 1.0f, 1.0f, 20.0f);
    ImGui::ColorEdit3("Color", (float*)& brushBuffer->Get().color);

    // 픽커에서 따온 좌표 참조 위치
    ImGui::Text("Terrain Pick Position");
    ImGui::Text("X : %.1f, Y : %.1f, Z : %.1f",
        brushBuffer->Get().pickingPos.x,
        brushBuffer->Get().pickingPos.y, 
        brushBuffer->Get().pickingPos.z);
}

Vector3 TerrainEditor::Pick()
{
    Ray ray = CAM->ScreenPointToRay(mousePos);

    for (UINT z = 0; z < height - 1; ++z)
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            UINT index[4];

            index[0] = width * z + x;
            index[1] = width * z + (x + 1);
            index[2] = width * (z + 1) + x;
            index[3] = width * (z + 1) + (x + 1);

            // 정점 받기
            vector<VertexType> vertices = mesh->GetVertices();

            Vector3 p[4];

            for (UINT i = 0; i < 4; ++i)
            {
                p[i] = vertices[index[i]].pos;
            }

            float distance = 0;
               
            if (TriangleTests::Intersects(ray.pos, ray.dir, p[0], p[1], p[2], distance))
            {
                return ray.pos + ray.dir * distance;
            }

            if (TriangleTests::Intersects(ray.pos, ray.dir, p[3], p[1], p[2], distance))
            {
                return ray.pos + ray.dir * distance;
            }
        }
    }

    // 여기까지 왔다면 그림을 돌리는 동안 광선과 그림에 접점이 없었다

    // 그러므로 아무거나 반환
    return Vector3(0, 0, 0); // 0, 0, 0 기본 결과만 반환
}

Vector3 TerrainEditor::ComputePick()
{
    // 목적 : 골랐을 때, 위치를 바로 반환만 하기보다, 아예 그 과정에서
    // 컴퓨트 데이터에 반영까지 해보기를 목표로

    Ray ray = CAM->ScreenPointToRay(mousePos);

    // 광선 버퍼에 광선 버퍼 정보 저장
    rayBuffer->Get().pos = ray.pos;
    rayBuffer->Get().dir = ray.dir;
    rayBuffer->Get().triangleSize = triangleSize; // 현재의 입력규모를 광선버퍼에도
    rayBuffer->SetCS(0); // 0번에 할당

    DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
    // 리소스에서 셰이더 세팅하기 ( 셰이더 슬롯, 보려는 뷰포트 개수, 원본 리소스 )

    // 출력요청, 접근 등을 그대로 출력하는 기능
    DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

    // 설정된 연산 셰이더를 세팅
    computeShader->Set();

    UINT x = ceil((float)triangleSize / 64.0f); // 입력 규모에서 값 x를 받을 텐데, 올림(ceil) 방식으로 받기

    DC->Dispatch(x, 1, 1); // 연산 셰이더 출력 환경에서 해당 CS의 작업 비중, 크기, 빈도 등을 조절하는 기능

    structuredBuffer->Copy(outputs.data(), sizeof(OutputDesc) * triangleSize); // 건축 버퍼 데이터를 출력에 저장

    float minDistance = FLT_MAX; // 최소거리 임시값 저장
    int minIndex = -1; // 최소 순번 임시값 저장

    UINT index = 0; // 순번 임시값으로 초기화

    // 위에서 나온 출력 결과 모두 반복문으로 호출
    for (OutputDesc output : outputs)
    {
        if (output.picked) // 선택 여부가 코드로 남아있다 = true
        {
            if (output.distance < minDistance) // 마지막으로 계측된 최소 거리보다 현재 출력데이터 거리가 작다면
            {
                minDistance = output.distance; // 갱신
                minIndex    = index;           // 갱신된 거리의 원본 출력 데이터의 순번
            }
        }

        ++index; // 반복문 수행 시마다 인덱스 +1

        // 이 반복문을 수행함으로써 출력 데이터 사이에서 "거리"가 제일 짧은 출려 결과를 얻어낼 수 있다
        // -> 광원에서 표면에 다다르는 최소 거리 = 직선 거리를 도출 가능
    }

    // 여기까지 왔을 때 index의 값이 -1이 아니면 ( index가 "있다면" )
    // 광원에서 물체로 가는 광선 충돌이 났다는 이야기
    // 해당 위치를 판별하는 과정에서 output이 버퍼를 통해 저장이 되기도 했다

    // 그러므로 해당 결과를 반환까지 해주면 된다

    // * 중간 힌트 : 이쯤에서 메시의 정점을 바꿔줄 수 있다면, 
    //              지형의 모양을 어느 정도 바꿔주는 게 가능할 겁니다!!

    if (minIndex > -1)
    {
        return ray.pos + ray.dir * minDistance; // 광원, 광선 방향, 측정된 직선거리
    }

    // 그렇지 않다면 충돌이 없었던 것 ( 따라서 반영할 다른 입력 결과도 없었던 것 )
    return Vector3();
}

void TerrainEditor::MakeMesh()
{
    vector<Float4> pixels(width * height, Float4(0, 0, 0, 0));

    if (heightMap)
    {
        width = (UINT)heightMap->GetSize().x;
        height = (UINT)heightMap->GetSize().y;

        heightMap->ReadPixels(pixels);
    }

    vector<VertexType>& vertices = mesh->GetVertices();

    vertices.reserve(width * height);

    for (UINT z = 0; z < height; ++z)
    {
        for (UINT x = 0; x < width; ++x)
        {
            VertexType vertex;
            vertex.pos = { (float)x, 0, (float)(height - z - 1) };
            
            vertex.uv.x = x / (float)(width - 1);
            vertex.uv.y = z / (float)(height - 1);
            
            UINT index = (width * z) + x;

            vertex.pos.y = pixels[index].x * MAX_HEIGHT;

            vertices.push_back(vertex);
        }
    }

    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve((width - 1) * (height - 1) * 6);

    for (UINT z = 0; z < height - 1; ++z)
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            indices.push_back(width * z + x);
            indices.push_back(width * z + x + 1);
            indices.push_back(width * (z + 1) + x);

            indices.push_back(width * (z + 1) + x);
            indices.push_back(width * z + x + 1);
            indices.push_back(width * (z + 1) + x + 1);
        }
    }
}

void TerrainEditor::MakeNormal()
{
    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
    {
        UINT index0 = indices[i * 3];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 v0 = vertices[index0].pos;
        Vector3 v1 = vertices[index1].pos;
        Vector3 v2 = vertices[index2].pos;

        Vector3 e0 = v1 - v0;
        Vector3 e1 = v2 - v0;

        Vector3 normal = Cross(e0, e1).GetNormalized();

        vertices[index0].normal = normal + vertices[index0].normal;
        vertices[index1].normal = normal + vertices[index1].normal;
        vertices[index2].normal = normal + vertices[index2].normal;
    }
}

void TerrainEditor::MakeTangent()
{
    vector<VertexType>&vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
    {
        UINT index0 = indices[i * 3];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 p0 = vertices[index0].pos;
        Vector3 p1 = vertices[index1].pos;
        Vector3 p2 = vertices[index2].pos;

        Vector2 uv0 = vertices[index0].uv;
        Vector2 uv1 = vertices[index1].uv;
        Vector2 uv2 = vertices[index2].uv;

        Vector3 e0 = p1 - p0;
        Vector3 e1 = p2 - p0;

        float u1 = uv1.x - uv0.x;
        float v1 = uv1.y - uv0.y;
        float u2 = uv2.x - uv0.x;
        float v2 = uv2.y - uv0.y;

        float d = 1.0f / (u1 * v2 - u2 * v1);

        Vector3 tangent = d * (e0 * v2 - e1 * v1);

        vertices[index0].tangent += tangent;
        vertices[index1].tangent += tangent;
        vertices[index2].tangent += tangent;
    }
}

void TerrainEditor::MakeComputeData()
{
    // 편집이 이루어지거나 이루어졌다고 하고 해당 계획까지 반영한 데이터 만들기

    vector<VertexType>vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    triangleSize = indices.size() / 3;

    // 다음 내 행동을 통해서 inputs와 outputs의 결과가 달라질 수도 있다
    // -> 바뀌는 부분에 대한 사전 처리도 필요하다

    inputs.resize(triangleSize); // 계산된 삼각형 크기에 맞추어서 벡터 재조정
    outputs.resize(triangleSize);

    // .clear() 같은 함수로 일괄 삭제를 해버리는 것도 방법이다 ( 확실하다 )

    for (UINT i = 0; i < triangleSize; ++i) // 계산된 삼각형들 만큼
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        // 입력한 결과에 지정된 입력의 정보를 반영하기
        // ( 나중에 출력은 어디서 호출하느냐 -> "고르기" 함수와, 업데이트, 렌더 등에서 각각 나눌 것 )
        // 입력이 제대로 들어가는 단계에서, 호출의 결과까지 배정

        inputs[i].v0 = vertices[index0].pos;
        inputs[i].v1 = vertices[index1].pos;
        inputs[i].v2 = vertices[index2].pos;
    }

    // 여기까지 오면 입력의 정보 반영 완료
}

void TerrainEditor::Reset()
{
    // 목적 : 소프트리셋 ( 규모 등을 바꾸지 않고 내부 내용 초기화 )
    //        그런데 메시 만들 때 이미 가로 세로가 반영되고 있는 중이라
    //        일단은 호출명은 다르고 하는 일은 Resize()와 동일하게

    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    mesh->UpdateVertex(); // 정점 정보 업데이트
    mesh->UpdateIndex();  // 인덱스 정보 업데이트

    structuredBuffer->UpdateInput(inputs.data()); // 건축 데이터 받아와서 반영하기
}

void TerrainEditor::Resize()
{
    // 내부 데이터 리셋 ( 크기가 새로 조정되는 경우 )

    // 메시 다시 만들기 ( 이 과정에서 가로 세로가 반영 )
    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    mesh->UpdateVertex(); // 정점 정보 업데이트
    mesh->UpdateIndex();  // 인덱스 정보 업데이트

    structuredBuffer->UpdateInput(inputs.data()); // 건축 데이터 받아와서 반영하기
}

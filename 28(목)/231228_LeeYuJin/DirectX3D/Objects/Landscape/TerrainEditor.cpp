#include "Framework.h"

TerrainEditor::TerrainEditor()
    : GameObject(L"Landscape/TerrainEditor.hlsl"),
    //: GameObject(L"Light/NormalMapping.hlsl"),
    width(MAX_SIZE),
    height(MAX_SIZE)
{
    // 매티리얼 배정
    material->SetDiffuseMap(L"Textures/Landscape/Dirt.png");
    secondMap = Texture::Add(L"Textures/Landscape/Dirt2.png");
    thirdMap = Texture::Add(L"Textures/Landscape/Dirt3.png");

    //메시 만들기 (기본, 부정형)
    mesh = new Mesh<VertexType>();

    //메시 만들기 (성형)
    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData(); //생성된 결과도 생성 시점에서 먼저 만들기

    mesh->CreateMesh();

    //연산 셰이더를 셰이더 사전 설정 파일에서 지정
    computeShader = Shader::AddCS(L"Compute/ComputePicking.hlsl");

    // 편집에 쓸 편집도구 초기화
    brushBuffer = new BrushBuffer();

    // 건축 과정에서 오가는 데이터를 보존 및 적용할 버퍼
    structuredBuffer = new StructuredBuffer(
        inputs.data(), sizeof(InputDesc), triangleSize,
                       sizeof(OutputDesc), triangleSize);
    // 스트럭처 버퍼(건축 버퍼)에 들어갈 매개변수:
    // 입력에 들어갈 데이터 / 입력의 데이터 규모 / 입력의 규모
    //                     / 출력의 데이터 규모 / 출력의 규모

    rayBuffer = new RayBuffer();

    //프로젝트 경로를 검사해서 할당하기
    char pathName[256]; // 문자열 미리 준비하기 : 이것보다 큰 문자열 불필요 (보통은 128자만으로도 충분)
    GetCurrentDirectoryA(256, pathName); // 현재 실행 중인 폴더명을 변수에 할당하기
    projectPath = pathName; //할당된 변수를 멤버 변수에 넣기
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
    if (CAM->GetTarget())
    {
        return;
    }
    
    if (IsComputePick(pickingPos)) // 굳이 찍지 않아도 마우스 위치(픽킹 포즈에 저장)를 매번 받으면서
                                   // 지형 픽킹이 잘 됐는지 여부까지 계속 판별하는 조건문을 사용
    {
        // 지형에 마우스 커서가 올라가 있는 상황 (컴퓨트 픽이 true 반환)
        brushBuffer->Get().pickingPos = pickingPos;
    }
    else
    {
        // 지형 픽킹이 안 된 상태에선 아래 모든 코드를 중단 (속도 확보)
        return;
    }

    //if (KEY_PRESS(VK_LBUTTON))
    if (KEY_PRESS(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse) // 뒤 조건은 디버그 상의 편의
                                                                   // 목적 : 디버그 패널 중에는
                                                                   // 마우스 위치가 지형과 겹쳐도
                                                                   // 조작이 안 되기를 바람
    {
        //brushBuffer->Get().pickingPos = ComputePick();
        //pickingPos = brushBuffer->Get().pickingPos;
        // 위치 찾기

        switch (editType) //브러시를 그었을 때 타입에 따라...
        {
        case TerrainEditor::HEIGHT: // 높이 조정이라면...
            AdjustHeight(); // 높이 바꾸기
            //UpdateHeight(); // 높이 업데이트
            break;

        case TerrainEditor::ALPHA:
            AdjustAlpha();
            //UpdateAlpha();
            break;
        }
    }

    //마우스를 뗐을 때 최종 지형 반영
    if (KEY_UP(VK_LBUTTON))
    {
        UpdateHeight();
        UpdateAlpha();
    }
}

void TerrainEditor::Render()
{
    // 만든 결과 확인

    //브러시 렌더
    brushBuffer->SetPS(10);
    
    //추가 텍스처를 레이어로 만들기
    secondMap->PSSet(11); // 나중에 이 텍스처가 보일 수 있다면 브러시보다 더 위에 (맵보다도) 보일 것
    thirdMap->PSSet(12);

    //전체 맵 렌더
    SetRender();

    mesh->Draw();
}

void TerrainEditor::RenderUI()
{
    //디버그 판에서 확인

    //타이틀
    ImGui::Text("Terrain Editor (Option)");
    if (ImGui::DragInt("Width", (int*)&width, 1.0f, 2, MAX_SIZE))
        Resize(); // 크기가 바뀌면 리사이즈
    if (ImGui::DragInt("Height", (int*)&height, 1.0f, 2, MAX_SIZE))
        Resize();

    //픽커에서 따온 좌표 참조 위치
    ImGui::Text("Terrain Pick Position");
    ImGui::Text("X : %.1f, Y : %.1f, Z : %.1f",
        brushBuffer->Get().pickingPos.x,
        brushBuffer->Get().pickingPos.y,
        brushBuffer->Get().pickingPos.z);
    ImGui::Text("Height : %.1f",
        GetHeightByPos(pickingPos));

    const char* editList[] = { "Height", "Alpha" };
    ImGui::Combo("EditType", (int*)&editType, editList, 2);

    const char* brushList[] = { "Circle", "SoftCircle", "Rect" };
    if (ImGui::Combo("BrushType", (int*)&brushType, brushList, 3))
        brushBuffer->Get().type = brushType;

    ImGui::DragFloat("Range", &brushBuffer->Get().range, 1.0f, 1.0f, 20.0f);
    ImGui::DragFloat("AdjustValue", &adjustValue, 1.0f, -50.0f, 50.0f);
    ImGui::ColorEdit3("Color", (float*)&brushBuffer->Get().color);

    ImGui::DragInt("SelectMap", (int*)&selectMap, 1.0f, 0, 2);

    SaveHeightMap();
    ImGui::SameLine();
    LoadHeightMap();

    SaveAlphaMap();
    ImGui::SameLine();
    LoadAlphaMap();
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

            //정점받기
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

    return Vector3();
}

Vector3 TerrainEditor::ComputePick()
{
    // 목적 : 골랐을 때, 위치를 바로 반환만 하기보다, 아예 그 과정에서
    // 컴퓨트 데이터에 반영까지 해보기를 목표로

    Ray ray = CAM->ScreenPointToRay(mousePos);

    //광선 버퍼에 광선 정보 저장
    rayBuffer->Get().pos = ray.pos;
    rayBuffer->Get().dir = ray.dir;
    rayBuffer->Get().triangleSize = triangleSize; // 현재 맵의 입력규모를 광선버퍼에도

    rayBuffer->SetCS(0);

    DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
    // 리소스에서 셰이더 세팅하기 (셰이더 슬롯, 보려는 뷰포트 개수, 원본 리소스)

    //출력요청, 접근 등을 그대로 출력하는 기능
    DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

    //설정된 연산 셰이더를 세팅
    computeShader->Set();

    UINT x = ceil((float)triangleSize / 64.0f); // 입력 규모에서 값 x를 받을 텐데, 올림(ceil) 방식으로 받기

    DC->Dispatch(x, 1, 1); // 연산 셰이더 출력 환경에서 해당 CS의 작업 비중, 크기, 빈도 등을 조절하는 기능

    structuredBuffer->Copy(outputs.data(), sizeof(OutputDesc) * triangleSize); // 건축 버퍼 데이터를 출력에 저장

    float minDistance = FLT_MAX; // 최소거리 임시값 저장
    int minIndex = -1; //최소 순번 임시값 저장

    UINT index = 0; // 순번 임시값으로 초기화

    //위에서 나온 출력 결과 모두 반복문으로 호출
    for (OutputDesc output : outputs)
    {
        if (output.picked) // 선택 여부가 코드로 남아있다 = 참이다
        {
            if (output.distance < minDistance) // 마지막으로 계측된 최소 거리보다 현재 출력데이터 거리가 작다면
            {
                minDistance = output.distance; //갱신
                minIndex = index; //갱신된 거리의 원본 출력 데이터의 순번
            }
        }
        ++index; // 반복문 수행 시마다 인덱스 +1

        // 이 반복문을 수행함으로써 출력 데이터 사이에서 "거리"가 제일 짧은 출력 결과를 얻어낼 수 있다
        // -> 광원에서 표면에 다다르는 최소거리 = 직선거리를 도출 가능
    }

    // 여기까지 왔을 때 index의 값이 -1이 아니면 (index가 "있다면")
    // 광원에서 물체로 가는 광선 충돌이 났다는 이야기
    // 해당 위치를 판별하는 과정에서도 output이 버퍼를 통해 저장이 되기도 했다

    // 그러므로 해당 결과를 반환까지 해주면 된다


    // * 중간 힌트: 이쯤에서 메시의 정점을 바꿔줄 수 있다면,
    //              지형의 모양을 어느 정도 바꿔주는 게
    //              가능할 겁니다!!


    if (minIndex > -1)
    {
        return ray.pos + ray.dir * minDistance; // 광원, 광선 방향, 측정된 직선거리
    }

    // 그렇지 않다면 충돌이 없었던 것 (따라서 반영할 다른 입력 결과도 없었던 것)
    return Vector3();
}

// 위 함수의 매개변수 대응형 (mousePos 없음)
Vector3 TerrainEditor::ComputePick(Vector3 sourcePos)
{
    // 목적 : 골랐을 때, 위치를 바로 반환만 하기보다, 아예 그 과정에서
    // 컴퓨트 데이터에 반영까지 해보기를 목표로

    //매개변수로 받은 위치에서 새로 광선을 생성
    Ray ray;
    ray.pos = sourcePos;  // 광원 : 매개변수의 위치
    ray.dir = Vector3::Down(); // 광선의 방향은 무조건 아래 (캐릭터로 치면 발 아래)

    //광선 버퍼에 광선 정보 저장
    rayBuffer->Get().pos = ray.pos;
    rayBuffer->Get().dir = ray.dir;
    rayBuffer->Get().triangleSize = triangleSize; // 현재 맵의 입력규모를 광선버퍼에도

    rayBuffer->SetCS(0);

    DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
    // 리소스에서 셰이더 세팅하기 (셰이더 슬롯, 보려는 뷰포트 개수, 원본 리소스)

    //출력요청, 접근 등을 그대로 출력하는 기능
    DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

    //설정된 연산 셰이더를 세팅
    computeShader->Set();

    UINT x = ceil((float)triangleSize / 64.0f); // 입력 규모에서 값 x를 받을 텐데, 올림(ceil) 방식으로 받기

    DC->Dispatch(x, 1, 1); // 연산 셰이더 출력 환경에서 해당 CS의 작업 비중, 크기, 빈도 등을 조절하는 기능

    structuredBuffer->Copy(outputs.data(), sizeof(OutputDesc) * triangleSize); // 건축 버퍼 데이터를 출력에 저장

    float minDistance = FLT_MAX; // 최소거리 임시값 저장
    int minIndex = -1; //최소 순번 임시값 저장

    UINT index = 0; // 순번 임시값으로 초기화

    //위에서 나온 출력 결과 모두 반복문으로 호출
    for (OutputDesc output : outputs)
    {
        if (output.picked) // 선택 여부가 코드로 남아있다 = 참이다
        {
            if (output.distance < minDistance) // 마지막으로 계측된 최소 거리보다 현재 출력데이터 거리가 작다면
            {
                minDistance = output.distance; //갱신
                minIndex = index; //갱신된 거리의 원본 출력 데이터의 순번
            }
        }
        ++index; // 반복문 수행 시마다 인덱스 +1

        // 이 반복문을 수행함으로써 출력 데이터 사이에서 "거리"가 제일 짧은 출력 결과를 얻어낼 수 있다
        // -> 광원에서 표면에 다다르는 최소거리 = 직선거리를 도출 가능
    }

    // 여기까지 왔을 때 index의 값이 -1이 아니면 (index가 "있다면")
    // 광원에서 물체로 가는 광선 충돌이 났다는 이야기
    // 해당 위치를 판별하는 과정에서도 output이 버퍼를 통해 저장이 되기도 했다

    // 그러므로 해당 결과를 반환까지 해주면 된다


    // * 중간 힌트: 이쯤에서 메시의 정점을 바꿔줄 수 있다면,
    //              지형의 모양을 어느 정도 바꿔주는 게
    //              가능할 겁니다!!


    if (minIndex > -1)
    {
        return ray.pos + ray.dir * minDistance; // 광원, 광선 방향, 측정된 직선거리
    }

    // 그렇지 않다면 충돌이 없었던 것 (따라서 반영할 다른 입력 결과도 없었던 것)
    return Vector3();
}

//원형 컴퓨트 픽(마우스 위치에서 지형 좌표 얻기) 함수의 bool 반환형 (+pos 저장)
bool TerrainEditor::IsComputePick(Vector3& pos)
{
    Ray ray = CAM->ScreenPointToRay(mousePos);

    rayBuffer->Get().pos = ray.pos;
    rayBuffer->Get().dir = ray.dir;
    rayBuffer->Get().triangleSize = triangleSize;

    rayBuffer->SetCS(0);

    DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
    DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

    computeShader->Set();

    UINT x = ceil((float)triangleSize / 64.0f);

    DC->Dispatch(x, 1, 1);

    structuredBuffer->Copy(outputs.data(), sizeof(OutputDesc) * triangleSize);

    float minDistance = FLT_MAX;
    int minIndex = -1;

    UINT index = 0;
    for (OutputDesc output : outputs)
    {
        if (output.picked)
        {
            if (minDistance > output.distance)
            {
                minDistance = output.distance;
                minIndex = index;
            }
        }
        index++;
    }

    if (minIndex >= 0)
    {
        pos = ray.pos + ray.dir * minDistance;
        return true;
    }

    return false;
}

// 매개변수를 받아 지형 좌표를 도출한 후, 해당 좌표의 Y (높이) 값을 소수로 반환하는 함수
float TerrainEditor::GetHeightByPos(Vector3 myPos)
{
    // 컴퓨트 픽(광선을 쏘면 정점 겹치기를 통해서 해당 정점의 높이를 도출)
    // 해당 함수의 결과 = 정점, 정점의 Y = 높이
    float result = ComputePick(myPos).y;

    return result;
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
            vertex.pos = { (float)x, 0.0f, (float)(height - z - 1) };
            vertex.uv.x = x / (float)(width - 1);
            vertex.uv.y = z / (float)(height - 1);

            UINT index = width * z + x;
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
        UINT index0 = indices[i * 3 + 0];
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
    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
    {
        UINT index0 = indices[i * 3 + 0];
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
    //편집이 이루어지거나 이루어졌다고 하고 해당 계획까지 반영한 데이터 만들기

    vector<VertexType> vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    triangleSize = indices.size() / 3;

    // 다음 내 행동을 통해서 inputs와 outputs의 결과가 달라질 수 있다
    // -> 바뀌는 부분에 대한 사전 처리도 필요하다

    inputs.resize(triangleSize); // 계산된 삼각형 크기에 맞추어서 벡터 재조정
    outputs.resize(triangleSize);

    //.clear() 같은 함수로 일괄 삭제를 해버리는 것도 방법이다 (확실하다)

    for (UINT i = 0; i < triangleSize; ++i) // 계산된 삼각형들만큼
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        // 입력한 결과에 지정된 입력의 정보를 반영하기
        // (나중에 출력은 어디서 호출하느냐 -> "고르기" 함수와, 업데이트, 렌더 등에서 각각 나눌 것)
        // 입력이 제대로 들어가는 단계에서, 호출의 결과까지 배정

        inputs[i].v0 = vertices[index0].pos;
        inputs[i].v1 = vertices[index1].pos;
        inputs[i].v2 = vertices[index2].pos;
    }

    //여기까지 오면 입력의 정보 반영 완료
}

void TerrainEditor::Reset()
{
    // 목적 : 소프트 리셋 (규모 등을 바꾸지 않고 내부 내용 초기화)
    //        그런데 메시 만들 때 이미 가로세로가 반영되고 있는 중이라...
    //        일단은 호출명은 다르고 하는 일은 리사이즈와 동일하게

    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    mesh->UpdateVertex(); // 정점 정보 업데이트
    mesh->UpdateIndex(); // 인덱스 정보 업데이트

    structuredBuffer->UpdateInput(inputs.data()); //건축 데이터 받아와서 반영하기
}

void TerrainEditor::Resize()
{
    // 내부 데이터 리셋 (크기가 새로 조정되는 경우)

    //메시 다시 만들기 (이 과정에서 가로세로가 반영)
    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    mesh->UpdateVertex(); // 정점 정보 업데이트
    mesh->UpdateIndex(); // 인덱스 정보 업데이트

    structuredBuffer->UpdateInput(inputs.data()); //건축 데이터 받아와서 반영하기
}

void TerrainEditor::UpdateHeight()
{
    // 아래 함수에서 정점은 조정을 했고 이제 반영할 차례

    vector<VertexType>& vertices = mesh->GetVertices();
    for (VertexType& vertex : vertices)
    {
        vertex.normal = {};
        vertex.tangent = {};
    }

    //위에서 초기화만 된 정점의 법선과 탄젠트를 밑에서 만들기
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    //조정된 높이를 실제 최종반영하기 (정점 업데이트 한번 더)
    mesh->UpdateVertex();

    structuredBuffer->UpdateInput(inputs.data());
}

void TerrainEditor::AdjustHeight()
{
    // 찍은 좌표 있음, 브러시 있음, 브러시 타입은 높이
    // -> 이에 따라 해당 좌표에 높이 변경을 진행

    // 높이 변경을 위해서는 정점 데이터가 필요하므로 받아오기
    vector<VertexType>& vertices = mesh->GetVertices();

    // 브러시 타입에 따라서 영역 구분하기
    switch (brushType)
    {
    case TerrainEditor::CIRCLE:

        //원인 경우
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z); // 메시 정점에서 가로 세로만 얻기
            pickingPos.y = 0; //높이 0에서 리셋

            float distance = Distance(pos, pickingPos); // 찍은 좌표의 중심에서 현재 정점의 거리 구하기

            if (distance <= brushBuffer->Get().range) // 거리가 브러시 현재 범위 안이라면 (*오타수정 : 1227)
            {
                vertex.pos.y += adjustValue * DELTA; // 정점의 높이에 강도와 시간경과를 반영
                // * DELTA를 입력함으로써 FPS 같은 성능 문제에 구애받지 않고 일정한 속도로 업데이트 연산 가능
                
                vertex.pos.y = Clamp(MIN_HEIGHT, MAX_HEIGHT, vertex.pos.y);
                //지금 호출된 함수 : clamp 함수 (여기서는 GameMath 클래스 안에 정의됨,
                //                              c++ 혹은 기타 프로그래밍 언어에 비슷한 함수 제공됨)
                //                  -> (호출 기준) 3번째로 들어간 매개변수가
                //                  최소값과 최대값 사이에 항상 있도록 강제하고,
                //                  범위보다 작을 경우 최소값을, 범위보다 클 경우 최대값을 반환
            }
        }
        break;

    case TerrainEditor::SOFT_CIRCLE:
        //작거나 흐릿한 원인 경우
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z); // 메시 정점에서 가로 세로만 얻기
            pickingPos.y = 0; //높이 0에서 리셋

            float distance = Distance(pos, pickingPos); // 찍은 좌표의 중심에서 현재 정점의 거리 구하기

            //작거나 흐릿한 원인 경우
            float temp = adjustValue * max(MIN_HEIGHT, cos(distance / brushBuffer->Get().range));
            // 단순 원 반지름의 범위가 아니라, 해당 범위 안에서 어느 정도의 보정치를 추가로 받느냐의 문제까지 포함
            // -> 중심에 가까울수록 거리가 짧아지기 때문에 코사인은 커진다

            if (distance <= brushBuffer->Get().range) // 거리가 브러시 현재 범위 안이라면 (*오타수정 : 1227)
            {
                vertex.pos.y += temp * DELTA; // 정점의 높이에 위에서 구한 임시값과 시간경과를 반영
                // * DELTA를 입력함으로써 FPS 같은 성능 문제에 구애받지 않고 일정한 속도로 업데이트 연산 가능

                vertex.pos.y = Clamp(MIN_HEIGHT, MAX_HEIGHT, vertex.pos.y);
                // 클램핑으로 최대 최소 강제하기
            }
        }
        break;

    case TerrainEditor::RECT:

        // 직사각형인 경우
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z); // 메시 정점에서 가로 세로만 얻기
            pickingPos.y = 0; //높이 0에서 리셋

            // "반" 구하기 (직사각형의 크기를 반으로 쪼개서 계산이 편하도록)
            float half = brushBuffer->Get().range * 0.5f;

            //가로세로 기준으로 렉트 구성요소 구하기
            float left = max(0, pickingPos.x - half);
            float right = max(0, pickingPos.x + half);
            float top = max(0, pickingPos.z + half);
            float bottom = max(0, pickingPos.z - half);

            for (UINT z = (UINT)bottom; z <= (UINT)top; ++z)
            {
                for (UINT x = (UINT)left; x <= (UINT)right; ++x)
                {
                    UINT index = width * (height - z - 1) + x; // 가로 세로 기준으로 정해져 있던 인덱스를 다시 구하기

                    if (index >= vertices.size()) continue; // 인덱스가 정점의 목록에 없으면 생략

                    vertices[index].pos.y = adjustValue * DELTA;
                    vertices[index].pos.y = Clamp(MIN_HEIGHT, MAX_HEIGHT, vertices[index].pos.y);
                }
            }
        }

        break;
    }

    // 여기까지 오면 스위치문과, 그 안의 반복문들까지 모두 수행
    // 수행 결과를 메시에서 업데이트
    mesh->UpdateVertex();
}


void TerrainEditor::UpdateAlpha()
{
    // TODO : 알파맵 나오면...?
}

void TerrainEditor::AdjustAlpha() //알파 조정하기
{
    //기본적으로는 높이 조정과 거의 내용이 같다
    // 브러시 범위와 지형 사이에 겹치는 부분을 조작한다

    vector<VertexType>& vertices = mesh->GetVertices();

    switch (brushType)
    {
    case TerrainEditor::CIRCLE:
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z);
            pickingPos.y = 0.0f;

            float distance = Distance(pos, pickingPos);

            if (distance <= brushBuffer->Get().range)
            {
                // 정점의 높이 대신 저장된 알파값을 바꾼다
                // 기대 : 텍스처 표현이 되어 있는 상태인 경우, 해당 텍스처가 보이고 보이지 않는 정도를 바꾼다
                vertex.alpha[selectMap] += adjustValue * DELTA;
                vertex.alpha[selectMap] = Clamp(0.0f, 1.0f, vertex.alpha[selectMap]);
            }
        }
        break;
    case TerrainEditor::SOFT_CIRCLE:
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z);
            pickingPos.y = 0.0f;

            float distance = Distance(pos, pickingPos);

            float temp = adjustValue * max(0, cos(distance / brushBuffer->Get().range));

            if (distance <= brushBuffer->Get().range)
            {
                vertex.alpha[selectMap] += temp * DELTA;
                vertex.alpha[selectMap] = Clamp(0.0f, 1.0f, vertex.alpha[selectMap]);
            }
        }
        break;
    case TerrainEditor::RECT:
    {
        float size = brushBuffer->Get().range * 0.5f;

        float left = max(0, pickingPos.x - size);
        float right = max(0, pickingPos.x + size);
        float top = max(0, pickingPos.z + size);
        float bottom = max(0, pickingPos.z - size);

        for (UINT z = (UINT)bottom; z <= (UINT)top; z++)
        {
            for (UINT x = (UINT)left; x <= (UINT)right; x++)
            {
                UINT index = width * (height - z - 1) + x;

                if (index >= vertices.size()) continue;

                vertices[index].alpha[selectMap] += adjustValue * DELTA;
                vertices[index].alpha[selectMap] = Clamp(0.0f, 1.0f, vertices[index].alpha[selectMap]);
            }
        }
    }
    break;
    }

    mesh->UpdateVertex();
}

void TerrainEditor::SaveHeightMap()
{
    if (ImGui::Button("SaveHeight"))
        DIALOG->OpenDialog("SaveHeight", "SaveHeight", ".png", ".");

    if (DIALOG->Display("SaveHeight"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            file = file.substr(projectPath.size() + 1, file.size());

            // 픽셀 배열 만들기 (픽셀 : 8바이트 색 정보 = 정수)
            // 모든 픽셀이 8바이트여야 한다 x
            // 높이 맵이라서 색을 다양하게 넣을 필요가 없다
            UINT size = width * height * 4;
            uint8_t* pixels = new uint8_t[size];

            // 정점 정보를 가져오기
            vector<VertexType> vertices = mesh->GetVertices();

            // 각 정점을 모두 계산해서 "높이"를 계산하고 픽셀별로 들어갈 정수값(=색 정보) 주기
            for (UINT i = 0; i < size / 4; i++)
            {
                float y = vertices[i].pos.y;

                uint8_t height = (y - MIN_HEIGHT) / (MAX_HEIGHT - MIN_HEIGHT) * 255;

                pixels[i * 4 + 0] = height;
                pixels[i * 4 + 1] = height;
                pixels[i * 4 + 2] = height;
                pixels[i * 4 + 3] = 255;
            }

            //이미지를 생성해서 해당 점 하나하나에 정점 정보를 픽셀의 정보로 계산해서 넣기
            Image image; //DX 제공된 구조체 (Directx::Image를 검색하는 편을 추천)
            image.width = width;
            image.height = height;
            image.format = DXGI_FORMAT_R8G8B8A8_UNORM;
            image.rowPitch = width * 4;
            image.slicePitch = size;
            image.pixels = pixels;

            //위에서 만든 이미지를 DX 제공 함수를 통해서 이미지 저장
            SaveToWICFile(image, WIC_FLAGS_FORCE_RGB,
                GetWICCodec(WIC_CODEC_PNG), ToWString(file).c_str());

            delete[] pixels;
        }

        DIALOG->Close();
    }
}

void TerrainEditor::LoadHeightMap()
{
    if (ImGui::Button("LoadHeight"))
        DIALOG->OpenDialog("LoadHeight", "LoadHeight", ".png", ".");

    if (DIALOG->Display("LoadHeight"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            file = file.substr(projectPath.size() + 1, file.size());

            // 높이 맵에 불러온 이미지를 저장하고
            heightMap = Texture::Add(ToWString(file));

            //리사이즈 (지형 리셋)
            Resize();
        }

        DIALOG->Close();
    }
}

//높이 대신 알파 정보를 8바이트 이미지로 만들어서 저장 (그리고 아래 함수에서 읽기)
void TerrainEditor::SaveAlphaMap()
{
    if (ImGui::Button("SaveAlpha"))
        DIALOG->OpenDialog("SaveAlpha", "SaveAlpha", ".png", ".");

    if (DIALOG->Display("SaveAlpha"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            file = file.substr(projectPath.size() + 1, file.size());

            UINT size = width * height * 4;
            uint8_t* pixels = new uint8_t[size];

            vector<VertexType> vertices = mesh->GetVertices();

            for (UINT i = 0; i < size / 4; i++)
            {
                pixels[i * 4 + 0] = vertices[i].alpha[0] * 255;
                pixels[i * 4 + 1] = vertices[i].alpha[1] * 255;
                pixels[i * 4 + 2] = vertices[i].alpha[2] * 255;
                pixels[i * 4 + 3] = 255;
            }

            Image image;
            image.width = width;
            image.height = height;
            image.format = DXGI_FORMAT_R8G8B8A8_UNORM;
            image.rowPitch = width * 4;
            image.slicePitch = size;
            image.pixels = pixels;

            SaveToWICFile(image, WIC_FLAGS_FORCE_RGB,
                GetWICCodec(WIC_CODEC_PNG), ToWString(file).c_str());

            delete[] pixels;
        }

        DIALOG->Close();
    }
}

void TerrainEditor::LoadAlphaMap()
{
    if (ImGui::Button("LoadAlpha"))
        DIALOG->OpenDialog("LoadAlpha", "LoadAlpha", ".png", ".");

    if (DIALOG->Display("LoadAlpha"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            file = file.substr(projectPath.size() + 1, file.size());

            Texture* alphaMap = Texture::Add(ToWString(file));

            vector<Float4> pixels;
            alphaMap->ReadPixels(pixels);

            vector<VertexType>& vertices = mesh->GetVertices();

            for (UINT i = 0; i < vertices.size(); i++)
            {
                vertices[i].alpha[0] = pixels[i].z;
                vertices[i].alpha[1] = pixels[i].y;
                vertices[i].alpha[2] = pixels[i].x;
                vertices[i].alpha[3] = pixels[i].w;
            }

            mesh->UpdateVertex();
        }

        DIALOG->Close();
    }
}

#include "Framework.h"

TerrainLOD::TerrainLOD(wstring heightFile)
{
    material->SetShader(L"TS/TerrainLOD.hlsl");
    material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    hullShader = Shader::AddHS(L"TS/TerrainLOD.hlsl");
    domainShader = Shader::AddDS(L"TS/TerrainLOD.hlsl");

    heightMap = Texture::Add(heightFile);

    terrainBuffer = new FloatValueBuffer();
    heightBuffer = new FloatValueBuffer();

    // 각 버퍼에 의미를 담아 수치를 할당
    terrainBuffer->Get()[0] = 1.0f;         // LOD 선별 기준거리, 최소
    terrainBuffer->Get()[1] = 1000.0f;      // LOD 선별 기준거리, 최대
            //-> 현재의 설정은 "카메라 바로 앞에서부터 LOD 시작, 거리 1000 이상은 최소 렌더
            //   게임에서 흔히 쓸 만한 현실적인 설정 x, 현재의 LOD는 이렇게 동작할 수도 있다는 예시
    terrainBuffer->Get()[2] = 1.0f;         // LOD 세부 묘사 수준, 최소
    terrainBuffer->Get()[3] = 64.0f;        // LOD 세부 묘사 수준, 최대
            //-> 현재 설정의 의미는 세부 묘사를 최소 1/64 수준까지 떨어뜨리겠다
            //   현실적인 설정 x, LOD가 이렇게 동작할 것이라는 예시

    // 위 LOD 설정 버퍼에서, 현실적인 게임이라면... 최소 거리는 조금 더 키우고,
    // 세부 묘사 최소 수준의 비율도 현재보다는 조금 더 높일 것

    heightBuffer->Get()[0] = 20.0f; // 일반 터레인 클래스에서 설정했던 최대 높이

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

TerrainLOD::~TerrainLOD()
{
    delete mesh;

    delete terrainBuffer;
    delete heightBuffer;
}

void TerrainLOD::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    // 버퍼 세팅
    terrainBuffer->SetHS(10); // 10 : 셰이더 내 조건문 활성화 + 다른 셰이더 세팅과 안 겹침
    heightBuffer->SetDS(10);

    heightMap->DSSet(); // 설정된 셰이더 할당

    //렌더 준비
    material->Set();
    hullShader->Set();
    domainShader->Set();

    //실제 그리기 (연산 후 대기)
    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
                // 사전에, 혹은 메쉬 작성 중에 설정한 patch의 단위로 렌더를 수행
                // -> patch에도 기본 값은 있다 : 6면체 영역 (직관적 이해 가능)

    //모니터에 셰이더 적용하고 출력
    DC->HSSetShader(nullptr, nullptr, 0);
    DC->DSSetShader(nullptr, nullptr, 0);
}

void TerrainLOD::GUIRender()
{
    ImGui::Text("TerrainLOD Option");
    ImGui::DragFloat("MinDistance", &terrainBuffer->Get()[0]);
    ImGui::DragFloat("MaxDistance", &terrainBuffer->Get()[1]);
    ImGui::DragFloat("MinQuality", &terrainBuffer->Get()[2]);
    ImGui::DragFloat("MaxQuality", &terrainBuffer->Get()[3]);
    ImGui::DragFloat("HeightScale", &heightBuffer->Get()[0]);
}

void TerrainLOD::MakeMesh()
{
    // LOD 터레인의 영역 구분과 실제 모양(정점) 정의까지

    width = heightMap->GetSize().x;
    height = heightMap->GetSize().y;

    // 한 영역에서 텍스처 참조를 어떻게 할 것인가
    cellUV = { 1.0f / width, 1.0f / height }; // <- 가장 단순, 명료한 방법

    // 영역의 형태와 규격을 정의
    patchWidth = ((width - 1) / cellsPerPatch) + 1; // <- 한 영역 안에 cellsPerPatch만큼의 픽셀을 넣겠다
    patchHeight = ((height - 1) / cellsPerPatch) + 1; // 영역 = 렉트(2D사각형 혹은 같은 xz내의 모든 높이를 포함하는 벡터공간)
                                                      // cells의 의미 : 여기서는 텍스처의 픽셀

    // 위 코드에서 도출된 영역, 규격, cells를 이용해서 LOD 메쉬를 제작

    //정점 데이터
    vector<VertexType>& vertices = mesh->GetVertices();
    vertices.resize(patchWidth * patchHeight);

    // 위에서 만든 데이터를 조합해서 정점 탐색 진행용 변수들을 만든다

    float halfWidth = width * cellSpacing * 0.5f;   // 영역을 도식화할 때 쓰기 위한 "절반값"
    float halfHeight = height * cellSpacing * 0.5f; // 렉트나 OBB 등의 절반값과 역할 동일

    float tempWidth = width * cellSpacing / patchWidth;      // 규격을 전체로 나누어서 단위와 개수 도출
    float tempHeight = height * cellSpacing / patchHeight;   // 

    float du = 1.0f / patchWidth;  // 단위 내의 UV (세부화되면 참조하는 픽셀을 늘리기 위함)
    float dv = 1.0f / patchHeight; // 

    for (UINT z = 0; z < patchHeight; z++)
    {
        float tempZ = halfHeight - z * tempHeight; // 좌표 z 내기
        for (UINT x = 0; x < patchWidth; x++)
        {
            float tempX = -halfHeight + x * tempWidth; //좌표 x 내기

            UINT index = patchWidth * z + x;              //정점을 인덱스로 찾아내기
                                                          //*여기서 인덱스는 실제 정점의 출력용 목록을 뜻하지 않고
                                                          // 단순히 정점 벡터 내의 순수한 순번을 뜻한다
            vertices[index].pos = { tempX, 0.0f, tempZ }; //정점 위치 조정
            vertices[index].uv = { x * du, z * dv };      //정점 uv 조정

            // -> 가까이 있으면 (규격과 세부단위가 올라가면 : temp가 낮아지면)
            //    index가 촘촘하게 바뀌기 때문에 정점들이 하나하나 모두 돌아가면서 바뀐다
            // -> 멀리 있으면 (규격과 세부단위가 내려가고, temp가 높아지면)
            //    intdex가 몇 단계씩 건너뛰면서 반복문이 진행 -> 정점 일부가 연산에서 점점 누락
            //    = 이 과정을 통해서 가까운 곳은 꼼꼼하게 묘사해주고, 먼 곳은 띄엄띄엄 계산
            //    = 이 과정을 통해서 정점 연산의 일부를 생략하고, 지형을 뭉뚱그리는 대신 최적화 진행

            // -> 이 정점 생략 과정 (+헐셰이더 + 도메인셰이더) : LOD 연산의 핵심
        }
    }

    //정점 인덱스
    vector<UINT>& indices = mesh->GetIndices();
    indices.reserve((patchWidth - 1) * (patchHeight - 1) * 4);

    for (UINT z = 0; z < patchHeight - 1; z++)
    {
        for (UINT x = 0; x < patchWidth - 1; x++)
        {
            // 렌더용 인덱스 구성과 같되 삼각형 x2 대신 렉트 x1 구성으로

            indices.push_back(patchWidth * z + x);
            indices.push_back(patchWidth * z + x + 1);
            indices.push_back(patchWidth * (z + 1) + x);
            indices.push_back(patchWidth * (z + 1) + x + 1);
        }
    }
}


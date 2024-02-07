#include "Framework.h"

QuadTreeTerrain::QuadTreeTerrain(wstring heightFile)
{
    terrainData = new TerrainData(heightFile);
    width = terrainData->GetSize().x;
    height = terrainData->GetSize().y;

    material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    vertices = terrainData->GetVertices(); // 생성 시, 터레인이 아닌
                                           // 각 터레인에 같이 등록된 인접지 데이터를 모두 가져온다
    UINT vertexCount = vertices.size();
    triangleCount = vertexCount / 3;

    float centerX = 0.0f;
    float centerZ = 0.0f;
    float size = 0.0f;

    CalcMeshDimensions(vertexCount, centerX, centerZ, size);

    root = new Node();
    CreateTreeNode(root, centerX, centerZ, size);
}

QuadTreeTerrain::~QuadTreeTerrain()
{
    DeleteNode(root);
    delete root;
}

void QuadTreeTerrain::Render()
{
    drawCount = 0;
    SetRender();
    RenderNode(root);
}

void QuadTreeTerrain::GUIRender()
{
    ImGui::Text("DrawCount : %d", drawCount);
}

void QuadTreeTerrain::RenderNode(Node* node)
{
    Vector3 center(node->x, 0.0f, node->z);
    float radius = node->size * 0.5f;

    if (!CAM->ContainSphere(center, radius))
        return;

    UINT count = 0;
    FOR(4)
    {
        if (node->children[i])
        {
            count++;
            RenderNode(node->children[i]);
        }
    }

    if (count != 0)
        return;

    //Leaf Node
    node->mesh->Draw();
    drawCount += node->triangleCount;
}

void QuadTreeTerrain::DeleteNode(Node* node)
{
    FOR(4)
    {
        if (node->children[i])
        {
            DeleteNode(node->children[i]);
            delete node->children[i];
        }
    }

    delete node->mesh;
}

void QuadTreeTerrain::CalcMeshDimensions(UINT vertexCount, float& centerX, float& centerZ, float& size)
{
    FOR(vertexCount)
    {
        centerX += vertices[i].pos.x;
        centerZ += vertices[i].pos.z;
    }

    centerX /= (float)vertexCount;
    centerZ /= (float)vertexCount;

    // 정점의 실제 위치를 반영해 "센터"의 실제 평균값을 찾고

    float maxX = 0.0f, maxZ = 0.0f;

    // 검산 겸 정점 기준으로 센터값을 재반영하고

    FOR(vertexCount)
    {
        float width = abs(vertices[i].pos.x - centerX);
        float depth = abs(vertices[i].pos.z - centerZ);

        if (width > maxX) maxX = width;
        if (depth > maxZ) maxZ = width;
    }

    // 도출된 센터 값을 피드백함과 동시에, 지형의 전체 크기까지 도출

    size = max(maxX, maxZ) * 2.0f; // <- 지형의 크기
}

// x, z 위치에 size만한 영역 내에서 삼각형이 존재하는지 여부 판단
bool QuadTreeTerrain::IsTriangleContained(UINT index, float x, float z, float size)
{
    UINT vertexIndex = index * 3;
    float halfSize = size * 0.5f;

    // 지형의 (단순 정점 아닌) 인접지까지의 데이터를 모두 가져와서 위치를 검사

    float x1 = vertices[vertexIndex].pos.x;
    float z1 = vertices[vertexIndex].pos.z;
    vertexIndex++;

    float x2 = vertices[vertexIndex].pos.x;
    float z2 = vertices[vertexIndex].pos.z;
    vertexIndex++;

    float x3 = vertices[vertexIndex].pos.x;
    float z3 = vertices[vertexIndex].pos.z;

    // 위에서 확인한 삼각형의 구성 요소 x, z를 각 세 점마다 최소, 최대 값을 낸다
    // ...그리고 최소값이 영역의 최대 한계보다 크면 / 최대값이 최소 한계보다 작으면?

    // -> 해당 삼각형은 영역 안에 있다고 볼 수 없는 것 (지나치게 크거나, 애초에 그 자리에 없거나)

    float minX = min(x1, min(x2, x3));
    if (minX > (x + halfSize))
        return false;

    float minZ = min(z1, min(z2, z3));
    if (minZ > (z + halfSize))
        return false;

    float maxX = max(x1, max(x2, x3));
    if (maxX < (x - halfSize))
        return false;

    float maxZ = max(z1, max(z2, z3));
    if (maxZ < (z - halfSize))
        return false;

    // 여기까지 통과되면 영역 안에 삼각형이 있다는 것

    return true;
}

UINT QuadTreeTerrain::ContainTriangleCount(float x, float z, float size)
{
    UINT count = 0;

    FOR(triangleCount)
    {
        if (IsTriangleContained(i, x, z, size))
            count++;
    }

    return count;
}

void QuadTreeTerrain::CreateTreeNode(Node* node, float x, float z, float size)
{
    // 노드의 위치(센터)와 크기
    node->x = x;
    node->z = z;
    node->size = size;

    //해당 위치와 크기에 해당하는 곳에 삼각형이 얼마나 있는가
    // -> 터레인 데이터에서 작성된 "삼각형 정점들(얼라인드 버텍스)"이 얼마나 들어가 있는가
    UINT triangles = ContainTriangleCount(x, z, size);

    if (triangles == 0) //삼각형이 하나도 없으면 계산종료
        return;

    if (triangles > MIN_TRIANGLE) // 삼각형이 최소 기준을 만족하면 = 쪼개야 하는 노드
                                  // * 삼각형의 개수 = 쿼드트리가 나뉘는 기준 중 하나(샘플)
                                  // 다른 조건이 필요하면 여기서 기준을 제시한다
                                  // (지금은 삼각형 개수만 기준으로)
    {
        FOR(4) // 구역이 나뉘어야 하면
        {
            float offsetX = (((i % 2) == 0) ? -1.0f : 1.0f) * (size / 4.0f);
            float offsetZ = ((i < 2) ? -1.0f : 1.0f) * (size / 4.0f);

            //각 구역을 새로운 노드로 만들고
            node->children[i] = new Node();
            //재귀 실행 후에 자기는 종료
            CreateTreeNode(node->children[i], x + offsetX, z + offsetZ, size * 0.5f);
        }

        return; // <- 종료
    }

    //Leaf Node
    //나뉠 수 없는 상황이면 여기서 자기 노드의 구성요소를 작성을 한다
    //-지금은 개수로만 나누는 중이므로, 지형을 있는 그대로 작성하는 걸 목적
    
    // (만약에 지형의 높이가 노드 안에서 똑같다든가... 하는 그런 부분이 있다면
    //  자식노드(압축불가) 혹은 부모노드(압축가능) 중에서 각각 경우에 따라 코드 수정 가능)
    
    // 위에서 도출된 "삼각형의 개수"를 노드에 대입 (정점 개수도 기입)
    node->triangleCount = triangles;
    UINT vertexCount = triangles * 3;

    //메쉬 데이터 준비
    node->mesh = new Mesh<VertexType>();
    vector<VertexType>& vertices = node->mesh->GetVertices();
    vertices.resize(vertexCount);

    UINT index = 0, vertexIndex = 0;
    FOR(triangleCount) // 삼각형 개수만큼 반복문을 돌리면서
    {
        if (IsTriangleContained(i, x, z, size)) //삼각형이 포함된(혹은 다른 기준이 충족된) 곳마다
        {
            vertexIndex = i * 3;
            vertices[index] = this->vertices[vertexIndex];
            index++;

            vertexIndex++;
            vertices[index] = this->vertices[vertexIndex];
            index++;

            vertexIndex++;
            vertices[index] = this->vertices[vertexIndex];
            index++;

            // -> 각 정점을 터레인 데이터에서 직접 받아온 다음
        }
    }

    node->mesh->CreateMesh(); // <- 메쉬 제작 (노드 내에서 부분 정점으로 만든 메쉬 생성)
}

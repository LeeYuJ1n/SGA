#pragma once

class QuadTreeTerrain : public GameObject
{
private:
    const float MAX_HEIGHT = 20.0f;
    const UINT MIN_TRIANGLE = 2048;

    typedef VertexUVNormal VertexType;

    struct Node
    {
        //노드를 구성하는 요소들
        float x, z, size; //위치와 크기
        UINT triangleCount = 0; //안에 있는 삼각형의 개수

        Mesh<VertexType>* mesh = nullptr; //해당 노드에서 갖고 있는 (지형의, 쪼개진) 모양

        Node* children[4] = {}; //노드 밑에 자식이 있다면 몇 개 있는지, 무엇인지
    };

public:
    QuadTreeTerrain(wstring heightFile);
    ~QuadTreeTerrain();

    void Render();
    void GUIRender();

private:
    void RenderNode(Node* node);
    void DeleteNode(Node* node);

    // 계산위치 정하기
    void CalcMeshDimensions(UINT vertexCount, float& centerX, float& centerZ, float& size);

    bool IsTriangleContained(UINT index, float x, float z, float size);
    UINT ContainTriangleCount(float x, float z, float size);

    // 노드 만들기, 쿼드트리의 시작
    void CreateTreeNode(Node* node, float x, float z, float size);

private:
    UINT width, height;
    UINT triangleCount = 0, drawCount = 0;

    TerrainData* terrainData;
    vector<VertexType> vertices;

    Node* root;
};
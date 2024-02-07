#pragma once

class TerrainData
{
private:
    const float MAX_HEIGHT = 20.0f;
    typedef VertexUVNormal VertexType;

public:
    TerrainData(wstring heightFile);
    ~TerrainData() = default;

    vector<VertexType> GetVertices() { return alignedVertices; }
    Vector2 GetSize() { return Vector2(width, height); }

private:
    void MakeMesh();
    void MakeNormal();
    void AlignVertexData();

private:
    vector<VertexType> vertices;
    vector<VertexType> alignedVertices; //각 정점에 인접한 정점 정보 (쿼드트리용)
    vector<UINT> indices;               //정점의 목록에서, 출력할 정점의 집합을 규정한 것(렌더용)

    // 정점의 인덱스와 정점의 인접지(구분)의 차이
    // -> 인덱스는 해당 정점 그 자체의 순번을 나타낸다.
    //    목록이 모이면 순서들을 통해서 인접 정보를 간접적으로 알 수는 있다 (직접 알려면 다시 계산)
    // -> 인접지 정보는 정점에서 인접한 정점들의 실제 정보를 갖고 있다
    //    주변 정보를 빠르게 참조할 수 있는 대신, 메모리를 잡아먹고, 이 자체로는 순번의 목록을 유추할 수 없다
    //    =렌더에 쓸 수 없다

    UINT width, height;

    Texture* heightMap;
};
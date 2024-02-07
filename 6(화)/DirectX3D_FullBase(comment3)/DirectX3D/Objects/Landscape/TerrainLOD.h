#pragma once

class TerrainLOD : public GameObject
{
    // LOD : 지형의 세부 묘사 수준 (level of detail)
    // LOD 클래스 : LOD를 지형에 적용해서 렌더할 때 사양의 부담을 낮추기 위한 클래스

private:
    typedef VertexUV VertexType; // 정점 타입(변경을 위해서 명명 재정의)
    //typedef VertexUVNormalTangent VertexType; //타입을 이렇게 바꾸어 쓸 수도 있다

public:
    TerrainLOD(wstring heightFile);
    ~TerrainLOD();

    void Render();
    void GUIRender();

private:
    void MakeMesh();

private:
    // 소수 버퍼
    FloatValueBuffer* terrainBuffer; // 용도에 따라 버퍼를 구분
    FloatValueBuffer* heightBuffer;  // 자료 구조가 나뉘는 이유 : 1. 일괄처리 선별
                                     //                         2. 휴먼에러 방지

    Mesh<VertexType>* mesh;

    HullShader* hullShader;          // 헐 셰이더, 중간 연산 셰이더
                                     // DX10부터 본격적으로 쓰이게 된 신기능
                                     // 정점 셰이더 계산 수 -> 렌더 절차 사이에 개입하여
                                     // 연산 일부를 조건에 따라 추가 셰이더를 받을 수 있도록
                                     // 연산을 다음 처리장치에 이전하는 셰이더 (다른 기능도 있지만 이쪽이 가장 중요)

    DomainShader* domainShader;      // 도메인 셰이더, 영역 셰이더
                                     // -> 정점과 픽셀을 그래픽 처리장치에서 통합계산하는 셰이더
                                     //    지오메트리 셰이더와 거의 비슷함 (GPU에서 하는 GS라고 이해해도 무방)
                                     // -> DS의 특징 : 헐 셰이더로부터 중간결과를 받아서 처리를 해준다
                                     //    = 조건에 따라 다른 정점 처리 가능

    Texture* heightMap;

    // 헐/도메인 셰이더 연산에 필요한 정점 선별 기준
    UINT cellsPerPatch = 32;    // 확인하려는 영역 내에 들어가야 할 세부 정점 단위
    float cellSpacing = 5;      // 단위간의 패딩
    Vector2 cellUV;             // 각 단위가 출력할 때 텍스처에서 참조할 UV

    UINT width, height;
    UINT patchWidth, patchHeight;
};
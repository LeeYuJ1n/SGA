#pragma once

class TerrainEditor : public GameObject
{
	// 클래스의 목적 : 터레인 픽커의 기능을 더욱 확장해서, 
	//                클릭에 따라 지형의 세부 모양이 앱 내에서도 바뀔 수 있도록 만들기
private:
    typedef VertexUVNormalTangent VertexType;
    const float MAX_HEIGHT = 20.0f; // 최대 높이 미리 정해놓기

    // 브러시 버퍼와 레이 버퍼
    class BrushBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            int type = 0;               // 이 브러시의 타입
            Float3 pickingPos;          // 찍고 있는 좌표
            float range = 5.0f;         // 기본 범위
            Float3 color = { 0, 0, 1 }; // 파란색, 0, 1, 0이면 초록색
        };

        Data data;

    public:
        BrushBuffer() : ConstBuffer(&data, sizeof(Data)) {}
        Data& Get() { return data; }
    };

    class RayBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Float3 pos;         // 광원
            int triangleSize;   // 영향 범위

            Float3 dir;         // 방향
            float padding;      // "유격" : 다목적 여유 공간
        };

        Data data;

    public:
        RayBuffer() : ConstBuffer(&data, sizeof(Data)) {}
        Data& Get() { return data; }
    };

    // 입출력 결과를 구조체로
    struct InputDesc // desc : 결과에 대한 의미 설명
    {
        // 어디를 찍었는가?
        Float3 v0;
        Float3 v1;
        Float3 v2;
    };

    struct OutputDesc
    {
        int picked;
        float distance;
    };

public:
    TerrainEditor();
    ~TerrainEditor();

    void Update();
    void Render();
    void RenderUI();

    Vector3 Pick();        // 찍는 행동
    Vector3 ComputePick(); // 찍고 계산하기 ( 필요하면 처리하기 )

private:
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();

    // 편집 지형 만들기
    void MakeComputeData();  // 계산된 데이터 만들기
    void Reset();            // 데이터 초기화
    void Resize();           // 데이터 크기 초기화

    UINT width;
    UINT height;
    UINT triangleSize; // 삼각형의 크기 : 클릭 중 처리될 범위

    Mesh<VertexType>* mesh;

    // 지형 편집 중에 필요한 데이터들
    // * 브러시 버퍼 : 지금 얼마만큼을 어떻게 바꿀 건가?
    // * 레이 버퍼   : 마우스 커서의 입력을 얼마나 어느 범위로 벋울 건가?
    BrushBuffer* brushBuffer;
    RayBuffer* rayBuffer;
    StructuredBuffer* structuredBuffer; // 지형이 구조화된 모양을 저장하는 버퍼

    // 있으면 좋은 데이터
    // * 입력 결과
    // * 출력 결과
    // 해당 결과들의 집합 ( 벡터 )

    vector<InputDesc> inputs;
    vector<OutputDesc> outputs;

    Texture* heightMap;

    Vector3 pickingPos;

    // 보정된 지형의 모습을 출력하기 위한 조정된 점정 셰이더 ( 컴퓨트 셰이더 )
    // * 연산 셰이더
    ComputeShader* computeShader;
};


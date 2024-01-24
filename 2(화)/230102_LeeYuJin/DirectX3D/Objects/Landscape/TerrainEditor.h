#pragma once

class TerrainEditor : public GameObject
{
    // 클래스의 목적 : 터레인 픽커의 기능을 더욱 확장해서,
    //                클릭에 따라 지형의 세부 모양이 앱 내에서도 바뀔 수 있도록 만들기

private:
    //브러시의 종류
    enum BrushType
    {
        CIRCLE, // 원
        SOFT_CIRCLE, // 가장자리가 흐린 (중심이 작은) 원
        RECT, // 직사각형
    };

    enum EditType // 브러시를 그으면 어떻게 되는가?
    {
        HEIGHT, // 높이 조정 (기본)
        ALPHA, // 투명값 조정
        NONE, // 아무 일도 없음 (맨 마지막에)
    };

private:
    typedef VertexUVNormalTangentAlpha VertexType;
    const float MAX_HEIGHT = 20.0f; // 최대 높이 미리 정해놓기
    const float MIN_HEIGHT = -20.0f; // 최소 높이 같이 정해놓기

    //프레임워크 헤더에 있던 데이터를 이곳으로 가져온다면 아래 주석을 활성화
    // -> 보험 코드
    //const UINT MAX_SIZE = 30;


    //브러시 버퍼와 레이 버퍼

    class BrushBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            int type = 0; // 이 브러시의 타입
            Float3 pickingPos; // 찍고 있는 좌표
            float range = 5.0f; //기본 범위
            Float3 color = { 0, 0, 1 }; //파란색. 0, 1, 0이면 초록색
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
            Float3 pos; //광원
            int triangleSize; //영향범위

            Float3 dir; //방향
            float padding; //"유격" : 다목적 여유 공간
        };
        Data data;

    public:
        RayBuffer() : ConstBuffer(&data, sizeof(Data)) {}
        Data& Get() { return data; }
    };

    //입출력 결과를 구조체로
    struct InputDesc //desc : 결과에 대한 의미설명
    {
        //어디를 찍었는가?
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

    Vector3 Pick();
    Vector3 ComputePick(); //찍고 계산하기 (필요하면 처리하기)
    Vector3 ComputePick(Vector3 sourcePos); // 매개변수가 있는 오버로드 함수
                                            // 내용에선 위 함수와 거의 같지만
                                            // 마우스 위치 대신 매개변수를 받는다
                                            // 자원에서 불리하지만 (비효율적 오버로드)
                                            // 순간의 계산을 빠르게 하기 위해 사용
    
    bool IsComputePick(Vector3& pos);     // 컴퓨트 픽과 역시 거의 같고,
                                          // 대신 미리 정해둔 변수에 결과를 저장하면서
                                          // 반환형은 boolean을 주는 함수

    float GetHeightByPos(Vector3 myPos);  // 매개변수가 주어지면 해당 데이터에 맞는 지형의 높이를 검출

private:
    //초기 지형
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();

    //편집 지형 만들기
    
    // 전체 데이터 총괄
    void MakeComputeData(); //계산된 데이터 만들기
    void Reset();  //데이터 초기화
    void Resize(); //데이터 크기 초기화

    // 세부 편집
    void UpdateHeight(); // 높이 업데이트 (조정이 생길 경우 반영, 혹은 직접 조정 수행)
    void AdjustHeight(); // 높이 "조정"   (변경, 혹은 업데이트 후 보정)
    // * 선언 단계에서는 어느 쪽이 먼저일지 확신이 안 되지만, 일단 이 두 함수는 별개,
    //   그러면서도 한 세트라는 점은 분명하다 (한쪽은 수행, 한쪽은 최종 확정)
    
    void UpdateAlpha(); // 알파 업데이트
    void AdjustAlpha(); // 알파 조정

    // ImGUI 내에서 조작 가능한 추가 기능
    // 높이 세이브 로드
    void SaveHeightMap();
    void LoadHeightMap();

    // 알파 세이브 로드
    void SaveAlphaMap();
    void LoadAlphaMap();

    // ImGUI 세이브 로드에 쓸 경로명 데이터 (파일명은 호출할 때 넣을 테니까)
    string projectPath;

    UINT width;
    UINT height;
    UINT triangleSize; // 삼각형의 크기 : 클릭 중 처리될 범위

    UINT selectMap = 0;

    //브러시 전용 데이터 (기본값도 세팅)
    float adjustValue = 10.0f; //조정할 값 (강도, 혹은 범위)
    BrushType brushType = BrushType::CIRCLE;
    EditType editType = EditType::HEIGHT; // 높이부터 정하기

    Mesh<VertexType>* mesh;

    // 지형 편집 중에 필요한 데이터들
    // * 브러시 버퍼 : 지금 얼만큼을 어떻게 바꿀 건가?
    // * 레이 버퍼 : 마우스 커서의 입력을 어느 범위로 받을 건가?
    BrushBuffer* brushBuffer;
    RayBuffer* rayBuffer;
    StructuredBuffer* structuredBuffer; //지형이 구조화된 모양을 저장할 버퍼

    //있으면 좋은 데이터
    // * 입력 결과
    // * 출력 결과
    // 해당 결과들의 집합 (벡터)
    vector<InputDesc> inputs;
    vector<OutputDesc> outputs;

    // 맵에 쓸 텍스처 미리 준비
    Texture* heightMap;
    Texture* secondMap;
    Texture* thirdMap;

    Vector3 pickingPos;

    //보정된 지형의 모습을 출력하기 위한 조정된 출력 정점 셰이더(컴퓨트 셰이더)
    // *연산 셰이더
    ComputeShader* computeShader;

};
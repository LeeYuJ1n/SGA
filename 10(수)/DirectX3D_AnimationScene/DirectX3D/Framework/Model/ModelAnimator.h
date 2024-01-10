#pragma once

class ModelAnimator : public Model
{
    // 모델의 움직임을 관리하는 클래스, 혹은 움직임을 보여줄 모델 그 자체까지 통칭

protected:

    // 움직임 데이터를 따오기 위한 구조체
    struct Frame
    {
        int clip = 0;       // 프레임에 기록되었던 클립의 코드
        UINT curFrame = 0;  // 현재 프레임
        float time = 0;     // 시간
        float scale = 1;    // 스케일

        // 움직임의 정보와 지금의 데이터를 한 곳에 모으기
    };

    class FrameBuffer : public ConstBuffer
    {
    public:
        struct Data
        {
            float takeTime = 0.2f;  // 전체 시간
            float tweenTime = 0;    // 전환 시간
            float runningTime = 0;  // 재생 시간
            float padding;          // 동작이 일찍 끝난 경우 (시작 전에 필요해도) 여백

            Frame cur;  //지금 프레임
            Frame next; //다음 프레임
        };

    public:
        FrameBuffer() : ConstBuffer(&data, sizeof(Data))
        {
            data.next.clip = -1; // -1 : "그런 거 없음"
        }
        Data& Get() { return data; }

    private:
        Data data;
    };

public:

    ModelAnimator(string name); // 애니메이션, 혹은 움직임을 가진 모델 자체의 이름 받기
    ~ModelAnimator();

    void Update();
    void Render();
    void GUIRender();

    //동작 준비하기 (읽기)
    void ReadClip(string clipName, UINT clipNum = 0); // 매개변수 : 클립의 이름과 시작 인덱스

    //동작 재생하기
    void PlayClip(int clip, float scale = 1.0f, float takeTime = 0.2f);

    //노드에서 행렬 받기
    Matrix GetTransformByNode(int nodeIndex); // 노드의 인덱스가 필요

    // 0109 : 클립 밖에서 호출하기
    ModelClip* GetClip(UINT index) { return clips[index]; }

protected:

    // 텍스처를 애니메이션에 맞게 재생성
    void CreateTexture();

    // 클립에서 트랜스폼 정보 재생성
    void CreateClipTransform(UINT index); // 무엇으로부터 생성할 것인가

    //프레임 업데이트
    void UpdateFrame();


    bool isPlay = true; //재생중 여부

    vector<ModelClip*> clips; // 동작의 목록

    FrameBuffer* frameBuffer; // 움직임 정보 준비해서 로딩하기

    ClipTransform* clipTransforms;
    ClipTransform* nodeTransforms;

    // 텍스처 클래스를 다 써도 되는데 모델의 경우 정점 등에 대한 연산, 기능이 메쉬와 다른 기능에 있어서
    // 굳이 만들어진 클래스를 다 안 써도 일단 DX 제공 클래스를 쓸 수 있다
    ID3D11Texture2D* texture = nullptr;
    ID3D11ShaderResourceView* srv; //셰이더에 의한 리소스 재연산 출력

    //필요하면 좀 더 복잡한 텍스처를 적용

};


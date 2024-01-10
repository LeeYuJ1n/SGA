#pragma once

class ModelAnimatorInstancing : public ModelAnimator
{
    // 동작과 동작까지 가진 모델을 인스턴싱 방식으로 관리

private:
    // 모델에 인스턴스 버퍼가 있었든, 애니메이터도 공통 동작을 담을 구조체를 따로 만들기

    // 애니메티어의 클립과 형태가 같은데 목적은 통합관리
    struct Motion
    {
        float takeTime = 0.2f;
        float tweenTime = 0.0f;
        float runningTime = 0.0f;
        float padding;

        Frame cur, next;

        Motion()
        {
            next.clip = -1;
        }
    };

    // 모셔를 통한 버퍼 관리도 애니메이터와 거의 같다
    class FrameInstancingBuffer : public ConstBuffer
    {
    public:
        struct Data
        {
            Motion motions[MAX_INSTANCE];
        };

    public:
        FrameInstancingBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        }

        Data& Get() { return data; }

    private:
        Data data;
    };

public:
    ModelAnimatorInstancing(string name);
    ~ModelAnimatorInstancing();

    void Update();
    void Render();
    void GUIRender();

    Transform* Add();

    // 각 고유 개체가 어떤 (몇 번)동작을 수행할 것인가 (이런 것만 객체들이 따로 논다)
    void PlayClip(UINT instanceID, int clip, float scale = 1.0f, float takeTime = 0.1f);

private:    
    void UpdateFrame(UINT instanceID, Motion& motion);
    void UpdateTransforms();

private:
    // 애니메이터와 별도로 하나 더 돌아가는 공통 데이터들

    vector<Transform*> transforms;
    InstanceData instanceDatas[MAX_INSTANCE];

    VertexBuffer* instanceBuffer;
    FrameInstancingBuffer* frameInstancingBuffer;

    // 드로우 유닛 / 콜 세기
    UINT drawCount = 0;
};
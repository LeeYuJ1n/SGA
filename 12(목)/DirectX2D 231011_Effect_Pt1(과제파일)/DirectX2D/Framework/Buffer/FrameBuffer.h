#pragma once

// 색 정보(셰이더)에 더해서 프레임 길이까지 더한 정보저장(버퍼)

class FrameBuffer : public ConstBuffer
{
private:
    struct Data
    {
        Vector2 maxFrame;
        Vector2 curFrame;
    };
    Data data;

public:
    FrameBuffer() : ConstBuffer(&data, sizeof(Data))
    {
    }

    void SetMaxFrame(Vector2 maxFrame) { this->data.maxFrame = maxFrame; }

    Vector2& GetCurFrame() { return this->data.curFrame; }
};


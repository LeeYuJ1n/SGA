#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
    MatrixBuffer() : ConstBuffer(&matrix, sizeof(Matrix))
    {
        matrix = XMMatrixIdentity();
    }

    void Set(Matrix value)
    {
        matrix = XMMatrixTranspose(value);
    }

private:
    Matrix matrix;
};

class WorldBuffer : public ConstBuffer
{
private:
    struct Data
    {
        Matrix world = XMMatrixIdentity();
        
        int type = 0;

        float padding[3];
    };

public:
    WorldBuffer() : ConstBuffer(&data, sizeof(Data))
    {
    }

    void Set(Matrix value)
    {
        data.world = XMMatrixTranspose(value);
    }

    void SetType(int type)
    {
        data.type = type;
    }

private:
    Data data;
};

class ViewBuffer : public ConstBuffer
{
private:
    struct Data
    {
        Matrix view;
        Matrix invView;
    };

public:
    ViewBuffer() : ConstBuffer(&data, sizeof(Data))
    {
        data.view = XMMatrixIdentity();
        data.invView = XMMatrixIdentity();
    }

    void Set(Matrix view, Matrix invView)
    {
        data.view = XMMatrixTranspose(view);
        data.invView = XMMatrixTranspose(invView);
    }

private:
    Data data;
};

class ColorBuffer : public ConstBuffer
{
public:
    ColorBuffer() : ConstBuffer(&color, sizeof(Float4))
    {
    }

    Float4& Get() { return color; }

private:
    Float4 color = { 1, 1, 1, 1 };
};

class IntValueBuffer : public ConstBuffer
{
public:
    IntValueBuffer() : ConstBuffer(values, sizeof(int) * 4)
    {
    }

    int* Get() { return values; }

private:
    int values[4] = {};
};

class FloatValueBuffer : public ConstBuffer
{
public:
    FloatValueBuffer() : ConstBuffer(values, sizeof(float) * 4)
    {
    }

    float* Get() { return values; }

private:
    float values[4] = {};
};

class LightBuffer : public ConstBuffer
{
    // 빛 버퍼 : 3D에서 음영을 만들기 위한 픽셀 셰이더에 들어가는 변수를 따로 집합시킨 것
    //          여기의 변수들을 픽셀 셰이더나 전문 빛 셰이더에 전달해서 색조를 변경한다
public:
    struct Light
    {
        Float4 color = { 1, 1, 1, 1 };      // 빛의 색
        Float3 direction = { 0, -1, 1 };    // 빛이 나가는 방향
        int type = 0;                       // *광원 유형
                                            //  

        Float3 pos = { 0, 0, 0 };           // 광원 위치
        float range = 100.0f;               // *광범위 : 빛이 미치는 범위
                                            //           여기서 "범위"의 정의는 유형마다 다르다
                                            //           = 빛의 유형을 알아야 범위도 알 수 있다

        float inner = 55.0f;                // 광원의 내적 크기 (중요치 않다*)
        float outer = 70.0f;                // 광원의 외적 크기 (중요치 않다*)
        float length = 50.0f;               // *광거리 : 특정 유형에서 유효. 빛이 미치는 거리
        int active = 1;                     // *활성화 여부(bool이어야 하는데 셰이더는 bool을 많이 쓰지 않아서 int)
    };
private:
    struct Data
    {
        Light lights[MAX_LIGHT];

        UINT lightCount = 1;
        Float3 ambientLight = { 0.1f, 0.1f, 0.1f };
        Float3 ambientCeil = { 0.1f, 0.1f, 0.1f };
        float padding;
    };

public:
    LightBuffer() : ConstBuffer(&data, sizeof(Data))
    {
    }

    Data& Get() { return data; }

private:
    Data data;
};

class WeatherBuffer : public ConstBuffer
{
private:
    struct Data
    {
        Float3 velocity = { 0, -1, 0 };
        float distance = 100.0f;

        Float4 color = { 1, 1, 1, 1 };

        Float3 origin = {};
        float time = 0.0f;

        Float3 size = { 50, 50, 50 };
        float turbulence = 5.0f;
    };
public:
    WeatherBuffer() : ConstBuffer(&data, sizeof(Data))
    {
    }

    Data& Get() { return data; }

private:
    Data data;
};

class FogBuffer : public ConstBuffer
{
private:
    struct Data
    {        
        Float4 color = { 1, 1, 1, 1 };

        float start = 0.0f;
        float random = 1.0f;

        float padding[2];
    };
public:
    FogBuffer() : ConstBuffer(&data, sizeof(Data))
    {
    }

    Data& Get() { return data; }

private:
    Data data;
};
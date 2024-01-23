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

// 색을 나타내고 정보를 메모리에 저장하기 위한 버퍼 //출력 등에도 쓸 것
class ColorBuffer : public ConstBuffer
{
public:
    ColorBuffer() : ConstBuffer(&color, sizeof(Float4))
    {
        color = { 1, 1, 1, 1 };
    }

    void Set(Float4 color)
    {
        this->color = color;
    }

    Float4& Get() { return color; }

private:
    Float4 color = { 1, 1, 1, 1 }; // 사전초기화, 확인사살
};

// 정수만 쓰는 버퍼 만들기
class IntValueBuffer : public ConstBuffer
{
public:
    IntValueBuffer() : ConstBuffer(values, sizeof(int) * 4) {}

    int* Get() { return values; }

private:
    int values[4] = {};
};

// 소수만 쓰는 버퍼 만들기
class FloatValueBuffer : public ConstBuffer
{
public:
    FloatValueBuffer() : ConstBuffer(values, sizeof(float) * 4) {}

    float* Get() { return values; }

private:
    float values[4] = {};
};
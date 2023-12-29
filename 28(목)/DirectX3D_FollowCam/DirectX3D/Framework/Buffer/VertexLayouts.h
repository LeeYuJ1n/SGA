#pragma once

struct Vertex
{
    Float3 pos;

    Vertex()
    {
        pos = { 0.0f, 0.0f, 0.0f };
    }

    Vertex(float x, float y, float z)
    {
        pos = { x, y, z };
    }
};

struct VertexUV
{    
    Float3 pos;
    Float2 uv;

    VertexUV() : pos(0, 0, 0), uv(0, 0)
    {
    }

    VertexUV(float x, float y, float z, float u, float v)
        : pos(x, y, z), uv(u, v)
    {     
    }
};

struct VertexColor
{
    Float3 pos;
    Float4 color;

    VertexColor()
    {
        pos = { 0.0f, 0.0f, 0.0f };
        color = { 1, 1, 1, 1 };
    }

    VertexColor(float x, float y, float z, float r, float g, float b)
    {
        pos = { x, y, z };
        color = { r, g, b, 1 };
    }
};

struct VertexUVNormal
{
    Float3 pos;
    Float2 uv;
    Float3 normal;

    VertexUVNormal() : pos(0, 0, 0), uv(0, 0), normal(0, 0, 0)
    {
    }
};

struct VertexUVNormalTangent
{
    Float3 pos;
    Float2 uv;
    Float3 normal;
    Float3 tangent;

    VertexUVNormalTangent()
        : pos(0, 0, 0), uv(0, 0), normal(0, 0, 0), tangent(0, 0, 0)
    {
    }
};

struct VertexUVNormalTangentAlpha
{
    Float3 pos = {}; // 정점(혹은 화소)의 위치
    Float2 uv = {};  // 텍스처가 있으면 텍스처의 위치
    Float3 normal = {};  // z축계산이 필요한가?
    Float3 tangent = {}; // z축 선의 방향이 어떻게 되는가
    float alpha[4] = {}; // 투명값도 넣어야 하는가?

    VertexUVNormalTangentAlpha()
    {
    }
};
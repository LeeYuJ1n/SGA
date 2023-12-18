#pragma once

class Sphere : public GameObject
{
    // 스피어(구체) : 2D에서 사용했던 원의 확장된 형태
    //               마찬가지로 지름과 분절점ㅇ
private:
    typedef VertexUVNormalTangent VertexType;

public:
    Sphere(float radius = 1.0f, UINT sliceCount = 32, UINT stackCount = 16);
    ~Sphere();

    void Render() override;

private:
    void MakeMesh();
    void MakeTangent();

private:
    Mesh<VertexType>* mesh;

    float radius;
    UINT sliceCount, stackCount;
};
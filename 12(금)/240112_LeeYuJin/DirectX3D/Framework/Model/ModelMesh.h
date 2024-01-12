#pragma once

class ModelMesh
{
public:
    ModelMesh(string name);// 이름을 받아서 메쉬 만들기
    ~ModelMesh();

    void Render();
    void RenderInstanced(UINT instanceCount);

    void CreateMesh(void* vertexData, UINT vertexCount, void* indexData, UINT indexCount);
    //void* : 원본 포맷이 뭐일지 모르니까, 혹은 무엇이라도 대응 가능하도록
//        (2D에서 버튼을 만들던 때와 비슷)

    void SetMaterial(Material* material) { this->material = material; }
private:
    string name; // 이 메쉬의 이름

    Material* material;
    Mesh<ModelVertex>* mesh;
};
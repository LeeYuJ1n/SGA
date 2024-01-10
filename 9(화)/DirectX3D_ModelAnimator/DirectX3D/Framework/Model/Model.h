#pragma once
class Model : public Transform
{
public:
    Model(string name);
    ~Model();

    void Render();
    void GUIRender();

    void SetShader(wstring file);

private:
    //원본 파일에서 데이터 가져오기
    void ReadMaterial();
    void ReadMesh();

protected:
    //이후 상속받을 다른 물체들과 데이터 공유

    string name;

    vector<Material*> materials;
    vector<ModelMesh*> meshes;
    vector<NodeData> nodes;
    vector<BoneData> bones;

    map<string, UINT> boneMap;

    //private:
    MatrixBuffer* worldBuffer;
};


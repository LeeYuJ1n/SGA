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
    //���� ���Ͽ��� ������ ��������
    void ReadMaterial();
    void ReadMesh();

protected:
    //���� ��ӹ��� �ٸ� ��ü��� ������ ����

    string name;

    vector<Material*> materials;
    vector<ModelMesh*> meshes;
    vector<NodeData> nodes;
    vector<BoneData> bones;

    map<string, UINT> boneMap;

    //private:
    MatrixBuffer* worldBuffer;
};


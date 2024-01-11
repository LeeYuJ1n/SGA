#include "Framework.h"

Model::Model(string name) : name(name)
{
    //������ ����
    ReadMaterial();
    ReadMesh();

    worldBuffer = new MatrixBuffer();
}

Model::~Model()
{
    for (Material* material : materials)
        delete material;

    for (ModelMesh* mesh : meshes)
        delete mesh;

    delete worldBuffer;
}

void Model::Render()
{
    //Ʈ������ ��� ������ ���� �����ϰ� ���� ����
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    for (ModelMesh* mesh : meshes)
        mesh->Render();
}

void Model::GUIRender()
{
    Transform::GUIRender();

    for (Material* material : materials)
        material->GUIRender();
}

void Model::SetShader(wstring file)
{
    for (Material* material : materials)
        material->SetShader(file); // �׸� �ϳ��ϳ��� ���̴� �� ����
}

void Model::ReadMaterial()
{
    string file = "Models/Materials/" + name + "/" + name + ".mats";

    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())// ������ ���ų� �ջ�ƴٸ�
        assert(false);     // ��� ������ �߻��ϰ� ���� ����

    UINT size = reader->UInt();

    materials.reserve(size);

    FOR(size)
    {
        Material* material = new Material(); // �⺻ ��Ƽ����(�ؽ�ó) ����
        material->Load(reader->String()); //���Ͽ��� ���� �о� �����ϱ�
        materials.push_back(material); //������� ���� �ؽ�ó�� ���Ϳ� �߰�
    }

    delete reader;
}

void Model::ReadMesh()
{
    string file = "Models/Meshes/" + name + ".mesh";

    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())// ������ �����ų� �ջ�ưų�...
        //return           // �Ѵٸ� ��� ���� (�⺻)
        assert(false);     // "���Ἲ ���� �Լ�" �����ϸ鼭 false ���� ���Ƿ� �ֱ� : ��� ����Ǹ鼭 ���� �޽������� �����
    // assertation : Ư�� �����̳� �����͸� �ְ� �ݵ�� �ش� ������ �ϼ��ϵ��� �����ϴ� ���
    // ������ ���� ����ϸ� �����ڰ� ����ڿ��� Ư�� ������ ���� ����

    UINT size = reader->UInt(); // �ҷ��� �������� ũ��

    //...�� �޽ÿ� �̸� ����
    meshes.reserve(size);

    FOR(size)
    {
        ModelMesh* mesh = new ModelMesh(reader->String());// ������ �����鼭 ���� ��� ���� ���
        mesh->SetMaterial(materials[reader->UInt()]);     // ��� �̾����� ������ ���ڷ� ��Ƽ���� �����ϱ�

        UINT vertexCount = reader->UInt();
        ModelVertex* vertices = new ModelVertex[vertexCount];
        reader->Byte((void**)&vertices, sizeof(ModelVertex) * vertexCount);

        UINT indexCount = reader->UInt();
        UINT* indices = new UINT[indexCount];
        reader->Byte((void**)&indices, sizeof(UINT) * indexCount);

        // ������� ���� .mesh ���Ͽ��� ������ �ε����� ������ ��´�

         //�޾ƿ� ����, �ε���, �� ������ �� ������ �ְ�, �ǵ���ϸ鼭 �޽� ����
        mesh->CreateMesh(vertices, vertexCount, indices, indexCount);

        //���� �޽ø� ���� �޽� ���Ϳ� �ֱ�
        meshes.push_back(mesh);
    }

    // 0109 ���� : ��� �� ���� �������� 

    //----------------------------------------------

    // �� ������ ��尡 ���� ���, �ش� ��带 �ϳ��ϳ� ���� �����ϱ�
    size = reader->UInt();
    nodes.resize(size);
    for (NodeData& node : nodes)
    {
        node.index = reader->Int();
        node.name = reader->String();
        node.parent = reader->Int();
        node.transform = reader->Matrix();
    }

    // ���븦 ã�Ƽ� ���� �����ϱ�
    size = reader->UInt();
    bones.resize(size);
    for (BoneData& bone : bones)
    {
        bone.index = reader->Int();
        bone.name = reader->String();        
        bone.offset = reader->Matrix();

        boneMap[bone.name] = bone.index;
    }

    delete reader;

    //-----------------------------------------------
}

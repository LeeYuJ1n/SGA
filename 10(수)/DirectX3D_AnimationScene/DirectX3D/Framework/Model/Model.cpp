#include "Framework.h"

Model::Model(string name) : name(name)
{
    //데이터 생성
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
    //트랜스폼 행렬 공간에 버퍼 적용하고 정점 세팅
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
        material->SetShader(file); // 그림 하나하나에 셰이더 다 적용
}

void Model::ReadMaterial()
{
    string file = "Models/Materials/" + name + "/" + name + ".mats";

    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())// 파일이 없거나 손상됐다면
        assert(false);     // 즉시 오류를 발생하고 강제 종료

    UINT size = reader->UInt();

    materials.reserve(size);

    FOR(size)
    {
        Material* material = new Material(); // 기본 매티리얼(텍스처) 생성
        material->Load(reader->String()); //파일에서 내용 읽어 적용하기
        materials.push_back(material); //만들어진 외장 텍스처를 벡터에 추가
    }

    delete reader;
}

void Model::ReadMesh()
{
    string file = "Models/Meshes/" + name + ".mesh";

    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())// 파일이 없었거나 손상됐거나...
        //return           // 한다면 즉시 종료 (기본)
        assert(false);     // "무결성 강제 함수" 실행하면서 false 값을 고의로 주기 : 즉시 종료되면서 오류 메시지까지 만들기
    // assertation : 특정 조건이나 데이터를 주고 반드시 해당 조건을 완수하도록 강제하는 기능
    // 적절한 곳에 사용하면 개발자가 사용자에게 특정 조건을 강요 가능

    UINT size = reader->UInt(); // 불러온 데이터의 크기

    //...를 메시에 미리 예약
    meshes.reserve(size);

    FOR(size)
    {
        ModelMesh* mesh = new ModelMesh(reader->String());// 파일을 읽으면서 나온 대로 정점 찍기
        mesh->SetMaterial(materials[reader->UInt()]);     // 계속 이어지는 배정된 숫자로 매티리얼 배정하기

        UINT vertexCount = reader->UInt();
        ModelVertex* vertices = new ModelVertex[vertexCount];
        reader->Byte((void**)&vertices, sizeof(ModelVertex) * vertexCount);

        UINT indexCount = reader->UInt();
        UINT* indices = new UINT[indexCount];
        reader->Byte((void**)&indices, sizeof(UINT) * indexCount);

        // 여기까지 오면 .mesh 파일에서 정점과 인덱스의 정보를 얻는다

         //받아온 정점, 인덱스, 각 정보의 총 개수를 주고, 피드백하면서 메시 생성
        mesh->CreateMesh(vertices, vertexCount, indices, indexCount);

        //만들어낸 메시를 모델의 메시 벡터에 넣기
        meshes.push_back(mesh);
    }

    // 0109 수정 : 노드 후 뼈대 적용으로 

    //----------------------------------------------

    // 모델 내에서 노드가 나뉜 경우, 해당 노드를 하나하나 따로 구현하기
    size = reader->UInt();
    nodes.resize(size);
    for (NodeData& node : nodes)
    {
        node.index = reader->Int();
        node.name = reader->String();
        node.parent = reader->Int();
        node.transform = reader->Matrix();
    }

    // 뼈대를 찾아서 뼈대 적용하기
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

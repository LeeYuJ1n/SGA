#include "Framework.h"

ModelExporter::ModelExporter(string name, string file)
    :name(name)
{
    importer = new Assimp::Importer(); // ������ ȣ��

    importer->SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false); // �ڱ� ��ü �� �ɼ��� ȣ���ؼ� �����ϴ� �Լ�
    // �Ű����� �ɼ� = "�������� FBX ������ ������ ���ǵ� ȸ���� ������ �ֳ���? / �ƴϿ�."
    importer->SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_TANGENTS_AND_BITANGENTS); // ���������� �ɼ� ����
    // �Ű����� �ɼ� = "������ �����ؼ� �����;� �ϳ���? / ȭ���� ���������� ���� �������ּ���!"

// �ּ� ����Ʈ�� ȣ���� ���� �߰� ����
    scene = importer->ReadFile(file, // �Ű������� ���� ������ �����ؼ� �б�
        aiProcessPreset_TargetRealtime_MaxQuality | //�� �о���̱� ������ �̸� ������ �ɼǿ��� 1�� ����, ������ = �ֻ��
        aiProcess_Triangulate |                     //3���� ������ �⺻���� 3D ������ ����
        aiProcess_GenSmoothNormals |                //�������� ������ �ʹ� Ŀ���� �ʵ��� ��ó�� ���� (ǥ���� ����������� �ʰ� �ε巯������)
        aiProcess_FixInfacingNormals |              //�������� �� (Ư�� ī�޶���) �������� ����� �� ��ó���� ���� ��ü ����� ������ ������ �ʴ� ����� �� ������
        aiProcess_RemoveRedundantMaterials |        //�������ϰų� ���ʿ� ������ �� �� ��Ƽ������ ������ �б⿡�� ����
        aiProcess_OptimizeMeshes |                  //����� ����� ����ؼ� �������� ��� �δ��� ����ȭ
        aiProcess_ValidateDataStructure |           //���� �������� ���� ����ü���� �ʿ��� �����͸� ��� ������ ��Ҵ��� Ȯ���ϰ�, ������
        aiProcess_ImproveCacheLocality |            //�޸𸮸� �� �� �ִ��� �����͵��� ������� �ʰ� ��� (������ ���� ���, �ӵ� ���)
        aiProcess_JoinIdenticalVertices |           //��ġ�� �Ȱ��ٰ� �Ǵ��ص� �� �������� ������ ���߿� ������ ���ܵ� �������� �ʰ� ���̱�
        aiProcess_FindInvalidData |                 //���� �߿� � ������ �������� �����Ͱ� �������� �Ǻ�
        aiProcess_TransformUVCoords |               //Ʈ�������� UV ��ǥ�� ���� ��� (�ؽ�ó�� ���� ��� ���)
        aiProcess_FlipUVs |                         //�ؽ�ó�� UV�� ������ �ٸ��ٰų�, �� ��ü�� �ݴ� �����̾ UV�� ����� �ν�
        aiProcess_ConvertToLeftHanded);             //����� ������ ���ͷ� ǥ���� ��, �޼� ��ǥ��� �ٲ۴ٴ� �� = DX�� �����

    assert(scene != nullptr); // ���� �� ������ ���� ����
    // = "�� �����ӿ�ũ�� FBX Ȥ�� �ٸ� ���� �� �����Ͱ� ������ ���� �����ϰڽ��ϴ�."
}

ModelExporter::~ModelExporter()
{
    delete importer;

    // delete scene; // ai���� ���� ����

    // �� ���� �����Ͱ� �� ��ü�� �� �ű� ������
    // ����ٸ� ����/���� ���� ������ ����� �� ���� �� : ���⼭�� �ϴ� ����
    //vector<Material*> materials;
    //vector<MeshData*> meshes;
    //vector<NodeData*> nodes;
    //vector<BoneData*> bones;

}

//�ۿ��� ȣ���ϱ� ���� ��ɵ�
void ModelExporter::ExportMaterial()
{
    // �о ȣ���ϰ� �������
    ReadMaterial();
    WriteMaterial();
}

void ModelExporter::ExportMesh()
{
    //������ �ϳ��� �б�
    ReadNode(scene->mRootNode, -1, -1); // root node : ���� ������ �ִ�, ��ü �� ��ü�� �Ѱ��ϴ� ���
    ReadMesh(scene->mRootNode); //��絵 �б�
    WriteMesh();
}

void ModelExporter::ExportClip(string clipName)
{
    FOR(scene->mNumAnimations) // �о���� ���Ͽ��� ���ϵ� �ִϸ��̼��� ����ŭ i�� ���� �ݺ����� ������
    {
        Clip* clip = ReadClip(scene->mAnimations[i]); // i��° �ִϸ��̼��� �����ϴ� �������� Ŭ������ �б�
        WriteClip(clip, clipName, i);
    }
}


// ���� ��ɵ�
void ModelExporter::ReadMaterial()
{
    FOR(scene->mNumMaterials) // ���� ���ϵ� ��Ƽ���� ����ŭ �ݺ�
    {
        aiMaterial* srcMaterial = scene->mMaterials[i]; // srcMaterial = source ��Ƽ����
        Material* material = new Material();

        material->GetName() = srcMaterial->GetName().C_Str(); // �ҽ� ��Ƽ������ �̸��� ��Ʈ������ ����

        aiColor3D color; //�� �޾ƿ���
        Material::MaterialBuffer::Data& data = material->GetData(); // ��Ƽ���� ������ �޾ƿ���

        //�ҽ��� �� ������ �޾Ƽ� �����ϱ�
        srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color); // ��ǻ� �÷��� �����ϱ� (�Ű������� ����->��� ��)
        data.diffuse = Float4(color.r, color.g, color.b, 1); // ��ǻ� ���� �����ؼ� �����Ϳ� �����ϱ�

        srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color); // �ݻ������� �÷��� �����ϱ� (�Ű������� ����->��� ��)
        data.diffuse = Float4(color.r, color.g, color.b, 1); // �ݻ������� ���� �����ؼ� �����Ϳ� �����ϱ�

        srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color); // ��ο� ������ �÷��� �����ϱ� (�Ű������� ����->��� ��)
        data.diffuse = Float4(color.r, color.g, color.b, 1); // ��ο� ������ ���� �����ؼ� �����Ϳ� �����ϱ�

        srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color); // ���� ������ �÷��� �����ϱ� (�Ű������� ����->��� ��)
        data.diffuse = Float4(color.r, color.g, color.b, 1); // ���� ������ ���� �����ؼ� �����Ϳ� �����ϱ�

        srcMaterial->Get(AI_MATKEY_SHININESS, data.shininess); // ���� �޾Ƶ��̴� ������ ����

        aiString file;
        srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file); // ���Ͽ��� �ؽ�ó�� ���� ��� (��ǻ���)
        material->SetDiffuseMap(ToWString(CreateTexture(file.C_Str()))); // ������ �̸����� �ؽ�ó�� �����ؼ� ��Ƽ���� ����
        file.Clear(); //���� �б� �޸� �ʱ�ȭ

        srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file); // ���Ͽ��� �ؽ�ó�� ���� ��� (����ŧ����)
        material->SetDiffuseMap(ToWString(CreateTexture(file.C_Str()))); // ������ �̸����� �ؽ�ó�� �����ؼ� ��Ƽ���� ����
        file.Clear(); //���� �б� �޸� �ʱ�ȭ

        srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file); // ���Ͽ��� �ؽ�ó�� ���� ��� (��ָ�)
        material->SetDiffuseMap(ToWString(CreateTexture(file.C_Str()))); // ������ �̸����� �ؽ�ó�� �����ؼ� ��Ƽ���� ����
        file.Clear(); //���� �б� �޸� �ʱ�ȭ

        materials.push_back(material); // ���Ϳ� �ֱ�
    }

}

void ModelExporter::WriteMaterial()
{
    //���� ���� : ���⼭ ���� ���� ������ ����� ���� ����
    // * ȣȯ�� �ִ� ������ �ʿ��ϸ� �׶� ���� Ŭ������ �ҷ��� ����

    string savePath = "Models/Materials/" + name + "/";
    string fileName = name + ".mats"; // .mats, .mat : ��Ƽ���� �������� ������ �� ���� Ȯ���� (���⼱ ���� ������ �ٸ�����...)

    CreateFolders(savePath);

    BinaryWriter* writer = new BinaryWriter(savePath + fileName);

    writer->UInt(materials.size()); // �о�� �� ��Ƽ���� ���� �̸� ����

    for (Material* material : materials)
    {
        string path = savePath + material->GetName() + ".mat";
        material->Save(path);

        writer->String(path); // ���Ͽ� ������ ���, �̸� ��� ����

        delete material; // ������ �а� ���Ⱑ �����̴� ��Ƽ���� �� �� �� �ϳ��� �����
    }

    materials.clear(); //�� ���������� ���͵� �뵵 ����

    delete writer;
}

string ModelExporter::CreateTexture(string file)
{
    if (file.length() == 0)
        return ""; //�ƹ��͵� ���� ���� ����

    string fileName = GetFileNameWithoutExtension(file) + ".png"; //�����̸� �غ�
    string savePath = "Textures/Model/" + name + "/" + fileName;

    CreateFolders(savePath);

    const aiTexture* texture = scene->GetEmbeddedTexture(file.c_str()); // ���� �̸����� FBX ���� �ؽ�ó ��������

    if (texture == nullptr) // �׷� ���� �ؽ�ó�� ������ �� ����
        return "";

    if (texture->mHeight < 1)
    {
        BinaryWriter writer(savePath);
        writer.Byte(texture->pcData, texture->mWidth);
    }
    else
    {
        //�ؽ�ó ������ C++�� Image Ŭ������ �Űܴ��
        Image image;
        image.width = texture->mWidth;
        image.height = texture->mHeight;
        image.pixels = (uint8_t*)(texture->pcData); // 8����Ʈ int : ���� �׸� Ư���� �������� �ʹ� ���� ���� �־
        image.rowPitch = image.width * 4;
        image.slicePitch = image.width * image.height * 4;

        //����ϱ�(=�׸��� �ֱ�) : �߰��ɼ� ����, PNG, ��ġ�� ������ ���ڿ��� ����
        SaveToWICFile(image, WIC_FLAGS_NONE,
            GetWICCodec(WIC_CODEC_PNG), ToWString(savePath).c_str());
    }

    //��� ���� ��θ� ��ȯ
    return savePath;
}


void ModelExporter::ReadMesh(aiNode* node)
{
    FOR(node->mNumMeshes) // �Ű������� ���� ���� node�� ���� �޽� ������ ����...
    {
        MeshData* mesh = new MeshData();
        mesh->name = node->mName.C_Str();

        UINT index = node->mMeshes[i]; // ���� ���� �ִ� i��° �޽��� ��ϵ� �ε����� ��������
        aiMesh* srcMesh = scene->mMeshes[index]; // ������ �ε����� ���� ã�Ƴ� �޽�

        mesh->materialIndex = srcMesh->mMaterialIndex; // ��Ƽ������ �ε���(��) �޾ƿ���

        vector<VertexWeights> vertexWeights(srcMesh->mNumVertices);
        ReadBone(srcMesh, vertexWeights);// ���� ����⸦ ���⼭ ȣ��

        mesh->vertices.resize(srcMesh->mNumVertices);

        for (UINT v = 0; v < srcMesh->mNumVertices; ++v) // ������ v
        {
            ModelVertex vertex;
            memcpy(&vertex.pos, &srcMesh->mVertices[v], sizeof(Float3));

            if (srcMesh->HasTextureCoords(0)) // HasTextureCoords : �Ű������� ���� ������ �ؽ�ó ��ǥ�� �ִ°�?
                // true��� �ؽ�ó�� ���� ������ 1�� �̻� ����
            {
                memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][v], sizeof(Float2));
            }

            if (srcMesh->HasNormals()) // �޽��� ���� ������ ���� ���� �ִٸ�
            {
                memcpy(&vertex.normal, &srcMesh->mNormals[v], sizeof(Float3));
            }

            if (srcMesh->HasTangentsAndBitangents()) // ź��Ʈ(������ ���� ȭ�� ���� ����)�� ���� �ִٸ�
            {
                memcpy(&vertex.tangent, &srcMesh->mTangents[v], sizeof(Float3));
            }

            // ...�̷��� �޸� ī�Ǹ� ���ؼ� ���� �޽��� ������ �޸𸮷� �о���δ�

            //�װ��� mesh�� ����
            mesh->vertices[v] = vertex;
        }

        // ������� ����
        // ������� �ε���

        mesh->indices.resize(srcMesh->mNumFaces * 3); // ���� �޽��� �� ���� x 3

        for (UINT f = 0; f < srcMesh->mNumFaces; ++f)
        {
            aiFace& face = srcMesh->mFaces[f]; // ���� �ϳ��� �޾Ƽ�

            for (UINT k = 0; k < face.mNumIndices; ++k)
            {
                //�� �ϳ� �ǳʶ� ������ �ε��� 3�� �ǳʶٰ�, �� ���� ���� 3���� �ε��� �ޱ�
                mesh->indices[f * 3 + k] = face.mIndices[k];
            }
        }

        // ������� ���� �޽��� ���� ������ ��� ���δ�! (����, �ε���)

        meshes.push_back(mesh); // ���� �޽� ���
    }

    // ���� ������ ���� �� ��� �ؿ� �ٸ� ��尡 �ִ� ���
    // �ش� �ڽ� ��嵵 ��� ã�Ƽ� �޽� �б⸦ ����

    for (UINT i = 0; i < node->mNumChildren; ++i)
    {
        ReadMesh(node->mChildren[i]); // ����Լ��� �޽� �б⸦ �ݺ�
    }

    // ������� ���� ���ʷ� ���� node�� ��� �޽� �бⰡ ������
}

void ModelExporter::ReadNode(aiNode* node, int index, int parent)
{
    NodeData* nodeData = new NodeData();
    nodeData->index = index;
    nodeData->parent = parent;
    nodeData->name = node->mName.C_Str();

    Matrix matrix(node->mTransformation[0]);
    nodeData->transform = XMMatrixTranspose(matrix);

    nodes.push_back(nodeData);

    FOR(node->mNumChildren)
        ReadNode(node->mChildren[i], nodes.size(), index);
}

void ModelExporter::ReadBone(aiMesh* mesh, vector<VertexWeights>& vertexWeights)
{
    FOR(mesh->mNumBones)
    {
        UINT boneIndex = 0;
        string name = mesh->mBones[i]->mName.C_Str();

        if (boneMap.count(name) == 0) //���븦 ���� ���� ��������
        {
            boneIndex = boneCount++; // �� �ε���
            boneMap[name] = boneIndex; // �ε����� ���� �� �̸� �ֱ�

            BoneData* boneData = new BoneData(); // �� ���� ������
            
            boneData->name = name;
            boneData->index = boneIndex;

            Matrix matrix(mesh->mBones[i]->mOffsetMatrix[0]); // ������ �ִ� ������ ��� ������ ��������
            boneData->offset = XMMatrixTranspose(matrix); // ������ ����ġ = ��ķ� �ٽ� ���� ������ ���� ������

            // ���Ͽ��� �����͸� �о����, ��Ŀ� �°� ��ȯ�� ��
            // -> ���Ϳ� �־��ش�

            bones.push_back(boneData);
        }
        else
        {
            boneIndex = boneMap[name]; // ���� ���� ���� ���� �׳� �̸��� �޾ƿͼ� �ε����� ����
        }

        // ���� �б�� ������ �������� ���⿡ ����ġ �ֱ�

        for (UINT j = 0; j < mesh->mBones[i]->mNumWeights; ++j) // ����ġ�� ���� ����� �� ���󰡸鼭
        {
            // ���� ���� �ִ� ������, ó������ ���ư��� ����ġ��ŭ, �� ���� ���� �̸�(����)�� �޾ƿ���
            UINT index = mesh->mBones[i]->mWeights[j].mVertexId;
            //�޽� �������� ������� ����(�ӿ� �ִ� ����)�� ����ġ ����
            vertexWeights[index].Add(boneIndex, mesh->mBones[i]->mWeights[j].mWeight);
        }
    }
}

void ModelExporter::WriteMesh()
{
    string savePath = "Models/Meshes/" + name + ".mesh";

    CreateFolders(savePath);

    BinaryWriter* writer = new BinaryWriter(savePath);

    writer->UInt(meshes.size()); // ���Ͽ� �� ù ���� : �޽ð� �󸶳� �ִ°�?

    for (MeshData* mesh : meshes)
    {
        //�� ���� ���Ͽ� ���� �غ�
        writer->String(mesh->name); // �޽��� �̸�
        writer->UInt(mesh->materialIndex); //����

        writer->UInt(mesh->vertices.size()); // �޽� ������ ũ�⸸ŭ
        writer->Byte(mesh->vertices.data(), sizeof(ModelVertex) * mesh->vertices.size());

        writer->UInt(mesh->indices.size()); //�ε����� ��� ���̸�ŭ
        writer->Byte(mesh->indices.data(), sizeof(UINT) * mesh->indices.size());

        //�غ� �� ���� �޽��� �뵵 �� ��
        delete mesh;
    }
    //������� ���� �޽��� �� ������ ���Ͽ� ���� ��

    meshes.clear(); //���� ��Ҵ� ������ �� �ݺ������� �� �������ϱ�

    //��� ���� �ֱ�

    writer->UInt(nodes.size()); //��尡 �󸶳� �ִ°�?

    for (NodeData* node : nodes)
    {
        writer->Int(node->index);
        writer->String(node->name);
        writer->Int(node->parent);
        writer->Matrix(node->transform);

        //��� �� ������ ����ϰ� ���
        delete node;
    }
    // �� ������ ��� �ѵ� �����
    nodes.clear();

    //����
    writer->UInt(bones.size());

    for (BoneData* bone : bones)
    {
        writer->Int(bone->index);
        writer->String(bone->name);
        writer->Matrix(bone->offset);

        delete bone;
    }
    bones.clear();

    // ������� ���� �� Read~~�� ���� �޽�, ���, ���븦 ��� ���Ͽ� �ְ�, �޸𸮿����� ���� ��
    // ���� ���� �ν��Ͻ��� ���⼭ �����ϰ� �Լ� ��ġ����

    delete writer;
}

//Ű �����ӿ� ���� ������ ������ �������� ����
Clip* ModelExporter::ReadClip(aiAnimation* animation)
{
    Clip* clip = new Clip();
    clip->name = animation->mName.C_Str();
    clip->tickPerSecond = (float)animation->mTicksPerSecond;
    clip->frameCount = (UINT)(animation->mDuration) + 1;

    // Ŭ���� ���� ��带 ��� ���� ����
    vector<ClipNode> clipNodes;
    clipNodes.reserve(animation->mNumChannels); // �ִϸ��̼� �������(ä��)��ŭ ����
    FOR(animation->mNumChannels)
    {
        aiNodeAnim* srcNode = animation->mChannels[i]; // ���� ���

        ClipNode node;
        node.name = srcNode->mNodeName;

        // ���۰� ȸ�� �߿��� Ű�� �� ���� ���� ��� Ű �ִ� ���ڸ� �����Ѵ�
        UINT keyCount = max(srcNode->mNumPositionKeys, srcNode->mNumRotationKeys);
        keyCount = max(keyCount, srcNode->mNumScalingKeys); // ũ��͵� ���ؼ� �ٽ� �ִ밪 ����

        node.transforms.reserve(clip->frameCount);

        KeyTransform transform;

        // ���� ����� �� �ִ� Ű ���ڸ�ŭ �ݺ��� ����
        for (UINT k = 0; k < keyCount; ++k)
        {
            bool isFound = false;
            float t = node.transforms.size(); 

            //���� Ű�� ��ġ ������ ���� ���̰�, ������ �ð��� t�� ���ٸ�
            if (k < srcNode->mNumPositionKeys // ������ �ƴϰ� ���� ������ �� ��
                && NearlyEqual((float)srcNode->mPositionKeys[k].mTime, t))
            {
                aiVectorKey key = srcNode->mPositionKeys[k]; // ������ Ű�� ������ ��ġ�� Ű
                //���� ����
                memcpy_s(&transform.pos, sizeof(Float3), &key.mValue, sizeof(aiVector3D)); //ai���Ϳ��� Ʈ����������

                //�ʿ��� Ű�� ã�Ҵ�
                isFound = true;
            }

            //���� ����� ���ǹ�, �̹����� ȸ��
            if (k < srcNode->mNumRotationKeys
                && NearlyEqual((float)srcNode->mRotationKeys[k].mTime, t))
            {
                aiQuatKey key = srcNode->mRotationKeys[k]; // Quat : �����

                transform.rot.x = (float)key.mValue.x; // ������ n�� ����
                transform.rot.y = (float)key.mValue.y; // i
                transform.rot.z = (float)key.mValue.z; // j
                transform.rot.w = (float)key.mValue.w; // k

                isFound = true;
            }

            //�̹����� ũ��
            if (k < srcNode->mNumScalingKeys
                && NearlyEqual((float)srcNode->mScalingKeys[k].mTime, t))
            {
                aiVectorKey key = srcNode->mScalingKeys[k];

                memcpy_s(&transform.scale, sizeof(Float3), &key.mValue, sizeof(aiVector3D));

                isFound = true;
            }

            //������� ���� ������ ��ϵ� Ű ����� ���� ���鼭
            //��ġ, ȸ��, ũ�� ������ �ϳ��� ��ϵ� Ű Ʈ������ ������ ��� ã�Ƴ� ��

            //�׷��� ã�� �ڷᰡ �ִٸ�
            if (isFound)
            {
                //��忡 Ű Ʈ������ ���� �߰��ϱ�
                node.transforms.push_back(transform);
            }
        }

        // Ű Ʈ������ ���� �����ؼ� �ϳ��� ���ͷ� �������

        // ����� ���� Ʈ������ ���� ũ�Ⱑ ��ü �����ӿ� �� ���ڶ��ٸ�
        if (node.transforms.size() < clip->frameCount)
        {
            UINT count = clip->frameCount - node.transforms.size(); // ���̸� �� ������
            KeyTransform keyTransform = node.transforms.back(); // ������ Ű Ʈ������ �����ϰ�

            FOR(count) // ������ ��ŭ
                node.transforms.push_back(keyTransform); // ���� �ڿ� �� �߰�
        }

        clipNodes.push_back(node); // �� ������� ��带 Ŭ���� �־��ش�
    }
    // ������� ���� �� ����� �� �ִϸ��̼��� ���������
    // -> � ���ۿ���, ��� ������ ��� �������� �ϴ����� �����ϰ� ¥�δ�

    //�ش� ��� ������ ���� ������ ������ �ѹ� �� �д´� (Ű ������ ����)

    ReadKeyFrame(clip, scene->mRootNode, clipNodes);

    return clip; // �� �а� ���� ���� Ŭ���� ��ȯ
}

void ModelExporter::ReadKeyFrame(Clip* clip, aiNode* node, vector<ClipNode>& clipNodes)
{
    KeyFrame* keyFrame = new KeyFrame();

    keyFrame->boneName = node->mName.C_Str();
    keyFrame->transforms.reserve(clip->frameCount); // ������ ����ŭ ���� �����ϱ�

    FOR(clip->frameCount)
    {
        ClipNode* clipNode = nullptr; // �� ���

        //���ã��
        for (ClipNode& tmp : clipNodes)
        {
            if (tmp.name == node->mName)
            {
                clipNode = &tmp;
                break;
            }
        }

        KeyTransform keyTransform;
        if (clipNode == nullptr) // ���� �� ��������
        {
            Matrix transform(node->mTransformation[0]);
            transform = XMMatrixTranspose(transform);

            Vector3 S, R, T; // ũ��, ȸ��, ��ġ

            // ��� ����
            XMMatrixDecompose(S.GetValue(), R.GetValue(), T.GetValue(), transform);

            // S R T�� �� ����
            keyTransform.scale = S;
            XMStoreFloat4(&keyTransform.rot, R); //Store Float �Լ� : �Ҽ� ���� �� ����
            keyTransform.pos = T;
        }
        else // ���� �� �ִ� ���
        {
            keyTransform = clipNode->transforms[i]; //�״�� �ֱ�
        }

        //�غ�� keyTransform�� ���Ϳ� �߰�
        keyFrame->transforms.push_back(keyTransform);

    }

    // ������ ���� �غ�
    //...�� ���� �ٽ� Ŭ���� ������ ������ �ֱ�
    clip->keyFrame.push_back(keyFrame);

    //�ڽ� ��尡 ������ ��ͷ� ���� ���� �ݺ��ϰ� ��!
    FOR(node->mNumChildren) // �ڽ� ����ŭ �ݺ�
        ReadKeyFrame(clip, node->mChildren[i], clipNodes);
}

//�����ӿ� ���� ������ �����ؼ� �̸����� ��Ī�Ͽ� ����
void ModelExporter::WriteClip(Clip* clip, string clipName, UINT index)
{
    string fileName = "Models/Clips/" + name + "/" + clipName + to_string(index) // Ŭ�� �̸��� �ε���
        + ".clip"; // .clip Ȯ����

    CreateFolders(fileName);

    BinaryWriter* writer = new BinaryWriter(fileName);

    writer->String(clip->name);
    writer->UInt(clip->frameCount);
    writer->Float(clip->tickPerSecond); // �ʴ� ���� ��

    writer->UInt(clip->keyFrame.size());

    for (KeyFrame* keyFrame : clip->keyFrame)
    {
        writer->String(keyFrame->boneName); //���� �̸�
        writer->UInt(keyFrame->transforms.size()); //�󸶳� ������
        writer->Byte(keyFrame->transforms.data(), //��� ������
            sizeof(KeyTransform) * keyFrame->transforms.size());

        delete keyFrame;
    }

    delete clip;
    delete writer;
}

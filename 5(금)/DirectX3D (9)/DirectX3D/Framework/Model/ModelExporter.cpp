#include "Framework.h"

ModelExporter::ModelExporter(string name, string file) : name(name)
{
	importer = new Assimp::Importer(); // ������ ȣ��
	importer->SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false); 
	// �ڱ� ��ü �� �ɼ��� ȣ���ؼ� �����ϴ� �Լ�
	// �Ű����� �ɼ�  = "�������� FBX ������ ������ ���ǵ� ȸ���� ������ �ֳ���? / �ƴϿ�."
	importer->SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_TANGENTS_AND_BITANGENTS); // ���������� �ɼ� ����
	// �Ű����� �ɼ� = "������ �����ؼ� �����;� �ϳ���? / ȭ���� ���������� ���� �������ּ���!

	// ���� ����Ʈ�� ȣ���� ���� �߰� ����
	scene = importer->ReadFile(file, // �Ű������� ���� ������ �����ؼ� �б�
		aiProcessPreset_TargetRealtime_MaxQuality | // �� �о���̱� ������ �̸� ������ �ɼǿ��� 1�� ����, ������ = �ֻ��
		aiProcess_Triangulate |                     // 3���� ������ �⺻���� 3D ������ ����
		aiProcess_GenSmoothNormals |                // �������� ������ �ʹ� Ŀ���� �ʵ��� ��ó�� ����
		aiProcess_FixInfacingNormals |              // �������� �� (Ư�� ī�޶���) �������� ����� �� ��ó���� ���� ��ü ����� ������ ������ �ʴ� ����� �� ������
		aiProcess_RemoveRedundantMaterials |        // �������ϰų� ���ʿ� ������ �� �� ��Ƽ������ ������ �б⿡�� ����
		aiProcess_OptimizeMeshes |                  // ����� ����� ����ؼ� �������� ��� �δ��� ����ȭ
		aiProcess_ValidateDataStructure |           // ���� �������� ���� ����ü���� �ʿ��� �����͸� ��� ������ ��Ҵ��� Ȯ���ϰ�, ������
		aiProcess_ImproveCacheLocality |            // �޸𸮸� �� �� �ִ��� �����͵��� ������� �ʰ� ��� (������ ���� ���, �ӵ� ���)
		aiProcess_JoinIdenticalVertices |           // ��ġ�� �Ȱ��ٰ� �Ǵ��ص� �� �������� ������ ���߿� ������ ���ܵ� �������� �ʰ� ���̱�
		aiProcess_FindInvalidData |                 // ���� �߿� � ������ �������� �����Ͱ� �������� �Ǻ�
		aiProcess_TransformUVCoords |               // Ʈ�������� UV ��ǥ�� ���� ��� (�ؽ�ó�� ���� ��� ���)
		aiProcess_FlipUVs |                         // �ؽ�ó�� UV�� ������ �ٸ��ٰų�, �� ��ü�� �ݴ� �����̾ UV�� ����� �ν�
		aiProcess_ConvertToLeftHanded);             // ����� ������ ���ͷ� ǥ���� ��, �޼� ��ǥ��� �ٲ۴ٴ� �� = DX�� �����

	assert(scene != nullptr); // ���� �� ������ ���� ����
	                          // = �� �����ӿ�ũ�� FBX Ȥ�� �ٸ� ���� �� �����Ͱ� ������ ���� �����ϰڽ��ϴ�
}

ModelExporter::~ModelExporter()
{
	delete importer;

	// delete scene; // ai���� ���� ����

	// �� ���� �����Ͱ� �� ��ü�� �� �ű� ������
	// ����ٸ� ���� ����� �� ���� �� : ���⼭�� �ϴ� ����
	// vector<Material*> materials;
	// vector<MeshData*> meshes;
	// vector<NodeData*> nodes;
	// vector<BoneData*> bones;
}

// �ۿ��� ȣ���ϱ� ���� ��ɵ�
void ModelExporter::ExportMaterial()
{
	// �о ȣ���ϰ� �������
	ReadMaterial();
	WriteMaterial();
}

void ModelExporter::ExportMesh()
{
	// ������ �ϳ��� �б�
	ReadNode(scene->mRootNode, -1, -1); // root node : ���� ������ �ִ�, ��ü �� ��ü�� �Ѱ��ϴ� ���
	ReadMesh(scene->mRootNode);         // ��絵 �б�
	WriteMesh();
}

void ModelExporter::ExportClip(string clipName)
{
	FOR(scene->mNumAnimations) // �о���� ���Ͽ��� ���ϵ� �ִϸ��̼��� �� ��ŭ i�� ���� �ݺ����� ������
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

		aiColor3D color; // �� �޾ƿ���
		Material::MaterialBuffer::Data& data = material->GetData(); // ��Ƽ���� ������ �޾ƿ���

		// �ҽ��� �� ������ �޾Ƽ� �����ϱ�
		srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);    // ��ǻ� �÷��� �����ϱ� (�Ű������� ����->��� ����)
		data.diffuse = Float4(color.r, color.g, color.b, 1); // ��ǻ� ���� �����ؼ� �����Ϳ� �����ذ���

		srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);   // �ݻ������� �÷��� �����ϱ� (�Ű������� ����->��� ����)
		data.diffuse = Float4(color.r, color.g, color.b, 1); // �ݻ������� ���� �����ؼ� �����Ϳ� �����ذ���

		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);    // ��ο� ������ �÷��� �����ϱ� (�Ű������� ����->��� ����)
		data.diffuse = Float4(color.r, color.g, color.b, 1); // ��ο� ������ ���� �����ؼ� �����Ϳ� �����ذ���

		srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);   // ���� ������ �÷��� �����ϱ� (�Ű������� ����->��� ����)
		data.diffuse = Float4(color.r, color.g, color.b, 1); // ���� ������ ���� �����ؼ� �����Ϳ� �����ذ���

		srcMaterial->Get(AI_MATKEY_SHININESS, data.shininess); // ���� �޾Ƶ��̴� ������ ����

		aiString file;
		srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);        // ���Ͽ��� �ؽ�ó�� ���� ��� (��ǻ���)
		material->SetDiffuseMap(ToWString(CreateTexture(file.C_Str()))); // ������ �̸����� �ؽ�ó�� �����ؼ� ��Ƽ���� ����
		
		file.Clear(); // ���� �б� �޸� �ʱ�ȭ

		srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);       // ���Ͽ��� �ؽ�ó�� ���� ��� (��ǻ���)
		material->SetDiffuseMap(ToWString(CreateTexture(file.C_Str()))); // ������ �̸����� �ؽ�ó�� �����ؼ� ��Ƽ���� ����

		file.Clear(); // ���� �б� �޸� �ʱ�ȭ

		srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file); // ���Ͽ��� �ؽ�ó�� ���� ��� (��ǻ���)
		material->SetDiffuseMap(ToWString(CreateTexture(file.C_Str()))); // ������ �̸����� �ؽ�ó�� �����ؼ� ��Ƽ���� ����
		file.Clear(); // ���� �б� �޸� �ʱ�ȭ

		materials.push_back(material); // ���Ϳ� �ֱ�
	}
}

void ModelExporter::WriteMaterial()
{
	// ���� ���� : ���⼭ ���� ���� ������ ����� ���� ����
	// * ȣȯ�� �ִ� ������ �ʿ��ϸ� �׶� ���� Ŭ������ �ҷ��� ����

	string savePath = "Models/Materials/" + name + "/";
	string fileName = name + ".mats"; // .mats : ��Ƽ���� �������� ������ �� ���� Ȯ���� (���⼱ ���� ������ �ٸ�����)

	CreateFolders(savePath);

	BinaryWriter* writer = new BinaryWriter(savePath + fileName);

	writer->UInt(materials.size()); // �ϰϾ� �� ��Ƽ���� ���� �̸� ����

	for (Material* material : materials)
	{
		string path = savePath + material->GetName() + ".mat";
		material->Save(path);

		writer->String(path); // ���Ͽ� ������ ���, �̸� ��� ����

		delete material; // ������ �а� ���Ⱑ �����̴� ��Ƽ���� �� �� �� �ϳ��� �����
	}

	materials.clear(); // �� ���������� ���͵� �뵵 �� ��
	
	delete writer;
}

string ModelExporter::CreateTexture(string file)
{
	if (file.length() == 0)
	{
		return ""; // �ƹ��͵� ���� ���� ����
	}

	string fileName = GetFileNameWithoutExtension(file) + ".png"; // ���� �̸� �غ�
	string savePath = "Textures/Model/" + name + "/" + fileName;

	CreateFolders(savePath);

	const aiTexture* texture = scene->GetEmbeddedTexture(file.c_str()); // �����̸����� FBX ���� �ؽ�ó ��������

	if (texture == nullptr) // �׷� ���� �ؽ�ó�� ���ٸ� �� ����
	{
		return "";
	}

	if (texture->mHeight < 1)
	{
		BinaryWriter writer(savePath);
		writer.Byte(texture->pcData, texture->mWidth);
	}
	else
	{
		// �ؽ�ó ������ C++�� Image Ŭ������ �Űܴ��
		Image image;
		image.width      = texture->mWidth;
		image.height     = texture->mHeight;
		image.pixels     = (uint8_t*)(texture->pcData); // 8����Ʈ int : ���� �׸� Ư���� �������� �ʹ� ���� ���� �����ϱ�
		image.rowPitch   = image.width * 4;
		image.slicePitch = image.width * image.height * 4;

		// ����ϱ� ( = �׸��� �ֱ�) : �߰��ɼ� ����, PNG, ��ġ�� ������ ���ڿ��� ����
		SaveToWICFile(image, 
			WIC_FLAGS_NONE,
			GetWICCodec(WIC_CODEC_PNG), 
			ToWString(savePath).c_str());
	}

	// ��� ���� ��θ� ��ȯ
	return savePath;
}

void ModelExporter::ReadMesh(aiNode* node)
{
	FOR(node->mNumMeshes) // �Ű������� ���� ���� ����� ���� �޽� ������ ����
	{
		MeshData* mesh = new MeshData();
		mesh->name = node->mName.C_Str();

		UINT index = node->mMeshes[i]; // ���� ���� �ִ� i��° �޽ÿ� ��ϵ� �ε����� ��������
		aiMesh* srcMesh = scene->mMeshes[index]; // ������ �ε����� ���� ã�Ƴ��� �޽�

		mesh->materialIndex = srcMesh->mMaterialIndex; // ��Ƽ������ �ε���(��) �޾ƿ���

		vector<VertexWeights> vertexWeights(srcMesh->mNumVertices);
		ReadBone(srcMesh, vertexWeights); // ���� ����⸦ ���⼭ ȣ��

		mesh->vertices.resize(srcMesh->mNumVertices);

		for (UINT v = 0; v < srcMesh->mNumVertices; ++v) // ������ v
		{
			ModelVertex vertex;
			memcpy(&vertex.pos, &srcMesh->mVertices[v], sizeof(Float3));

			if (srcMesh->HasTextureCoords(0)) // HasTextureCoords : �Ű������� ���� ������ �ؽ�ó ��ǥ�� �ִ°�?
				                              // true : �ؽ�ó�� ���� ������ 1�� �̻� ����
			{
				memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][v], sizeof(Float2));
			}

			if (srcMesh->HasNormals()) // �޽ð� ���� ������ ���� ���� �ִٸ�
			{
				memcpy(&vertex.normal, &srcMesh->mNormals[v], sizeof(Float3));
			}

			if (srcMesh->HasTangentsAndBitangents()) // ź��Ʈ (������ ���� ȭ�� ���� ����)�� ���� �ִٸ�
			{
				memcpy(&vertex.tangent, &srcMesh->mTangents[v], sizeof(Float3));
			}

			// �̷��� �޸� ī�Ǹ� ���ؼ� ���� �޽��� ������ �޸𸮷� �о���δ�

			// �װ��� mesh�� ����
			mesh->vertices[v] = vertex;
		}

		// ������� ����
		// ������ʹ� �ε���

		mesh->indices.resize(srcMesh->mNumFaces * 3); // ���� �޽��� �� ���� x3

		for (UINT f = 0; f < srcMesh->mNumFaces; ++f)
		{
			aiFace& face = srcMesh->mFaces[f]; // ���� �ϳ��� �޾Ƽ�

			for (UINT k = 0; k < face.mNumIndices; ++k)
			{
				// �� �ϳ� �ǳʶ� ������ �ε��� 3�� �ǳʶٰ�, �� ���� ���� 3���� �ε��� �ޱ�
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

}

void ModelExporter::ReadBone(aiMesh* mesh, vector<VertexWeights>& vertexWeights)
{

}

void ModelExporter::WriteMesh()
{

}

Clip* ModelExporter::ReadClip(aiAnimation* animation)
{
	return nullptr;
}

void ModelExporter::ReadKeyFrame(Clip* clip, aiNode node, vector<ClipNode>* clipnodes)
{

}

void ModelExporter::WriteClip(Clip* clip, string clipName, UINT index)
{

}

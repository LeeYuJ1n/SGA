#pragma once

class ModelExporter
{
	// �� �����͸� ���� �����Ϳ��� �� ��� ������ ���� ������ �������� ��ȯ���� Ŭ����

	// ���� ������ : FBX, nif, dds, png... ��Ʈ ������, Ű ������ �� 
	//              �⺻���� �����Ͱ� ������ ��� ��¥ ���ҽ�

	// �� ������ : .mesh, .model, .mats, .mat, .prefab
	// �𸮾� ���� : .mesh, .model, mats
	// ����Ƽ ���� : .mat, .prefab
	//              ���� �����͸� ���ؼ� ���� ������ ������ ������ �� �ֵ���
	//              �뵵�� �ڷ����� ���� �����͸� �ٽ� ������ ���

public:
	ModelExporter(string name, string file);
	// ���Ͽ��� ������ �̸��� �����ؼ�, ���� �̸��� ����� ���� �����͸� �����
	~ModelExporter();

	void ExportMaterial(); // ��Ƽ����
	void ExportMesh();     // �޽�
	void ExportClip(string clipName);     // Ű �������� �о ������ �����ͷ� �������� ���� �Լ�

private:
	// ��Ƽ����
	void ReadMaterial();  // �������� ������ �б�
	void WriteMaterial(); // ���� ������ �����ϰų� ����
	
	string CreateTexture(string file);
	// FBX�� �ȿ� ������, �޽�, �ؽ�ó���� �� ���� �ִ� ���
	// �ؽ�ó�� ���� ���� ���� �Լ�

	// �޽�
	// ai�� ������ ���� ����Ʈ���� �����ϴ� �ڷ��������� �����ϰڴٶ�� ��
	void ReadMesh(aiNode* node); // ��ü ��� �б�
	void ReadNode(aiNode* node, int index, int parent); // ���� ���� �б�
	void ReadBone(aiMesh* mesh, vector<VertexWeights>& vertexWeights); // ����� ������ ����ġ ����

	void WriteMesh(); // �� ���� �����ͷ� ��� �޽� �����

	// ����
	Clip* ReadClip(aiAnimation* animation); // aiAnimation : ���� ����Ʈ ���̺귯���� �ִϸ��̼� ���� Ŭ����

	void ReadKeyFrame(Clip* clip, aiNode node, vector<ClipNode>* clipnodes); // Ű ������ �б�
	void WriteClip(Clip* clip, string clipName, UINT index);                 // ���������� ������ �����ϱ�

private:
	// ���� ����Ʈ ���̺귯�� ��� : �о���̱� Ŭ����
	Assimp::Importer* importer; // importer : �о����, export : �Ἥ ������

	const aiScene* scene; // ����Ʈ�� �� �����ϱ� : �ٸ� ������ �Լ��� �ҷ��� �� �ְ�

	string name; // ���� �̸��� �Ű��������� ���� �� �ְ�

	vector<Material*> materials;
	vector<MeshData*> meshes;
	vector<NodeData*> nodes;
	vector<BoneData*> bones;

	map<string, UINT> boneMap;

	UINT boneCount = 0; // ���� ���� (0���� �ʱ�ȭ�� ����)
};


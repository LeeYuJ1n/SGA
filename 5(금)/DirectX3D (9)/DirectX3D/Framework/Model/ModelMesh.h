#pragma once

class ModelMesh
{
public:
	ModelMesh(string name); // �̸��� �޾Ƽ� �޽� �����
	~ModelMesh();

	void Render();

	// void* : ���� ������ ������ �𸣴ϱ�, Ȥ�� �����̶� ���� �����ϵ���
	//         (2D���� ��ư�� ����� ���� ���)
	void CreateMesh(void* vertexData, 
		UINT vertexCount, 
		void* indexData, 
		UINT indexCount);

	void SetMaterial(Material* material) { this->material = material; }

private:
	string name; // �� �޽��� �̸�

	Material* material;
	Mesh<ModelVertex>* mesh;
};


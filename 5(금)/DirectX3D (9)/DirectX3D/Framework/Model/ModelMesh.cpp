#include "Framework.h"

ModelMesh::ModelMesh(string name) : name(name)
{
	// this->name = name;
}

ModelMesh::~ModelMesh()
{
	// ��Ƽ������ �ؽ�ó���� �����
	delete mesh;
}

void ModelMesh::Render()
{
	// nullptr ���� ���ǹ� ��� : �ʿ䰡 ������ (�ٸ� ���� ���ؼ� ��Ƽ������ �������� �ϴϱ�)
	//                           ���ǹ��� ������ ��Ƽ���� ��� �ȵ�
	material->Set();
	mesh->Draw();
}

void ModelMesh::CreateMesh(void* vertexData, UINT vertexCount, void* indexData, UINT indexCount)
{
	// ������ �⺻ �޽� ����
	mesh = new Mesh<ModelVertex>();

	// ������ �Ű������� ���� ������ �ε����� �� ������ �̸� ���� ������¡
	// -> �Ű������� ������ �ε����� �� ������ �ִٴ� ���ε� �׷��� �ǳ� ( = �ش� ������ ������ ��� �ϳ�?)
	//    = �� Ŭ������ ���� ����Ʈ ���̺귯��, Ȥ�� �� �ܿ��� DX�� ������ ���� ������ ���ε� ������ ���°��� ����� �ϰ� �ִ�
	//      �ش� ������ ����� �׸� ����ó�� ������ ������ �̹� �� �ִ�
	mesh->GetVertices().resize(vertexCount);
	mesh->GetIndices().resize(indexCount);

	// -> �� ������¡�ΰ�? �� reserve�� �ƴѰ�?
	
	// memcpy : strcpy�� ������ ������ ���� �Լ�, C++ �⺻ ���� �Լ� �� �ϳ�
	//          strcpy���� ���̴� ���� ����� ���ڿ��� �ƴ϶� �����Ͷ�� ��
	//          �����͸� �ҷ��ͼ� ǥ�� ��ġ�� �������� ���̱� ������ 
	//          reserve(�⺻�� ���� �ʰ� ���ุ ��) �Լ��� �������� �ʾƵ� �ȴ�
	memcpy(mesh->GetVertices().data(), vertexData, sizeof(ModelVertex) * vertexCount);
	memcpy(mesh->GetIndices().data(), indexData, sizeof(UINT) * indexCount);
	// -> ������ �����͸� �����ͼ�, ã�Ƴ� ������ �� ���� (x������ �޸� ũ��)��ŭ, �Ű������� ���� ���� �ǵ����ش�

	// ������ �ε����� �޾ƿͼ� �ε��ϰ�, �غ� �ߴ�
	// -> �����

	mesh->CreateMesh();
}

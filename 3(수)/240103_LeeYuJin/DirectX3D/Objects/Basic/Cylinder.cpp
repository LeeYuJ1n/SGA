#include "Framework.h"

Cylinder::Cylinder(float radius, float height, UINT sliceCount)
	: radius(radius), height(height), sliceCount(sliceCount)
{
	tag = "Cylinder"; // �±� ���̱�

	// �޽� ����� (ȣ��)
	mesh = new Mesh<VertexType>();
	MakeMesh();          // ���� ���
	MakeNormal();        // ��翡�� ������ ����
	MakeTangent();       // ������ ���� ��� ������ �ؽ�ó ȭ�Һ���
	mesh->CreateMesh();  // ���� �� ���� ���� ������ �޽� �����
}

Cylinder::~Cylinder()
{
	delete mesh;
}

void Cylinder::Render()
{
	SetRender();
	mesh->Draw();
}

void Cylinder::MakeMesh()
{
	// ��Ÿ ���ϱ� (���ư��鼭 ���� ���� �� ���� ���� �ݺ��� ó���� ȸ�� ����)
	float thetaStep = XM_2PI / sliceCount; // ��ü �� �� ���� ������ �����̽�

	// ���� �ޱ�
	vector<VertexType>& vertices = mesh->GetVertices();
	vertices.reserve((sliceCount + 1) * 4); // ��, �Ʒ�, ���� �� �� ���� ���

	// ���������� �׸���
	VertexType top;
	top.pos = { 0, (height * 0.5f), 0 };
	top.uv  = { 0.5f, 0.5f };
	
	vertices.push_back(top);

	for (int i = 0; i <= sliceCount; ++i) // ���ƿ� ������ �����ؼ� �� ���� ������
	{
		// ���� ������ ����
		float theta = thetaStep * i;

		// ���� x, y ���ϱ�
		float x = cos(theta);
		float z = sin(theta);

		VertexType vertex;

		// �������� �����ؼ� ���� ��ġ ���ϱ�
		vertex.pos = { x * radius, height * 0.5f, z * radius };
		vertex.uv  = { (x + 1) / 2,(z + 1) / 2 };

		// ��ġ�� ������ ������ ���Ϳ�
		vertices.push_back(vertex);
	}

	// �Ʒ� �� �׸���
	VertexType bottom;
	bottom.pos = { 0, (height * -0.5f), 0 };
	bottom.uv  = { 0.5f, 0.5f };

	vertices.push_back(bottom);

	for (int i = 0; i <= sliceCount; ++i) // ���ƿ� ������ �����ؼ� �� ���� ������
	{
		// ���� ������ ����
		float theta = thetaStep * i;

		// ���� x, y ���ϱ�
		float x = cos(theta);
		float z = sin(theta);

		VertexType vertex;

		// �������� �����ؼ� ���� ��ġ ���ϱ�
		vertex.pos = { x * radius, height * -0.5f, z * radius };
		vertex.uv  = { (x + 1) / 2,(z + 1) / 2 };

		// ��ġ�� ������ ������ ���Ϳ�
		vertices.push_back(vertex);
	}

	// ��
	for (int i = 0; i <= sliceCount; ++i)
	{
		float theta = thetaStep * i;

		float x = cos(theta);
		float z = sin(theta);

		VertexType vertex1;
		vertex1.pos = { x * radius,height * -0.5f,z * radius };
		vertex1.uv  = { (float)i / (float)sliceCount,1.0f };
		vertices.push_back(vertex1);

		VertexType vertex2; // ���� ���� vertex�� �� �� �ᵵ �Ǵµ� �ǹ� ���л�
		vertex2.pos = { x * radius,height * 0.5f,z * radius };
		vertex2.uv  = { (float)i / (float)sliceCount, 0.0f };
		vertices.push_back(vertex2);
	}

	// ���� ������ �ε��� ���ۿ� �ֱ�
	vector<UINT>& indices = mesh->GetIndices();

	indices.reserve(sliceCount * 6); // x6 : �� �����

	for (UINT i = 0; i < sliceCount; ++i)
	{
		indices.push_back(0);      // top
		indices.push_back(i + 2);  // ���� �� ��
		indices.push_back(i + 1);  // ��� ���� ���� �ٷ� �� ��
	}

	// �Ʒ���
	UINT bottomIndex = sliceCount + 2; // 0 ~ sliceCount + 1 ������ ���� �׸��鼭 �� �Ҵ� �����ϱ�
	
	// for (UINT i = bottomIndex; i < sliceCount; ++i) // <- �̷��� �־ �Ǵµ� ����̳� ���ذ� ����
	for (UINT i = 0; i < sliceCount; ++i)
	{
		// ��� �ε��� ����� �� �� ��
		indices.push_back(bottomIndex + i + 0);
		indices.push_back(bottomIndex + i + 1);
		indices.push_back(bottomIndex + i + 2);
	}

	// ����
	UINT SideIndex = (sliceCount + 2) * 2; // �� ����, �Ʒ� ����, �� ���� �ε���

	for (UINT i = 0; i < sliceCount; ++i)
	{
		// ��� �ε��� ����� �� �� ��
		indices.push_back(SideIndex + (i * 2) + 0); // ���� �ε��� + 0
		indices.push_back(SideIndex + (i * 2) + 1); // ���� �ε��� + 1
		indices.push_back(SideIndex + (i * 2) + 2); // ���� �ε��� + 2

		indices.push_back(SideIndex + (i * 2) + 2); // ���� �ε��� + 2
		indices.push_back(SideIndex + (i * 2) + 1); // ���� �ε��� + 1
		indices.push_back(SideIndex + (i * 2) + 3); // ���� �ε��� + 3
	}
}

void Cylinder::MakeNormal()
{
	// ������ �ε��� �޾ƿ���
	vector<VertexType>& vertices = mesh->GetVertices();
	vector<UINT>& indices = mesh->GetIndices();

	for (UINT i = 0; i < indices.size() / 3; ++i) // x3 : ���� ���� ���� (�� 3���� �� �� �� ��)
	{
		// �ε��� ���ϱ�
		UINT index0 = indices[(i * 3) + 0];
		UINT index1 = indices[(i * 3) + 1];
		UINT index2 = indices[(i * 3) + 2];

		// ���� ��ġ ���ϱ�
		Vector3 v0 = vertices[index0].pos;
		Vector3 v1 = vertices[index1].pos;
		Vector3 v2 = vertices[index2].pos;

		// ������ ���̷� ���� ���� ���ϱ�
		Vector3 e0 = v1 - v0;
		Vector3 e1 = v2 - v0;
		
		// �� ������ ����ȭ(���� ���� = ũ�ν� ����)�ؼ� ����ȭ
		Vector3 normal = Cross(e0, e1).GetNormalized();

		// ���� ���� �ǵ��
		vertices[index0].normal = normal + vertices[index0].normal;
		vertices[index1].normal = normal + vertices[index1].normal;
		vertices[index2].normal = normal + vertices[index2].normal;
	}
}

void Cylinder::MakeTangent()
{
	// ������ �ε��� �޾ƿ���
	vector<VertexType>& vertices = mesh->GetVertices();
	vector<UINT>& indices = mesh->GetIndices();

	for (UINT i = 0; i < indices.size() / 3; ++i)
	{
		// �ε��� ���ϱ�
		UINT index0 = indices[(i * 3) + 0];
		UINT index1 = indices[(i * 3) + 1];
		UINT index2 = indices[(i * 3) + 2];

		// �� ���� ��ġ ���ϱ�
		Vector3 p0 = vertices[index0].pos;
		Vector3 p1 = vertices[index1].pos;
		Vector3 p2 = vertices[index2].pos;

		// UV��ǥ (2����)
		Vector2 uv0 = vertices[index0].uv;
		Vector2 uv1 = vertices[index1].uv;
		Vector2 uv2 = vertices[index2].uv;

		// ������ ����
		Vector3 e0 = p1 - p0;
		Vector3 e1 = p2 - p0;

		// UV�� �� ���ϱ�
		float u1 = uv1.x - uv0.x;
		float v1 = uv1.y - uv0.y;
		float u2 = uv2.x - uv0.x;
		float v2 = uv2.y - uv0.y;

		// ź��Ʈ
		float d = 1.0f / (u1 * v2 - u2 * v1);
		Vector3 tangent = d * (e0 * v2 - e1 * v1);

		// ź��Ʈ �ǵ��
		vertices[index0].tangent = tangent + vertices[index0].tangent;
		vertices[index1].tangent = tangent + vertices[index1].tangent;
		vertices[index2].tangent = tangent + vertices[index2].tangent;
	}
}
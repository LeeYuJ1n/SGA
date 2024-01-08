#pragma once

class Cylinder : public GameObject
{
private:
	typedef VertexUVNormalTangent VertexType;

public:
	Cylinder(float radius = 1.0f, float height = 1.0f, UINT sliceCount = 32);
	~Cylinder();

	void Render() override;

private:
	void MakeMesh();
	void MakeNormal();
	void MakeTangent();

	Mesh<VertexType>* mesh;

	float radius; // ������ ������ ���� 1 : �ٴ��� ��
	float height; // ������ ������ ���� 2 : ������ ���� �簢��

	UINT sliceCount; // �������� �� �׸��� = �������� ����� �ٰ������� ����� ���� �Ű� �ʿ�
};


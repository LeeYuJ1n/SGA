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

	float radius; // 원통이 원통인 이유 1 : 바닥이 원
	float height; // 원통이 원통인 이유 2 : 옆에서 보면 사각형

	UINT sliceCount; // 정점으로 원 그리기 = 원주율을 나누어서 다각형으로 만들기 위한 매개 필요
};


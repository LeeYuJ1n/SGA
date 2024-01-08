#include "Framework.h"

Cylinder::Cylinder(float radius, float height, UINT sliceCount)
	: radius(radius), height(height), sliceCount(sliceCount)
{
	tag = "Cylinder"; // 태그 붙이기

	// 메시 만들기 (호출)
	mesh = new Mesh<VertexType>();
	MakeMesh();          // 정점 모양
	MakeNormal();        // 모양에서 나오는 법선
	MakeTangent();       // 법선과 같이 사용 가능한 텍스처 화소보정
	mesh->CreateMesh();  // 정점 및 관련 버퍼 정보로 메시 만들기
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
	// 세타 구하기 (돌아가면서 정점 찍을 때 쓰기 위한 반복문 처리별 회전 각도)
	float thetaStep = XM_2PI / sliceCount; // 전체 원 한 바퀴 나누기 슬라이스

	// 정점 받기
	vector<VertexType>& vertices = mesh->GetVertices();
	vertices.reserve((sliceCount + 1) * 4); // 위, 아래, 옆의 양 끝 정점 찍기

	// 위에서부터 그리기
	VertexType top;
	top.pos = { 0, (height * 0.5f), 0 };
	top.uv  = { 0.5f, 0.5f };
	
	vertices.push_back(top);

	for (int i = 0; i <= sliceCount; ++i) // 돌아올 때까지 포함해서 한 바퀴 돌리기
	{
		// 현재 정점의 각도
		float theta = thetaStep * i;

		// 평면상 x, y 구하기
		float x = cos(theta);
		float z = sin(theta);

		VertexType vertex;

		// 반지름을 적용해서 정점 위치 구하기
		vertex.pos = { x * radius, height * 0.5f, z * radius };
		vertex.uv  = { (x + 1) / 2,(z + 1) / 2 };

		// 위치가 정해진 정점을 벡터에
		vertices.push_back(vertex);
	}

	// 아래 면 그리기
	VertexType bottom;
	bottom.pos = { 0, (height * -0.5f), 0 };
	bottom.uv  = { 0.5f, 0.5f };

	vertices.push_back(bottom);

	for (int i = 0; i <= sliceCount; ++i) // 돌아올 때까지 포함해서 한 바퀴 돌리기
	{
		// 현재 정점의 각도
		float theta = thetaStep * i;

		// 평면상 x, y 구하기
		float x = cos(theta);
		float z = sin(theta);

		VertexType vertex;

		// 반지름을 적용해서 정점 위치 구하기
		vertex.pos = { x * radius, height * -0.5f, z * radius };
		vertex.uv  = { (x + 1) / 2,(z + 1) / 2 };

		// 위치가 정해진 정점을 벡터에
		vertices.push_back(vertex);
	}

	// 옆
	for (int i = 0; i <= sliceCount; ++i)
	{
		float theta = thetaStep * i;

		float x = cos(theta);
		float z = sin(theta);

		VertexType vertex1;
		vertex1.pos = { x * radius,height * -0.5f,z * radius };
		vertex1.uv  = { (float)i / (float)sliceCount,1.0f };
		vertices.push_back(vertex1);

		VertexType vertex2; // 위에 만든 vertex를 두 번 써도 되는데 의미 구분상
		vertex2.pos = { x * radius,height * 0.5f,z * radius };
		vertex2.uv  = { (float)i / (float)sliceCount, 0.0f };
		vertices.push_back(vertex2);
	}

	// 만든 정점을 인덱스 버퍼에 넣기
	vector<UINT>& indices = mesh->GetIndices();

	indices.reserve(sliceCount * 6); // x6 : 면 만들기

	for (UINT i = 0; i < sliceCount; ++i)
	{
		indices.push_back(0);      // top
		indices.push_back(i + 2);  // 위의 한 점
		indices.push_back(i + 1);  // 방금 찍은 점의 바로 앞 점
	}

	// 아랫면
	UINT bottomIndex = sliceCount + 2; // 0 ~ sliceCount + 1 까지는 윗면 그리면서 다 할당 했으니까
	
	// for (UINT i = bottomIndex; i < sliceCount; ++i) // <- 이렇게 넣어도 되는데 계산이나 이해가 귀찮
	for (UINT i = 0; i < sliceCount; ++i)
	{
		// 대신 인덱스 계산을 한 번 더
		indices.push_back(bottomIndex + i + 0);
		indices.push_back(bottomIndex + i + 1);
		indices.push_back(bottomIndex + i + 2);
	}

	// 옆면
	UINT SideIndex = (sliceCount + 2) * 2; // 위 빼고, 아래 빼고, 그 다음 인덱스

	for (UINT i = 0; i < sliceCount; ++i)
	{
		// 대신 인덱스 계산을 한 번 더
		indices.push_back(SideIndex + (i * 2) + 0); // 기준 인덱스 + 0
		indices.push_back(SideIndex + (i * 2) + 1); // 기준 인덱스 + 1
		indices.push_back(SideIndex + (i * 2) + 2); // 기준 인덱스 + 2

		indices.push_back(SideIndex + (i * 2) + 2); // 기준 인덱스 + 2
		indices.push_back(SideIndex + (i * 2) + 1); // 기준 인덱스 + 1
		indices.push_back(SideIndex + (i * 2) + 3); // 기준 인덱스 + 3
	}
}

void Cylinder::MakeNormal()
{
	// 정점과 인덱스 받아오기
	vector<VertexType>& vertices = mesh->GetVertices();
	vector<UINT>& indices = mesh->GetIndices();

	for (UINT i = 0; i < indices.size() / 3; ++i) // x3 : 면을 보기 위해 (점 3개가 모여 면 한 개)
	{
		// 인덱스 구하기
		UINT index0 = indices[(i * 3) + 0];
		UINT index1 = indices[(i * 3) + 1];
		UINT index2 = indices[(i * 3) + 2];

		// 정점 위치 구하기
		Vector3 v0 = vertices[index0].pos;
		Vector3 v1 = vertices[index1].pos;
		Vector3 v2 = vertices[index2].pos;

		// 정점간 차이로 면의 방향 구하기
		Vector3 e0 = v1 - v0;
		Vector3 e1 = v2 - v0;
		
		// 면 방향을 벡터화(법선 도출 = 크로스 연산)해서 정규화
		Vector3 normal = Cross(e0, e1).GetNormalized();

		// 법선 정보 피드백
		vertices[index0].normal = normal + vertices[index0].normal;
		vertices[index1].normal = normal + vertices[index1].normal;
		vertices[index2].normal = normal + vertices[index2].normal;
	}
}

void Cylinder::MakeTangent()
{
	// 정점과 인덱스 받아오기
	vector<VertexType>& vertices = mesh->GetVertices();
	vector<UINT>& indices = mesh->GetIndices();

	for (UINT i = 0; i < indices.size() / 3; ++i)
	{
		// 인덱스 구하기
		UINT index0 = indices[(i * 3) + 0];
		UINT index1 = indices[(i * 3) + 1];
		UINT index2 = indices[(i * 3) + 2];

		// 각 정점 위치 구하기
		Vector3 p0 = vertices[index0].pos;
		Vector3 p1 = vertices[index1].pos;
		Vector3 p2 = vertices[index2].pos;

		// UV좌표 (2차원)
		Vector2 uv0 = vertices[index0].uv;
		Vector2 uv1 = vertices[index1].uv;
		Vector2 uv2 = vertices[index2].uv;

		// 정점간 차이
		Vector3 e0 = p1 - p0;
		Vector3 e1 = p2 - p0;

		// UV간 차 구하기
		float u1 = uv1.x - uv0.x;
		float v1 = uv1.y - uv0.y;
		float u2 = uv2.x - uv0.x;
		float v2 = uv2.y - uv0.y;

		// 탄젠트
		float d = 1.0f / (u1 * v2 - u2 * v1);
		Vector3 tangent = d * (e0 * v2 - e1 * v1);

		// 탄젠트 피드백
		vertices[index0].tangent = tangent + vertices[index0].tangent;
		vertices[index1].tangent = tangent + vertices[index1].tangent;
		vertices[index2].tangent = tangent + vertices[index2].tangent;
	}
}
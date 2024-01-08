#include "Framework.h"

ModelMesh::ModelMesh(string name) : name(name)
{
	// this->name = name;
}

ModelMesh::~ModelMesh()
{
	// 매티리얼은 텍스처에서 지운다
	delete mesh;
}

void ModelMesh::Render()
{
	// nullptr 감지 조건문 폐기 : 필요가 없었음 (다른 곳을 통해서 매티리얼을 넣으려고 하니까)
	//                           조건문이 있으면 매티리얼 출력 안됨
	material->Set();
	mesh->Draw();
}

void ModelMesh::CreateMesh(void* vertexData, UINT vertexCount, void* indexData, UINT indexCount)
{
	// 부정형 기본 메시 생성
	mesh = new Mesh<ModelVertex>();

	// 위에서 매개변수로 받은 정점과 인덱스의 총 개수로 미리 벡터 리사이징
	// -> 매개변수에 정점과 인덱스의 총 개수가 있다는 말인데 그래도 되나 ( = 해당 정보가 없으면 어떻게 하나?)
	//    = 이 클래스는 에셋 임포트 라이브러리, 혹은 그 외에도 DX나 엔진과 같은 곳에서 공인된 포맷을 쓰는것을 전재로 하고 있다
	//      해당 포맷은 헤더엣 그림 파일처럼 데이터 정보가 이미 다 있다
	mesh->GetVertices().resize(vertexCount);
	mesh->GetIndices().resize(indexCount);

	// -> 왜 리사이징인가? 왜 reserve가 아닌가?
	
	// memcpy : strcpy와 유사한 데이터 복제 함수, C++ 기본 제공 함수 중 하나
	//          strcpy와의 차이는 복제 대상이 문자열이 아니라 데이터라는 것
	//          데이터를 불러와서 표적 위치에 덮어씌우려는 것이기 때문에 
	//          reserve(기본값 주지 않고 예약만 함) 함수에 얾매이지 않아도 된다
	memcpy(mesh->GetVertices().data(), vertexData, sizeof(ModelVertex) * vertexCount);
	memcpy(mesh->GetIndices().data(), indexData, sizeof(UINT) * indexCount);
	// -> 벡터의 데이터를 가져와서, 찾아낸 정점의 총 개수 (x정점의 메모리 크기)만큼, 매개변수로 받은 곳에 되돌려준다

	// 정점과 인덱스를 받아와서 로드하고, 준비 했다
	// -> 만든다

	mesh->CreateMesh();
}

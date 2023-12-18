#include "Framework.h"

Collider::Collider() : GameObject(L"Basic/DiffuseLight.hlsl")
{
	// 메시 만들기
	mesh = new Mesh<Vertex>(); // 아직 부정형 (세부 충돌체마다 형태 따로 지정 필요)

	SetColor(0, 1, 0); // 기본은 초록색
}

Collider::~Collider()
{
	delete mesh;
}

void Collider::Render()
{
	// (2D와 마찬가지) 트랜스폼이 활성화되어 있어야 렌더
	
	// 지금 클래스에서 렌더가 On 상태여야 또 렌더
	if (!isRender) return;

	SetRender(); // 부모의 렌더 세팅

	mesh->Draw(); // 설정된 기본 세팅에 의해서 출력
	// mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST); // 메시를 선의 집합으로 표시하기
}

bool Collider::IsCollision(Collider* collider)
{
	// 활성화가 되지 않았으면 false 반환
	// (보류)

	// 필요한 호출 (세부 유형에 따라 실제 판별 함수 호출)
	switch (collider->type) // 부딪친 충돌체의 타입이 무엇인가에 따라
	{
	case Collider::Type::BOX:
		return IsBoxCollision((BoxCollider*)collider);

	case Collider::Type::SPHERE:
		return InSphereCollision((SphereCollider*) collider);
	}

	// 여기까지 왔다면 둘 중 하나
	// 1. 충돌체의 타입이 박스도 구조체도 아니다
	// 2. 충돌 상황 자체에 어떤 문제가 있어서 판별을 못 하겠다
	//    (단순 충돌 아님이라면 위에서 false가 return됐을 테니까)

	return false;
}

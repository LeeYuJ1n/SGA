#pragma once

class BoxCollider : public Collider
{
	// 3D 충돌체를 상속받은 "박스" 세부 충돌체

	// 박스 충돌에서 필요한 것
	// 1. 박스 생김새
	// 2. 박스 제작에 필요한 정보( = 크기)
	// 3. (WinAPI, DX2D 때와 같은) 충돌 당시의 상황을 기록하기 위한 정보들 (함수에 있거나 직접 도출하거나 구조체를 만들거나)
	//    -> "AABB"와 "OBB" : 박스끼리의 충돌을 AABB, 구와의 충돌을 OBB로 지칭

public:
	BoxCollider(Vector3 size = { 1, 1, 1});
	~BoxCollider() = default;

	// OBB 기록용 구조체
	struct ObbDesc
	{
		Vector3 pos;      // 위치
		Vector3 axis[3];  // 축 정보
		Vector3 halfSize; // 계산 편의를 위한 절반크기
	};

	// OBB가 발생할 경우 기록하기 위한 함수
	void GetObb(ObbDesc& obbDesc);

	// AABB는 일단 보류(하나하나 만들면 축이 늘어남에 따라 복잡)

	// 판별하는 기능 선언
	virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact = nullptr) override;
	virtual bool InSphereCollision(class SphereCollider* collider) override;
	virtual bool IsBoxCollision(class BoxCollider* collider) override;

	// 축이 다른 경우 계산을 적용하기 위한 별도 함수
	bool IsSeperateAxis(Vector3 D, Vector3 axis, ObbDesc box1, ObbDesc box2);

	// (부모 인터페이스에서 받은) 모양 만들기
	virtual void MakeMesh() override;

	// 실제 사이즈(라기 보다, 상대적인 비율일 경우가...)
	Vector3 size;
};


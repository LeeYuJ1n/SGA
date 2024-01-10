#pragma once

class Human : public ModelAnimator
{
public:
	Human();
	~Human();

	void Update();
	void Render();
	void GUIRender();

private:
	// TODO :
	// 나중에 자식 개체가 붙거나 별도 연산 대상이 생기면 코드 추가
	// 자식 개체 : 모자, 배낭, 방탄 조끼, 손에 든 무기 등
	// 별도 연산 대상 : 발소리 체크를 위한 "내 발" 혹은 무기를 쥐기 위한 "내 손"

	// 예 : 쇠지렛대를 무기로 사용해, 손에 쥐기
	Crowbar* crowbar;    // 쇠지렛대 (무기)
	Transform* mainHand; // 주로 쓰는 손 (보통은 오른쪽인)

private:
	void Control();
	void Jump(); // 지금은 좌표격차(높이 0)가 마치 땅인 것 처럼 만들어도 OK
	             // 혹은 존재하는 터레인 에디터 혹은 블록 매니저와 연결하거나

	// 움직임용 변수들 

	// 일단은 예시 (써도 좋고, 수정해도 좋고)
	float moveSpeed;
	float jumpVelocity;
	float jumpForce;
	float gravityMult;

	bool isJump;

};


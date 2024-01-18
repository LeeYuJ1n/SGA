#pragma once

class DepthStencil
{
	// 뎁스 스텐실 : 뎁스 버퍼 스테이트와 스텐실 버퍼 스테이트를 쉽게 설정하고 저정하기 위한 클래스

	// 뎁스 버퍼 : 화소에 Z 위치, 혹은 출려그이 우선순위를 지정해서 우선순위가 높은 쪽이 출력됟록 하는 데이터
	// 스텐실 버퍼 : 화소에 출력 선별 여부, 혹은 장애물이 있을 경우 영향을 받을지 여부 (혹은 지금 가려져 있는가)
	//              등을 계속 지정, 재지정하면서 이미지 출력 여부를 선별하는 데이터

	// ~~~~스테이트 : DX에서 그래픽 연산 데이터(버퍼)를 일괄처리하기 위한 지정한 기능

	// 그럼 이 클래스는 왜 있는가? -> 매번 스테잉트를 불러서 옵션을 지정하는 번거로움을 (100%는 못 없애도)
	//                              가능한 선에서는 지우기 위해서

	// -> 이는 곧 스테이트를 귀찮을 정도로 불러야 할 응용 기능이 앞으로 있을 거라는 이야기

	// -> 따라서 이 클래스는 앞으로 있을 버퍼 응용 기능을 위한 밑준비라고 볼 수 있다

public:
	// ○ 생성자
	DepthStencil(IN UINT width     = WIN_WIDTH, 
		         IN UINT height    = WIN_HEIGHT, 
		         IN bool isStencil = false);
	// 매개변수 : 가로, 세로, "이 객체는 스텐실에 대한 지정인가?" 여부

	// ○ 소멸자
	~DepthStencil();

	void Clear(); // 리셋

	ID3D11DepthStencilView*& GetDSV() { OUT return dsv; }
	ID3D11ShaderResourceView*& GetSRV() { OUT return srv; }

	// TODO : 콕 집어서 옵션을 바꿀 일이 있으면 여기서 추가 작성을 하면 된다

private:
	// ○ 내부용 멤버 함수

	void CreateDSVTexture();
	void CreateDSV();
	void CreateSRV();

private:
	// ○ 내부용 멤버 변수

	UINT width;     // 가로
	UINT height;    // 세로
	bool isStencil; // 인스턴스는 스텐실에 대한 지정인가?

	// DX 제공 데이터를 통한 변수 저장
	ID3D11Texture2D* dsvTexture;   // 뎁스-스텐실-뷰 텍스처
	ID3D11DepthStencilView* dsv;   // 뎁스-스텐실 스테이트를 거친 결과로서의 "뷰"
	ID3D11ShaderResourceView* srv; // 셰이더 리소스 뷰 = 텍스처를 셰이더로 연산시켜 주는 과정이자 결과
};


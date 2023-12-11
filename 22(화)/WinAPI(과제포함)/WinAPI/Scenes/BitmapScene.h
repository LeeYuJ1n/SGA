#pragma once

class BitmapScene : public Scene
{
public:
	BitmapScene();
	~BitmapScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	// 비트맵 씬
	// 비트맵 : 화면에서 각 픽셀이 어떤 색을 가지고 있는지를 구성한 자료의 집합(위치와 색 정보로 이루어진 map)
	//          → 컴퓨터에서 그림을 나타내는 가장 단순하고 정확한 방식

	// 비트맵이 출력되려면? 그림 데이터가 필요하다

	// 앱에서 말하는 그림 데이터는 크게 두 가지를 뜻한다

	// 1. 그림 그 자체 (로raw 데이터라고도 하고, 자원resource(리소스) 데이터라고도 한다)
	// 2. 그 실제 그림을 앱에서 코드의 형태로 등록한 것 (등록된 변수)
	
	// 위의 1과 2까지 모두 합쳐서 그림 데이터라고 한다

	// 그림은 탐색기로 폴더에 넣었으니, 등록할 변수를 코드에서 만들자

	HBITMAP artist; // 도화가 그림
	HBITMAP human; // 사람 그림
	// HBITMAP : 그림 파일을 앱에서 쓰기 위해 등록하는 자료형

	HBITMAP human2;

	// 그리고 한 가지가 더 필요하다
	
	// 지금 우리가 윈도우에서 화면을 2개로 나누어서 번갈아 출력 중(실제 + 가상)
	// → 깜빡임, 실시간 처리에 의한 시간 비효율 등을 줄이기 위해서

	// → 똑같은 이유로, 그림을 처리해줄 가상의 출력 장소가 또 하나 더 필요하다

	HDC memDC; // 그림을 처음 그려준 (눈에 안 보이는) 출력 장소
};


#include "Framework.h"
#include "ShaderScene.h"

ShaderScene::ShaderScene()
{
	// 그대로 씬 초기화를 진행
	Init();
}

ShaderScene::~ShaderScene()
{
	// 그대로 종료
	Quit();
}

void ShaderScene::Update()
{
	// 추가로 조작할 부분이 있으면 코드 추가
}

void ShaderScene::Render()
{
	secondMap->PSSet(1);        // 이펙트인 것처럼 (씌우자)
	intValueBuffer->SetPS(1);   // 1 : 여기서는 이펙트 -> 이 버퍼는 필터로 씌우는 그림에 적용할 거라는 의미
	floatValueBuffer->SetPS(2); // 2, 0 : 여기서는 그림 -> 이 버퍼는 쿼드에 쓰겠다

	quad->Render();
}

void ShaderScene::PostRender()
{
	ImGui::ColorEdit4("Color", (float*) &quad->GetColor()); // 색 수동 지정
	ImGui::SliderInt("Index", intValueBuffer->Get(), 0, 8); // 정수 포인터와 최소, 최대 값을 지정한 슬라이더

	ImGui::SliderInt("Scale1", &intValueBuffer->Get()[1], 0, 100); // 인트버퍼 배열의 두 번째 값의 위치
	ImGui::SliderInt("Scale2", &intValueBuffer->Get()[2], 0, 100); // 이 버퍼가 가진 숫자를 추가로 사용 가능
	ImGui::SliderInt("Scale3", &intValueBuffer->Get()[3], 0, 100); // 매개변수는 정수버퍼에서 인덱스 이후로 받은 각 셰이더 정보
	                                                               // * 라이트 셰이더의 경우, [1]의 의미 = 광원의 반지름

	ImGui::SliderFloat2("LightLocation", &floatValueBuffer->Get()[2], 0, 1000); // 광원의 위치, 숫자는 뷰포트 상의 픽셀 위치 (단 텍스처 UV 기준)
}

void ShaderScene::Init()
{
	// 그림부터 할당
	quad = new Quad(true, L"Textures/Test_Picture.jpg"); // 첫 번째 매개변수로 true를 줘서 텍스처(UV)를 쓰는 쿼드가 되도록 생성
	quad->Pos() = { CENTER_X, CENTER_Y };
	quad->UpdateWorld();

	// 이 다음에 만든 쿼드에 대한 2차 설정이 들어가야 한다
	// quad->SetPixelShader(L"Multi.hlsl"); // (일단 다중 셰이더 사용부터)
	// quad->SetPixelShader(L"Light.hlsl");
	quad->SetPixelShader(L"Filter.hlsl");

	intValueBuffer = new IntValueBuffer();
	floatValueBuffer = new FloatValueBuffer();

	floatValueBuffer->Get()[0] = quad->GetSize().x * 2;
	floatValueBuffer->Get()[1] = quad->GetSize().y * 2;

	// 두 번째 텍스처 만들기
	secondMap = Texture::Add(L"Textures/sun.png");
}

void ShaderScene::Quit()
{
	delete quad;
	delete intValueBuffer;
	delete floatValueBuffer;

	secondMap->Delete();
}
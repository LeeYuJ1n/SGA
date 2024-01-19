#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
	forest = new Model("Forest");
	forest->Scale() *= 10.0f;
	forest->UpdateWorld();

	imitationHuman = new Human();
	imitationHuman->UpdateWorld();

	human = new Human();
	renderTarget = new RenderTarget();
	depthstencil = new DepthStencil();

	quad  = new Quad(Vector2(500, 500)); // 아무것도 없는 사각형 만들기 (그림이 아니다)
	quad->Pos()  = { 300, 400 };
	quad->GetMaterial()->SetShader(L"PostEffect/Bloom.hlsl"); // "빛번짐" 효과 : 후처리 셰이더 중 하나
	quad->GetMaterial()->SetDiffuseMap(Texture::Add(L"Render", renderTarget->GetSRV()));
	// 매개변수는 "렌더라는 이름으로 지칭할, 렌더 타겟 객체의 실시간 생성 텍스처
	quad->UpdateWorld();

	valueBuffer = new FloatValueBuffer(); // 새 소수 연산용 버퍼 생성
	valueBuffer->Get()[0] = 1;
	valueBuffer->Get()[1] = 1;

	isRenderTarget = false;
}

RenderTargetScene::~RenderTargetScene()
{
	// ○ 포인터 인스턴스 지우기
	delete forest;
	delete human;
	delete renderTarget;
	delete depthstencil;
	delete quad;
	delete valueBuffer;
}

void RenderTargetScene::Update()
{
	human->Update();

	if (!isRenderTarget)
	{
		if (KEY_DOWN('I'))
		{
			isRenderTarget = true;
		}
	}
	else if (isRenderTarget)
	{
		if (KEY_DOWN('I'))
		{
			isRenderTarget = false;
		}
	}
	
}

void RenderTargetScene::PreRender()
{
	renderTarget->Set(depthstencil);

	imitationHuman->Render();
}

void RenderTargetScene::Render()
{
	forest->Render();
	human->Render();
}

void RenderTargetScene::PostRender()
{
	valueBuffer->SetPS(10);

	if (isRenderTarget)
	{
		quad->Render(); // 쿼드(렌더 타겟의 결과물)를 렌더
	}
	else {}
	
}

void RenderTargetScene::GUIRender()
{
	// Threshold : 임계점 -> 설정한 연산이나 일어나기 위한 최소(혹은 최대)조건
	//             임계점을 못 넘으면 연산이 아예 수행되지 않음
	//             게임에서는 방어력이나 공략 조건 등에 응용된다
	ImGui::SliderFloat("Threshold", &valueBuffer->Get()[0], 0, 1);

	// * 위 임계점에 대한 연산값 : 빛번짐 셰이더의 적용 계수
	//   빛에 의한 가시정도 (밝은 정도)가 설정된 값 이하일 때 (위 Threshold로 설정)
	//   이 옵션에서 설정된 대로 색조가 변화할 것
	ImGui::SliderFloat("Value", &valueBuffer->Get()[1], 0, 10);
}

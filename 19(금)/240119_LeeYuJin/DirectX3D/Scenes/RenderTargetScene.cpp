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

	quad  = new Quad(Vector2(500, 500)); // �ƹ��͵� ���� �簢�� ����� (�׸��� �ƴϴ�)
	quad->Pos()  = { 300, 400 };
	quad->GetMaterial()->SetShader(L"PostEffect/Bloom.hlsl"); // "������" ȿ�� : ��ó�� ���̴� �� �ϳ�
	quad->GetMaterial()->SetDiffuseMap(Texture::Add(L"Render", renderTarget->GetSRV()));
	// �Ű������� "������� �̸����� ��Ī��, ���� Ÿ�� ��ü�� �ǽð� ���� �ؽ�ó
	quad->UpdateWorld();

	valueBuffer = new FloatValueBuffer(); // �� �Ҽ� ����� ���� ����
	valueBuffer->Get()[0] = 1;
	valueBuffer->Get()[1] = 1;

	isRenderTarget = false;
}

RenderTargetScene::~RenderTargetScene()
{
	// �� ������ �ν��Ͻ� �����
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
		quad->Render(); // ����(���� Ÿ���� �����)�� ����
	}
	else {}
	
}

void RenderTargetScene::GUIRender()
{
	// Threshold : �Ӱ��� -> ������ �����̳� �Ͼ�� ���� �ּ�(Ȥ�� �ִ�)����
	//             �Ӱ����� �� ������ ������ �ƿ� ������� ����
	//             ���ӿ����� �����̳� ���� ���� � ����ȴ�
	ImGui::SliderFloat("Threshold", &valueBuffer->Get()[0], 0, 1);

	// * �� �Ӱ����� ���� ���갪 : ������ ���̴��� ���� ���
	//   ���� ���� �������� (���� ����)�� ������ �� ������ �� (�� Threshold�� ����)
	//   �� �ɼǿ��� ������ ��� ������ ��ȭ�� ��
	ImGui::SliderFloat("Value", &valueBuffer->Get()[1], 0, 10);
}

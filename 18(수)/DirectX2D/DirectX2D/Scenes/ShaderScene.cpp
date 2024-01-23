#include "Framework.h"
#include "ShaderScene.h"

ShaderScene::ShaderScene()
{
	// �״�� �� �ʱ�ȭ�� ����
	Init();
}

ShaderScene::~ShaderScene()
{
	// �״�� ����
	Quit();
}

void ShaderScene::Update()
{
	// �߰��� ������ �κ��� ������ �ڵ� �߰�
}

void ShaderScene::Render()
{
	secondMap->PSSet(1);        // ����Ʈ�� ��ó�� (������)
	intValueBuffer->SetPS(1);   // 1 : ���⼭�� ����Ʈ -> �� ���۴� ���ͷ� ����� �׸��� ������ �Ŷ�� �ǹ�
	floatValueBuffer->SetPS(2); // 2, 0 : ���⼭�� �׸� -> �� ���۴� ���忡 ���ڴ�

	quad->Render();
}

void ShaderScene::PostRender()
{
	ImGui::ColorEdit4("Color", (float*) &quad->GetColor()); // �� ���� ����
	ImGui::SliderInt("Index", intValueBuffer->Get(), 0, 8); // ���� �����Ϳ� �ּ�, �ִ� ���� ������ �����̴�

	ImGui::SliderInt("Scale1", &intValueBuffer->Get()[1], 0, 100); // ��Ʈ���� �迭�� �� ��° ���� ��ġ
	ImGui::SliderInt("Scale2", &intValueBuffer->Get()[2], 0, 100); // �� ���۰� ���� ���ڸ� �߰��� ��� ����
	ImGui::SliderInt("Scale3", &intValueBuffer->Get()[3], 0, 100); // �Ű������� �������ۿ��� �ε��� ���ķ� ���� �� ���̴� ����
	                                                               // * ����Ʈ ���̴��� ���, [1]�� �ǹ� = ������ ������

	ImGui::SliderFloat2("LightLocation", &floatValueBuffer->Get()[2], 0, 1000); // ������ ��ġ, ���ڴ� ����Ʈ ���� �ȼ� ��ġ (�� �ؽ�ó UV ����)
}

void ShaderScene::Init()
{
	// �׸����� �Ҵ�
	quad = new Quad(true, L"Textures/Test_Picture.jpg"); // ù ��° �Ű������� true�� �༭ �ؽ�ó(UV)�� ���� ���尡 �ǵ��� ����
	quad->Pos() = { CENTER_X, CENTER_Y };
	quad->UpdateWorld();

	// �� ������ ���� ���忡 ���� 2�� ������ ���� �Ѵ�
	// quad->SetPixelShader(L"Multi.hlsl"); // (�ϴ� ���� ���̴� ������)
	// quad->SetPixelShader(L"Light.hlsl");
	quad->SetPixelShader(L"Filter.hlsl");

	intValueBuffer = new IntValueBuffer();
	floatValueBuffer = new FloatValueBuffer();

	floatValueBuffer->Get()[0] = quad->GetSize().x * 2;
	floatValueBuffer->Get()[1] = quad->GetSize().y * 2;

	// �� ��° �ؽ�ó �����
	secondMap = Texture::Add(L"Textures/sun.png");
}

void ShaderScene::Quit()
{
	delete quad;
	delete intValueBuffer;
	delete floatValueBuffer;

	secondMap->Delete();
}
#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
    // ��� �ۼ�
    background = new Quad(L"Textures/Shooting/backgraound.png");
    background->Pos() = {CENTER_X, CENTER_Y};
    background->Scale() = background->Scale() * 2;
    background->UpdateWorld();

    //�����
    plane = new Plane();
    plane->Pos() = { CENTER_X, CENTER_Y };

    //���� Ÿ�� �ν��Ͻ� ����
    renderTarget = new RenderTarget();

    Texture* texture = Texture::Add(L"Textures/blank.png", renderTarget->GetSRV());

    //���� Ÿ�� ������ ������ ����� �ؽ�ó
    Quad* renderTexture;
    renderTexture = new Quad(Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 2));
    renderTexture->Pos() = { CENTER_X / 2, CENTER_Y / 2 };
    renderTexture->UpdateWorld();
    renderTexture->SetTexture(texture);

    //���� Ÿ�� �ؽ�ó�� ���Ϳ� �ֱ�
    renderTextures.push_back(renderTexture);

    // ���� ������ ���� �Ҵ��� ���ļ� �� �ؽ�ó �� ����� (C++���� cin���� �Է� �ٲ�� �Ͱ� ����� ����)
    renderTexture = new Quad(Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 2)); //ũ��� ù ��°�� ����
    renderTexture->Pos() = { CENTER_X * 3 / 2, CENTER_Y / 2 }; // ��ġ�� ù ��°�� ���� ������
    renderTexture->UpdateWorld();
    renderTexture->SetTexture(texture);
    //�̹� �ؽ�ó�� �߰� �ȼ� ���̴� �����ϱ�
    renderTexture->SetPixelShader(L"Filter.hlsl");

    //���� Ÿ�� �ؽ�ó�� ���Ϳ� �ֱ�
    renderTextures.push_back(renderTexture);

    //���� �����
    intBuffer = new IntValueBuffer();
    intBuffer->Get()[0] = 3;
    intBuffer->Get()[1] = 50;

    floatBuffer = new FloatValueBuffer();
    floatBuffer->Get()[0] = WIN_WIDTH;
    floatBuffer->Get()[1] = WIN_HEIGHT;
}

RenderTargetScene::~RenderTargetScene()
{
    delete background;
    delete plane;

    delete renderTarget;

    for (Quad* quad : renderTextures)
        delete quad;

    delete intBuffer;
    delete floatBuffer;
}

void RenderTargetScene::Update()
{
    plane->Update();
}

void RenderTargetScene::Render()
{
    // ���� Ÿ���� �ƴ϶�� ���⼭ (��) ���� ����
    // (�� ȭ�鿡 ���;� �Ǵ� �� �ִٸ� ���⼭ �ۼ�)
}

void RenderTargetScene::PreRender()
{
    // ���� �ۼ��Ǵ� �ڵ���� ���� ���� ���� ����ȴ�

    renderTarget->Set(); // ������ ������ ���� ���� ��ü�� �ƴ�, ������Ʈ��⵵ �ָ���

    //���� ����⵵ ����Ϳ� ���� ��µ� ����� (�̹�����) �ƴϴ�
    background->Render();
    plane->Render();
}

void RenderTargetScene::PostRender()
{
    // ���� Ÿ���� ȭ�� ���� ������, 1�� ��� �Ŀ�, ����� ���� ���
    // (ȭ���� ������� �ϸ� ���⼭ ���)

    intBuffer->SetPS(1);   //���Ϳ� ���߼��̴�
    floatBuffer->SetPS(2); //�ؽ�ó

    //���� Ÿ�� ���
    for (Quad* renderTexture : renderTextures)
        renderTexture->Render();
}
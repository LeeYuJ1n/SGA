#pragma once

class GBuffer
{
	// G Buffer : ������Ʈ��(���) ����
	//            ��ü ������ ����(������ ���� ����)�� ������ ������ �� �ֵ��� �����͸�
	//            ������ �з��ϴ� ���� Ŭ����

	// -> ��ü ������ ���¸� ������ �����ؼ� ��¿ �ǰ�? -> ������ �Ŵ�
	// -> ���� Ÿ���� ���� ��ǻ�� ���忡���� ������, ��� ���忡�� ���� ���� �з��ϴ� ��

public:
	// �� ������
	GBuffer();

	// �� �Ҹ���
	~GBuffer();

	// �� �Լ�
	void SetMultiRenderTarget();
	void PostRender();
	void SetSRVs();

private:
	// ���⿡ �ʿ��� ���� Ÿ�� �������� �־�д�

	// �Ʒ� �� �� �ڵ尡 ���� �ڵ��̸�, ���߿� ����� �� �ּ��� Ǯ� ����
	// vector<RenderTarget*> renderers;                // <- �̷� ���ͷ� ���� ���� Ÿ��"��"�� �⺻��
	// vector< ID3D11ShaderResourceView*> shaderViews; // �⺻���� �����ϴ� ���̴� ���ҽ�

	// �� ���� ���̴�
	
	// ���� �����ʹ� ���� : ���� ���� �������� ���� ���� �ӽ� ������
	// ������ �� �⺻���� ���� : ���� ���� ���� Ÿ���� ���� ������ ���鼭 �ٸ� ȭ���� ���� ���� ����
	RenderTarget* diffuseRender;
	RenderTarget* specularRender;
	RenderTarget* normalRender;

	DepthStencil* depthStencil;

	RenderTarget* rtvs[3];

	class Quad* quads[4]; // ���߿� ��� ����� 4��
	ID3D11ShaderResourceView* srvs[4];
};


#pragma once

class RenderTarget
{
	// �� More
	
	// ���� Ÿ�� : ������ ����� ����Ʈ ��ü�� �ƴ� ������ ������ �κ������� �����ϴ� ��
	//            �׸��� �� ������ ����� Ŭ������ �����ϱ⵵ �Ѵ�

public:
	// �� ������
	RenderTarget(UINT width  = WIN_WIDTH,
		         UINT height = WIN_HEIGHT,
		         DXGI_FORMAT = DXGI_FORMAT_R32G32B32A32_FLOAT);
	// �⺻�� ������ ��ü ũ�⸸ŭ, �Ϲ� ���ó��

	// �� �Ҹ���
	~RenderTarget();

	void Set(DepthStencil* depthStencil, Float4 clearColor = Float4(1 ,1, 1, 1)); // ���� ���ٽ� �ڷ� �ʿ�, �⺻ ����(����)�� �Ͼ��
	static void SetMulti(RenderTarget** target,
		                 UINT count, 
		                 DepthStencil* depthStencil,
		                 Float4 clearColor = Float4(1, 1, 1, 1));
	// ���� ���ٽ� �ڷ� �ʿ�, �⺻ ����(����)�� �Ͼ��
	// �׸��� 1�� �̻��� ���� Ÿ�� �ʿ�
	// (ù �Ű����� = �������� �迭 (Ȥ�� �����ͷ� ǥ�� ������ �������� �迭))

	ID3D11ShaderResourceView*& GetSRV() { return srv; } // &�� ���� ���� ����
	ID3D11RenderTargetView*& GetRTV() { return rtv; }   // &�� ���� ���� ����

private:
	void CreateRTVTexture();
	void CreateRTV();
	void CreateSRV();

private:
	// �� ���� ������

	UINT width;
	UINT height;

	DXGI_FORMAT format; // �׷��� ���� - ���߿� ���� �̿��� ���� ���� �����ڵ�

	ID3D11Texture2D* rtvTexture;    //���� Ÿ�ٿ� ����� �ؽ�ó (�ð��� ���)
	ID3D11RenderTargetView* rtv;    // ���� Ÿ�� ��
	ID3D11ShaderResourceView* srv;  // ���̴� ���ҽ�
};

